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
    this->entityList = NULL;
    this->wallList = NULL;
}

std::list<Door*> ModuleTile::getDoorList() const {
    return doorList;
}

templateList<Wall> *ModuleTile::getWallList() const {
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

void ModuleTile::addToWallList(Wall *wall)
{
    templateList<Wall> *newWall = new templateList<Wall>();
    newWall->data = wall;
    newWall->next = wallList;
    wallList = newWall;
}

void ModuleTile::addToDoorList(Door *doors)
{
    doorList.push_back(doors);
}

void ModuleTile::addToEntityList(Entity* toAdd)
{
    templateList<Entity> *temp = entityList;
    while(temp != NULL)
    {
        if(temp->data == toAdd)return;
        temp = temp->next;
    }
    templateList<Entity> *newEntity = new templateList<Entity>();
    newEntity->data = toAdd;
    newEntity->next = entityList;
    entityList = newEntity;
}

void ModuleTile::deleteFromEntityList(Entity* toDelete)
{
    if(entityList != NULL && entityList->find(toDelete) != NULL)
    {
        if(entityList->data == toDelete)
        {
            templateList<Entity> *temp = entityList;
            entityList = entityList -> next;
            delete temp;
        }
        else
        {
            templateList<Entity> *temp = entityList->findPrevious(toDelete);
            templateList<Entity> *listToDelete = temp->next;
            temp->next = listToDelete->next;
            delete listToDelete;
        }
    }
}

templateList<Entity>* ModuleTile::getEntityList() const {
    return entityList;
}

void ModuleTile::deleteWall(Wall* toDelete)
{
    if(wallList != NULL && wallList->find(toDelete) != NULL)
    {
        if(wallList->data == toDelete)
        {
            templateList<Wall> *temp = wallList;
            wallList = wallList -> next;
            delete temp;
        }
        else
        {
            templateList<Wall> *temp = wallList->findPrevious(toDelete);
            templateList<Wall> *listToDelete = temp->next;
            temp->next = listToDelete->next;
            delete listToDelete;
        }
    }
    for(int i = 0; i < adjacentTilesCount; i++)
    {
        ModuleTile *tile = adjacentTiles[i];
        if(tile != NULL)if(tile->wallList != NULL && tile->wallList->find(toDelete) != NULL)
        {
            if(tile->wallList->data == toDelete)
            {
                templateList<Wall> *temp = tile->wallList;
                tile->wallList = tile->wallList -> next;
                delete temp;
            }
            else
            {
                templateList<Wall> *temp = tile->wallList->findPrevious(toDelete);
                templateList<Wall> *listToDelete = temp->next;
                temp->next = listToDelete->next;
                delete listToDelete;
            }
        }
    }
}