/* 
 * File:   ModuleTile.cpp
 * Author: Qb
 * 
 * Created on 8 grudzień 2014, 18:53
 */

#include "ModuleTile.h"
#include "globalVariables.h"
#include "Turret.h"

ModuleTile::ModuleTile(bool obstructed, int roomId, int base) {
    this->aiTile = new AiTile(obstructed, roomId, base);
    this->entityList = NULL;
    this->wallList = NULL;
    this->turretList = NULL;
    doorList = new Door*[4];
    for(int i = 0; i < 4; i++)doorList[i] = NULL;
    threatLevel = 0;
}

void ModuleTile::update()
{
    templateList<Entity> *turrets = turretList;
    while(turrets != NULL)
    {
        Turret *cT = dynamic_cast<Turret*>(turrets->data);
        if(cT->getCurrentThreatLevel() < threatLevel)
        {
            cT->setCurrentThreatLevel(threatLevel);
            cT->setTargetAngle(Variables::getAngle(centerX, centerY, cT->getCoords()->X, cT->getCoords()->Y), centerX, centerY);
        }
        turrets = turrets->next;
    }
}

Door **ModuleTile::getDoorList() const {
    return doorList;
}

templateList<Wall> *ModuleTile::getWallList() const {
    return wallList;
}

ModuleTile** ModuleTile::getAdjacentTiles() const {
    return adjacentTiles;
}

void ModuleTile::setAdjacentTiles(ModuleTile **tiles)
{
    adjacentTiles = tiles;
    for(int i = 0; i < 8; i++)
    {
        if(adjacentTiles[i] == NULL)aiTile->setAdjacentTile(i, NULL);
        else aiTile->setAdjacentTile(i, adjacentTiles[i]->getAiTile());
    }
}

void ModuleTile::addToWallList(Wall *wall)
{
    templateList<Wall> *newWall = new templateList<Wall>();
    newWall->data = wall;
    newWall->next = wallList;
    wallList = newWall;
}

void ModuleTile::addToDoorList(Door *doors, int direction)
{
    doorList[direction] = doors;
    aiTile->setOpenDoorValue(((direction+1) * 2) - 1, true);
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
    for(int i = 0; i < 8; i++)
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

AiTile* ModuleTile::getAiTile() const {
    return aiTile;
}


bool ModuleTile::hasOpenDoor(int direction)
{
    bool result = false;
    if(direction % 2 != 0)
    {
        if(doorList[direction/2] != NULL)if(doorList[direction/2]->isOpen())result = true;
    }
    return result;
}

void ModuleTile::addToThreatLevel(int threatLevel) {
    this->threatLevel += threatLevel;
    if(this->threatLevel < 0)this->threatLevel = 0;
}

int ModuleTile::getThreatLevel() const {
    return threatLevel;
}

void ModuleTile::propagateTurret(Entity* turret)
{
    if(Variables::proximity(centerX, centerY, turret->getCoords()->X, 
            turret->getCoords()->Y) <= dynamic_cast<Turret*>(turret)->getRange())
    {
        if(turretList->find(turret) == NULL)
        {
            templateList<Entity> *newTurret = new templateList<Entity>();
            newTurret->data = turret;
            newTurret->next = turretList;
            turretList = newTurret;
            
            for(int i = 0; i < 8; i++)
            {
                if(adjacentTiles[i] != NULL)
                    if(adjacentTiles[i]->aiTile->getRoomId() == aiTile->getRoomId() || hasOpenDoor(i))
                        adjacentTiles[i]->propagateTurret(turret);
            }
        }
    }
}

void ModuleTile::setCenter(int X, int Y)
{
    centerX = X;
    centerY = Y;
}