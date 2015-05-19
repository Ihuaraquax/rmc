/* 
 * File:   Lock.cpp
 * Author: Qb
 * 
 * Created on 7 kwiecień 2015, 18:57
 */

#include "Lock.h"
#include "globalVariables.h"
#include "Player.h"

Lock::Lock() {
    keyValue = 1;
    coords = new Coordinates();
    coords->width = Variables::tileSize;
    coords->height = Variables::tileSize;
    coords->angle = 0;
    coords->speedX = 0;
    coords->speedY = 0;
    std::string path = "images/Lock.jpg";
    this->image = new Image(path, true);
    image->state = NORMAL;
}

void Lock::update()
{
    
}

void Lock::display()
{
    image->display(coords);
}

void Lock::use()
{
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    if(player->getKeyValue() == keyValue)
    {
        player->setKeyValue(-1);
        this->health = -1;
        Variables::status = WIN;
    }
}

void Lock::save(std::fstream& savefile)
{
    savefile << "LO" << std::endl;
    this->saveGeneric(savefile);
    savefile << keyValue << ' ';
    savefile << std::endl;
}

void Lock::load(std::fstream& savefile)
{
    this->loadGeneric(savefile);
    savefile >> keyValue;
    int temp;
    savefile >> temp;
    
    ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y);
    tile->setObstacle(this);
    tile->addToEntityList(this);
    for(int i = 0; i < 4; i++)
    {
        if(tile->getAiTile()->getRoomId() == tile->getAdjacentTiles()[i*2 +1]->getAiTile()->getRoomId())
            tile->getAdjacentTiles()[i*2 +1]->setUsableObject(this);
    }
}

Entity *Lock::CreateLock(double X, double Y)
{
    Entity *lock = new Lock();
    if(X != -1)
    {        
        lock->getCoords()->X = X;
        lock->getCoords()->Y = Y;
        
        ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(lock->getCoords()->X, lock->getCoords()->Y);
        tile->setObstacle(lock);
        tile->addToEntityList(lock);
        for(int i = 0; i < 4; i++)
        {
            if(tile->getAiTile()->getRoomId() == tile->getAdjacentTiles()[i*2 +1]->getAiTile()->getRoomId())
                tile->getAdjacentTiles()[i*2 +1]->setUsableObject(dynamic_cast<Lock*>(lock));
        }
    }
    return lock;
}

void Lock::getHit(int damage, int damageType)
{
    //indestructible object
}
