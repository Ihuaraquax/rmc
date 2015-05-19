/* 
 * File:   Key.cpp
 * Author: Qb
 * 
 * Created on 7 kwiecień 2015, 18:57
 */

#include "Key.h"
#include "globalVariables.h"
#include "Player.h"

KeyHolder::KeyHolder() {
    keyValue = 1;
    hasKey = true;
    coords = new Coordinates();
    coords->width = Variables::tileSize;
    coords->height = Variables::tileSize;
    coords->angle = 0;
    coords->speedX = 0;
    coords->speedY = 0;
    std::string path = "images/KeyHolder.jpg";
    this->image = new Image(path, true);
    image->state = NORMAL;
    path = "images/Holder.jpg";
    emptyImage = new Image(path, true);
    emptyImage->state = NORMAL;
}

void KeyHolder::update()
{
    if(hasKey == false && Variables::session->getAllEntities()->getPlayer()->getHealth() < 1000)hasKey = true;
}

void KeyHolder::display()
{
    if(hasKey)image->display(coords);
    else emptyImage->display(coords);
}

void KeyHolder::save(std::fstream& savefile)
{
    savefile << "KH" << std::endl;
    this->saveGeneric(savefile);
    savefile << keyValue << ' ';
    if(hasKey)savefile << "1 ";
    else savefile << "0 ";
    savefile << std::endl;
}

void KeyHolder::load(std::fstream& savefile)
{
    this->loadGeneric(savefile);
    savefile >> keyValue;
    int temp;
    savefile >> temp;
    if(temp == 1)hasKey = true;
    else hasKey = false;
    
    ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y);
    tile->setObstacle(this);
    tile->addToEntityList(this);
    for(int i = 0; i < 4; i++)
    {
        if(tile->getAiTile()->getRoomId() == tile->getAdjacentTiles()[i*2 +1]->getAiTile()->getRoomId())
            tile->getAdjacentTiles()[i*2 +1]->setUsableObject(this);
    }
}

Entity *KeyHolder::CreateKeyHolder(double X, double Y)
{
    Entity *keyHolder = new KeyHolder();
    if(X != -1)
    {
        keyHolder->getCoords()->X = X;
        keyHolder->getCoords()->Y = Y;
        
        ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(keyHolder->getCoords()->X, keyHolder->getCoords()->Y);
        tile->setObstacle(keyHolder);
        tile->addToEntityList(keyHolder);
        for(int i = 0; i < 4; i++)
        {
            if(tile->getAiTile()->getRoomId() == tile->getAdjacentTiles()[i*2 +1]->getAiTile()->getRoomId())
                tile->getAdjacentTiles()[i*2 +1]->setUsableObject(dynamic_cast<KeyHolder*>(keyHolder));
        }
    }
    return keyHolder;
}

void KeyHolder::getHit(int damage, int damageType)
{
    //indestructible object
}

void KeyHolder::use()
{
    if(hasKey)
    {
        dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->setKeyValue(keyValue);
        hasKey = false;
    }
}
