/* 
 * File:   Monster.cpp
 * Author: Qb
 * 
 * Created on 16 grudzień 2014, 20:50
 */

#include "Monster.h"
#include "globalVariables.h"
#include "ModuleTile.h"
#include "CollisionDetector.h"
#include "Player.h"
#include "WeaponLoader.h"
#include "PickUp.h"
#include "Explosion.h"

Monster::Monster()
{
    image = Variables::images->getMonster1();
    health = 500;
    teamId = 2;
    this->coords = new Coordinates();
    this->coords->width = Variables::tileSize;
    this->coords->height = Variables::tileSize;
    this->coords->speedX = 1.7;
    this->coords->speedY = 1.7;
    this->coords->angle = 0;
    this->coords->height = 25;
    this->coords->width = 25;
    bleeds = true;
    this->weapons = new Weapon*[2];
    this->weapons[0] = new Weapon();
    this->weapons[1] = new Weapon();
    WeaponLoader::loadWeapon(weapons[0], 0);
    WeaponLoader::loadWeapon(weapons[1], 0);
    possessedWeapons = 2;
    expirience = 100;
    maximumHealth = health;
    bleeds = true;
    this->threatLevel = 10;
}

void Monster::setCoords(double X, double Y)
{
    this->coords->X = X;
    this->coords->Y = Y;
}

void Monster::setRandomCoords()
{
    do
    {
        this->coords->X = ((rand()%(Variables::tilesPerRoom - 2)) * Variables::tileSize) + Variables::tileSize;
        this->coords->Y = ((rand()%(Variables::tilesPerRoom - 2)) * Variables::tileSize) + Variables::tileSize;
    }while(isBadSpawningPoint());
}

void Monster::setStartingTile()
{
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->addToEntityList(this);
    Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->addToThreatLevel(threatLevel);
}

Monster::~Monster() {
}

void Monster::update()
{
    int direction = getDirection();
    if(direction >= 0)
    {
        int targetX = (direction / Variables::tilesPerRoom) * Variables::tileSize + 24;
        int targetY = (direction % Variables::tilesPerRoom) * Variables::tileSize + 24;        
        double dX, dY;
        dX = targetX - (coords->X);
        dY = (coords->Y) - targetY;
        double targetAngle= 180 + (atan(dX/dY) * 180 / M_PI);
        if(targetY <= (coords->Y))targetAngle += 180;
        targetAngle += 180;
        if(targetAngle > 360)targetAngle -= 360;
        if(ceil(coords->angle) - ceil(targetAngle) < -10 || ceil(coords->angle) - ceil(targetAngle) > 10)
        {
            if(!turnRight(targetAngle))coords->angle += coords->speedX;
            else coords->angle -= coords->speedX;
        }    
        double x,y;
        Variables::giveFactors(coords->angle, x,y);
        this->move(x,y);
    }
    if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[19] == 1)if(Variables::currentFrame%30 == 0)
    {
        heal(1);
    }
    if(Variables::isMonsterShoot)checkForAttack();
    for(int i = 0; i < possessedWeapons; i++)weapons[i]->update();
    this->updateBuffers();
}

int Monster::getDirection()
{
    int result = -1;
    ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->
            getModuleTileAt(coords->X + 25 - coords->width/2,
            coords->Y + 25 - coords->height/2);
    int biggestAIValue = tile->getAiTile()->getCurrentAIValue();
    
    int direction = -1;
    for(int i = 0; i < 8; i++)
    {
        if(tile->getAdjacentTiles()[i] != NULL)
        if(tile->getAdjacentTiles()[i]->getObstacle() == NULL)
        if(tile->getAdjacentTiles()[i]->getAiTile()->getCurrentAIValue() > biggestAIValue)
        {
            biggestAIValue = tile->getAiTile()->getAdjacentTiles()[i]->getCurrentAIValue();
            direction = i;
        }
    }
    if(direction >= 0)
    {
        result = Variables::session->getMap()->getCurrentModule()
                ->getIndexOfModule(tile->getAdjacentTiles()[direction]);
        
    }        
    return result;
}

void Monster::checkForAttack()
{
    ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->
            getModuleTileAt(coords->X + 25 - coords->width/2,
            coords->Y + 25 - coords->height/2);
    if(tile->getAiTile()->getTarget()->X >= 0)
    {
        this->targetCoords = tile->getAiTile()->getTarget();
        for(int i = 0; i < possessedWeapons; i++)this->attack(i);
    }
    else
    {
        for(int i = 0; i < 8; i++)
            if(tile->getAdjacentTiles()[i] != NULL)
            if(tile->getAdjacentTiles()[i]->getAiTile()->getTarget()->X >= 0)
            {
                this->targetCoords = tile->getAdjacentTiles()[i]->getAiTile()->getTarget();
                for(int i = 0; i < possessedWeapons; i++)this->attack(i);
                break;
            }
    }
}

bool Monster::isBadSpawningPoint()
{
    bool result = false;
    if(Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->getAiTile()->isObstructed())result = true;
    else if(CollisionDetector::isAnyCollision(Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y), this))result = true;
    return result;
}

void Monster::executeAgony()
{
    dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->addExpirience(expirience);
    ModuleTile *tile = Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y);
    if(tile != NULL)tile->addToThreatLevel(-threatLevel);
    if(rand()%100 <= 7)
    {
        Entity *pickUp = new PickUp();
        pickUp->setCoords(coords->X, coords->Y);
        Variables::session->getAllEntities()->addEntity(pickUp);
        Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->addToPickUpList(pickUp);
    }
    if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[13] == 1)
    {
        Entity *explosion = new Explosion();
        dynamic_cast<Explosion*>(explosion)->setCoords(coords->X, coords->Y);
        dynamic_cast<Explosion*>(explosion)->setDamage(this->maximumHealth/10);
        dynamic_cast<Explosion*>(explosion)->setDamageType(explosive);
        dynamic_cast<Explosion*>(explosion)->dealDamage();
        Variables::session->getAllEntities()->addEntity(explosion);
    }
}

bool Monster::turnRight(double targetAngle)
{
    bool result = false;
    
    int tempTargetAngle = ceil(targetAngle) +180;
    tempTargetAngle %= 360;
    int delta = 180 - ceil(coords->angle);
    tempTargetAngle += delta;
    if(tempTargetAngle < 180)result = true;
    
    return result;
}

void Monster::save(std::fstream& file)
{
    file << "MO" << std::endl;
    saveGeneric(file);
    file << expirience << ' ' << this->image->getImagePath() << ' ';
    file << std::endl;
}

void Monster::load(std::fstream& file)
{
    loadGeneric(file);
    std::string path = "images/monster2.png";
    file >> expirience >> path[0];
    this->image = new Image(path, true);
    this->image->state = NORMAL;
}

Entity *Monster::CreateMonster(double X, double Y)
{
    Entity *monster = new Monster();
    if(X != -1 && Y != -1)monster->setCoords(X,Y);
    return monster;
}