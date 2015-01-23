/* 
 * File:   ModuleTile.cpp
 * Author: Qb
 * 
 * Created on 8 grudzień 2014, 18:53
 */

#include "ModuleTile.h"
#include "globalVariables.h"

ModuleTile::ModuleTile(bool obstructed, int roomId, int base) {
    this->obstructed = rand()%50 == 0;
    this->roomId = roomId;
    this->baseAIValue = base;
    if(obstructed)this->baseAIValue -= 50;
}

std::list<Door*> ModuleTile::getDoorList() const {
    return doorList;
}

std::list<Wall*> ModuleTile::getWallList() const {
    return wallList;
}

ModuleTile** ModuleTile::getAdjacentTiles() const {
    return adjacentTiles;
}

ModuleTile::ModuleTile(const ModuleTile& orig) {
}

void ModuleTile::setRoomId(int roomId) {
    this->roomId = roomId;
}

int ModuleTile::getRoomId() const {
    return roomId;
}

ModuleTile::~ModuleTile() {
}

bool ModuleTile::isObstructed()
{
    return obstructed;
}
double ModuleTile::getAngle()
{
    return angle;
}

void ModuleTile::resetAIValue()
{
    currentAIValue = baseAIValue;
    for(int i = 0; i < adjacentTilesCount; i++)
    {
        if(adjacentTiles[i] != NULL)
        if(adjacentTiles[i]->roomId == roomId &&
           adjacentTiles[i]->currentAIValue != adjacentTiles[i]->baseAIValue)
                adjacentTiles[i]->resetAIValue();
    }
}

void ModuleTile::setAdjacentTilesCount(int adjacentTilesCount) {
    this->adjacentTilesCount = adjacentTilesCount;
}

int ModuleTile::getAdjacentTilesCount() const {
    return adjacentTilesCount;
}

void ModuleTile::setCurrentAIValue(int currentAIValue) {
    this->currentAIValue = currentAIValue;
    for(int i = 0; i < adjacentTilesCount; i++)
    {
        if(adjacentTiles[i] != NULL)
        if(adjacentTiles[i]->obstructed == false &&
           adjacentTiles[i]->roomId == roomId &&
           adjacentTiles[i]->currentAIValue < currentAIValue-5)
                adjacentTiles[i]->setCurrentAIValue(currentAIValue-5);
    }
}

int ModuleTile::getCurrentAIValue() const {
    return currentAIValue;
}

void ModuleTile::setAdjacentTiles(ModuleTile **tiles)
{
    adjacentTiles = tiles;
}

void ModuleTile::addToWallList(Wall *walls)
{
    wallList.push_back(walls);
}

void ModuleTile::addToDoorList(Door *doors)
{
    doorList.push_back(doors);
}

void ModuleTile::addToEntityList(Entity* toAdd)
{
    entityList.push_back(toAdd);
}

void ModuleTile::deleteFromEntityList(Entity* toDelete)
{
    entityList.remove(toDelete);
}

std::list<Entity*> ModuleTile::getEntitiesFromsLists()
{
    std::list<Entity*> result;
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
        result.push_back(temp);
    }
    for(int i = 0; i < 8; i++)
    {
        if(adjacentTiles[i] != NULL)
            for(std::list<Entity*>::iterator j = adjacentTiles[i]->entityList.begin(); j != adjacentTiles[i]->entityList.end(); ++j)
            {
                Entity *temp = *j;
                result.push_back(temp);
            }
    }
    return result;
}