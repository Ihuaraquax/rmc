/* 
 * File:   Spawner.cpp
 * Author: Qb
 * 
 * Created on 8 marzec 2015, 12:43
 */

#include "Spawner.h"
#include "globalVariables.h"
#include "Monster.h"
#include "MonsterLoader.h"

Spawner::Spawner() {
    this->coords = new Coordinates();
    this->coords->width = Variables::tileSize;
    this->coords->height = Variables::tileSize;
    this->coords->angle = 0;
    this->coords->speedX = 0;
    this->coords->speedY = 0;
    this->image = Variables::images->getByName("spawner");
    health = 2000;
    teamId = 0;
    this->threatLevel = 15;
    maximumHealth = health;
    spawnTimer = 5;
    spawnCountdown = 5;
}

void Spawner::setRandomCoords()
{
    int X, Y;
    bool isViableTile = false;
    do
    {        
        X = Variables::tileSize + rand()%(Variables::tileSize * (Variables::tilesPerRoom - 2));
        Y = Variables::tileSize + rand()%(Variables::tileSize * (Variables::tilesPerRoom - 2));
        X -= X%Variables::tileSize;
        Y -= Y%Variables::tileSize;
        ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X, Y);
        if(tile->getObstacle() == NULL && tile->getEntityList() == NULL)isViableTile = true;
        else isViableTile = false;
    } while(!isViableTile);
    coords->X = X;
    coords->Y = Y;
    monsterType = rand()%3;
}

void Spawner::update()
{
    if(Variables::currentFrame == 0)spawnCountdown--;
    if(spawnCountdown == 0)
    {
        spawnCountdown = spawnTimer;
        spawnMonster();
    }
    this->updateBuffers();
}

void Spawner::spawnMonster()
{
    Coordinates *spawnCoords = new Coordinates();
    spawnCoords->X = coords->X;
    spawnCoords->Y = coords->Y;
    
    int X, Y;
    int tries = 0;
    bool isViableTile = false;
    do
    {
        tries++;
        int angle = rand()%360;
        X = coords->X + 70 * cos(angle * M_PI / 180);
        Y = coords->Y + 70 * sin(angle * M_PI / 180); 
        ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X, Y);
        if(tile->getObstacle() == NULL && tile->getEntityList() == NULL)isViableTile = true;
        else isViableTile = false;
        if(tries == 5)isViableTile = true;
    } while(!isViableTile);
    if(tries < 5)
    {
        spawnCoords->X = X;
        spawnCoords->Y = Y;
        Entity *monster = Monster::CreateMonster(spawnCoords->X, spawnCoords->Y);  
        MonsterLoader::loadMonster(monster, monsterType, rand()%7);
        Variables::session->getAllEntities()->addEntity(monster);
    }
        delete spawnCoords;
}

void Spawner::setStartingTile()
{
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->addToEntityList(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->setObstacle(this);
}

void Spawner::save(std::fstream& file)
{
    file << "SP" << std::endl;
    this->saveGeneric(file);
    file << monsterType << ' ' << spawnCountdown << ' ' << spawnTimer << ' ';
    file << std::endl;
}

void Spawner::load(std::fstream& file)
{
    loadGeneric(file);
    file >> monsterType >> spawnCountdown >> spawnTimer;
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->setObstacle(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->addToThreatLevel(threatLevel);
}

Entity *Spawner::CreateSpawner(double X, double Y)
{
    Entity *spawner = new Spawner();
    if(X == 0 && Y == 0)dynamic_cast<Spawner*>(spawner)->setRandomCoords();
    else
    {
        spawner->getCoords()->X = X;
        spawner->getCoords()->Y = Y;
    }
    return spawner;
}