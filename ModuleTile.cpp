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
    this->obstacle = NULL;
    this->wallList = new Wall*[4];
    this->turretList = NULL;    
    doorList = new Door*[4];
    for(int i = 0; i < 4; i++)
    {
        wallList[i] = NULL;
        doorList[i] = NULL;
    }
    threatLevel = 0;
}

ModuleTile::~ModuleTile()
{
    obstacle = NULL;
    delete aiTile;
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

Wall **ModuleTile::getWallList() const {
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

void ModuleTile::addToWallList(Wall *wall, int direction)
{
    wallList[direction] = wall;
    aiTile->setOpenDoorValue(direction*2 + 1, false);
}

void ModuleTile::addToDoorList(Door *doors, int direction)
{
    doorList[direction] = doors;
    aiTile->setOpenDoorValue(((direction+1) * 2) - 1, doors->isOpen());
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
    if(toDelete->isBarricade())
    {
        this->obstacle = NULL;
        this->aiTile->setObstructed(false);
        this->aiTile->setBaseAIValue(0);
    }
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
    for(int i = 0; i < 4; i++)if(wallList[i] == toDelete)
    {
        wallList[i] = NULL;
        aiTile->setOpenDoorValue(i*2 + 1, true);
    }
    for(int j = 0; j < 8; j++)
    {
        for(int i = 0; i < 4; i++)if(adjacentTiles[j]->wallList[i] == toDelete)
        {
            adjacentTiles[j]->wallList[i] = NULL;
            adjacentTiles[j]->aiTile->setOpenDoorValue(i*2 +1, true);
        }
    }
}

AiTile* ModuleTile::getAiTile() const {
    return aiTile;
}


bool ModuleTile::hasOpenDoor(int direction)
{
    bool result = aiTile->isOpenDoor(direction);
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

Entity* ModuleTile::getObstacle() const {
    return obstacle;
}

void ModuleTile::setObstacle(Entity* obstacle) {
    this->obstacle = obstacle;
    this->addToEntityList(obstacle);
    aiTile->setObstructed(true);
}

void ModuleTile::deleteDoor(Door* toDelete)
{
    
    for(int i = 0; i < 4; i++)if(doorList[i] == toDelete)
    {
        doorList[i] = NULL;
        aiTile->setOpenDoorValue(i*2 + 1, true);
    }
    for(int j = 0; j < 8; j++)
    {
        for(int i = 0; i < 4; i++)if(adjacentTiles[j]->doorList[i] == toDelete)
        {
            adjacentTiles[j]->doorList[i] = NULL;
            adjacentTiles[j]->aiTile->setOpenDoorValue(i*2 +1, true);
        }
    }
}