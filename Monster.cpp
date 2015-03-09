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

Monster::Monster() {
    this->coords = new Coordinates();
    do
    {
        this->coords->X = ((rand()%(Variables::tilesPerRoom - 2)) * Variables::tileSize) + Variables::tileSize;
        this->coords->Y = ((rand()%(Variables::tilesPerRoom - 2)) * Variables::tileSize) + Variables::tileSize;
    }while(isBadSpawningPoint());
    this->coords->angle = 0;
    this->coords->height = 25;
    this->coords->width = 25;
    this->coords->speedX = 1.7;
    this->coords->speedY = 1.7;
    std::string paths[] = {"images/monster.png"};
    this->image = new Image(1, paths, true);
    this->image->state = NORMAL;
    health = 20;
    teamId = 0;
    this->weapons = new Weapon*[2];
    this->weapons[0] = new Weapon();
    this->weapons[1] = new Weapon();
    WeaponLoader::loadWeapon(weapons[0], 0);
    WeaponLoader::loadWeapon(weapons[1], 0);
    this->threatLevel = 10;
    Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->addToThreatLevel(threatLevel);
    this->setStartingTile();
    expirience = 100;
    maximumHealth = health;
}

Monster::Monster(double X, double Y)
{
    this->coords = new Coordinates();
    this->coords->X = X;
    this->coords->Y = Y;
    this->coords->angle = 0;
    this->coords->height = 25;
    this->coords->width = 25;
    this->coords->speedX = 1.7;
    this->coords->speedY = 1.7;
    std::string paths[] = {"images/monster.png"};
    this->image = new Image(1, paths, true);
    this->image->state = NORMAL;
    health = 20;
    teamId = 0;
    this->weapons = new Weapon*[2];
    this->weapons[0] = new Weapon();
    this->weapons[1] = new Weapon();
    WeaponLoader::loadWeapon(weapons[0], 0);
    WeaponLoader::loadWeapon(weapons[1], 0);
    this->threatLevel = 10;
    Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->addToThreatLevel(threatLevel);
    this->setStartingTile();
    expirience = 100;
    maximumHealth = health;
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
        coords->angle = 180 + (atan(dX/dY) * 180 / M_PI);
        if(targetY <= (coords->Y))coords->angle += 180;    
    
        double x,y;
        Variables::giveFactors(coords->angle, x,y);
        this->move(x,y);
    }
    checkForAttack();
    this->weapons[0]->update();
    this->weapons[1]->update();
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
        if(tile->getAdjacentTiles()[i]->getAiTile()->getRoomId() == tile->getAiTile()->getRoomId() || tile->hasOpenDoor(i))
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
        this->attack(true);
    }
    else
    {
        for(int i = 0; i < 8; i++)
            if(tile->getAdjacentTiles()[i] != NULL)
            if(tile->getAdjacentTiles()[i]->getAiTile()->getTarget()->X >= 0)
            {
                this->targetCoords = tile->getAdjacentTiles()[i]->getAiTile()->getTarget();
                this->attack(0);
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
}