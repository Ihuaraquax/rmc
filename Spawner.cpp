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
    this->coords->angle = 0;
    this->coords->height = 50;
    this->coords->width = 50;
    this->coords->speedX = 0;
    this->coords->speedY = 0;
    std::string paths[] = {"images/spawner.png"};
    this->image = new Image(1, paths, true);
    this->image->state = NORMAL;
    health = 2000;
    teamId = 0;
    this->threatLevel = 15;
    Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->addToThreatLevel(threatLevel);
    this->setStartingTile();
    maximumHealth = health;
    monsterType = rand()%3;
    spawnTimer = 5;
    spawnCountdown = 5;
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->setObstacle(this);
}

void Spawner::update()
{
    if(Variables::currentFrame == 0)spawnCountdown--;
    if(spawnCountdown == 0)
    {
        spawnCountdown = spawnTimer;
        spawnMonster();
    }
}

void Spawner::spawnMonster()
{
    Coordinates *spawnCoords = new Coordinates();
    spawnCoords->X = coords->X;
    spawnCoords->Y = coords->Y;
    
    int X, Y;
    bool isViableTile = false;
    do
    {
        int angle = rand()%360;
        X = coords->X + 70 * cos(angle * M_PI / 180);
        Y = coords->Y + 70 * sin(angle * M_PI / 180); 
        ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X, Y);
        if(tile->getObstacle() == NULL && tile->getEntityList() == NULL)isViableTile = true;
        else isViableTile = false;
    } while(!isViableTile);
    spawnCoords->X = X;
    spawnCoords->Y = Y;
    Entity *monster = new Monster(spawnCoords->X, spawnCoords->Y);  
    MonsterLoader::loadMonster(monster, monsterType);
    Variables::session->getAllEntities()->addEntity(monster);
    delete spawnCoords;
}
