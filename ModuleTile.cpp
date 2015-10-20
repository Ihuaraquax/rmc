/* 
 * File:   ModuleTile.cpp
 * Author: Qb
 * 
 * Created on 8 grudzień 2014, 18:53
 */

#include "ModuleTile.h"
#include "globalVariables.h"
#include "Turret.h"
#include "AiTileAdjacentSetter.h"
#include "CollisionDetector.h"

ModuleTile::ModuleTile(bool obstructed, int roomId, int base) {
    lightValue = 0;
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
    object = NULL;
    aiTiles = new AiTile*[16];
    for(int i = 0; i < 16; i++)
    {
        aiTiles[i] = new AiTile(obstructed, roomId, base);
    }
    this->bufferList = NULL;
    this->pickUpList = NULL;
    transferDirection = -1;
    this->remoteAccessObject = NULL;
}

ModuleTile::~ModuleTile()
{
    obstacle = NULL;
    delete aiTile;
    for(int i = 0; i < 16; i++)
    {
        delete aiTiles[i];
    }
    delete []aiTiles;
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

templateList<Entity>* ModuleTile::getPickUpList() const {
    return pickUpList;
}

void ModuleTile::setRemoteAccessObject(Entity* remoteAccessObject) {
    this->remoteAccessObject = remoteAccessObject;
}

Entity* ModuleTile::getRemoteAccessObject() const {
    return remoteAccessObject;
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
    AiTileAdjacentSetter::setAdjacentTiles(this);
    for(int i = 0; i < 8; i++)
    {
        if(adjacentTiles[i] == NULL)aiTile->setAdjacentTile(i, NULL);
        else aiTile->setAdjacentTile(i, adjacentTiles[i]->getAiTile());
    }
}

void ModuleTile::addToWallList(Wall *wall, int direction)
{
    wallList[direction] = wall;
}

void ModuleTile::addToDoorList(Door *door, int direction)
{
    if(this->setUsableObject(door))
    {
        doorList[direction] = door;
    }
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
    this->aiTile->changeEntitiesAiValue(toAdd->getAiValue());
}

void ModuleTile::deleteFromEntityList(Entity* toDelete)
{
    if(toDelete == NULL)
    {
        return;
    }
    if(toDelete == this->obstacle)
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
    this->aiTile->changeEntitiesAiValue(-toDelete->getAiValue());
    }
    else if(pickUpList->find(toDelete) != NULL)this->deleteFromPickUpList(toDelete);
}

templateList<Entity>* ModuleTile::getEntityList() const {
    return entityList;
}

void ModuleTile::deleteWall(Wall* toDelete)
{
    for(int i = 0; i < 4; i++)if(wallList[i] == toDelete)
    {
        wallList[i] = NULL;
    }
    for(int j = 0; j < 8; j++)
    {
        if(adjacentTiles[j] != NULL)
        {
            for(int i = 0; i < 4; i++)if(adjacentTiles[j]->wallList[i] == toDelete)
            {
                adjacentTiles[j]->wallList[i] = NULL;
            }
        }
    }
}

AiTile* ModuleTile::getAiTile() const {
    return aiTile;
}


bool ModuleTile::hasOpenDoor(int direction)
{
    return true;
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
                    if(adjacentTiles[i]->aiTile->getRoomId() == aiTile->getRoomId() && adjacentTiles[i]->getObstacle() == NULL)
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
    }
    for(int j = 0; j < 8; j++)
    {
        if(adjacentTiles[j] != NULL)
        {
            for(int i = 0; i < 4; i++)if(adjacentTiles[j]->doorList[i] == toDelete)
            {
                adjacentTiles[j]->doorList[i] = NULL;
            }
        }
    }
}

int ModuleTile::getCenterY() const {
    return centerY;
}

int ModuleTile::getCenterX() const {
    return centerX;
}

void ModuleTile::deleteTurret(Entity* turret)
{
    if(this->turretList->find(turret) != NULL)
    {
        this->deleteFromTurretList(turret);
        
            for(int i = 0; i < 8; i++)
            {
                if(adjacentTiles[i] != NULL)
                    if(adjacentTiles[i]->aiTile->getRoomId() == aiTile->getRoomId() && adjacentTiles[i]->getObstacle() == NULL)
                        adjacentTiles[i]->deleteTurret(turret);
            }
    }
}

void ModuleTile::deleteFromTurretList(Entity* toDelete)
{
    if(turretList->data == toDelete)
    {
        templateList<Entity> *temp = turretList;
        turretList = turretList -> next;
        delete temp;
    }
    else
    {
        templateList<Entity> *temp = turretList->findPrevious(toDelete);
        templateList<Entity> *listToDelete = temp->next;
        temp->next = listToDelete->next;
        delete listToDelete;
    }
}

bool ModuleTile::setUsableObject(UsableObject* object)
{
    bool result = false;
    if(this->object == NULL)
    {
        this->object = object;
        result = true;
    }
    return result;    
}

void ModuleTile::useObject()
{
    if(object != NULL)
    {
        object->use();
    }
}

AiTile** ModuleTile::getAiTiles() const {
    return aiTiles;
}

templateList<GenericBuffer>* ModuleTile::getBufferList() const {
    return bufferList;
}

AiTile *ModuleTile::getAiTileAt(double X, double Y)
{
    int x = floor(X / 12.5);
    int y = floor(Y / 12.5);
    return aiTiles[x * 4 + y];
}

void ModuleTile::propagateBuffs(GenericBuffer* buff)
{
    templateList<GenericBuffer> *newBuffer = new templateList<GenericBuffer>();
    newBuffer->data = buff;
    newBuffer->next = bufferList;
    bufferList = newBuffer;
}

void ModuleTile::depropagateBuffs(GenericBuffer* buff)
{
    templateList<GenericBuffer> *toDelete = bufferList->find(buff);
    if(toDelete != NULL)
    {
        if(toDelete == bufferList)
        {
            bufferList = bufferList->next;
            delete toDelete;
        }
        else
        {
            templateList<GenericBuffer> *previous = bufferList->findPrevious(buff);
            previous->next = toDelete->next;
            delete toDelete;
        }
        for(int i = 0; i < 8; i++)if(adjacentTiles[i] != NULL)adjacentTiles[i]->depropagateBuffs(buff);
    }
}

void ModuleTile::setTransferDirection(int transferDirection) {
    this->transferDirection = transferDirection;
}

int ModuleTile::getTransferDirection() const {
    return transferDirection;
}

void ModuleTile::deleteUsableObject(UsableObject *toDelete)
{
    if(toDelete == this->object)object = NULL;
}

void ModuleTile::addToPickUpList(Entity* toAdd)
{
    templateList<Entity> *temp = pickUpList;
    while(temp != NULL)
    {
        if(temp->data == toAdd)return;
        temp = temp->next;
    }
    templateList<Entity> *newEntity = new templateList<Entity>();
    newEntity->data = toAdd;
    newEntity->next = pickUpList;
    pickUpList = newEntity;
}

void ModuleTile::deleteFromPickUpList(Entity* toDelete)
{
    if(pickUpList->data == toDelete)
    {
        templateList<Entity> *temp = pickUpList;
        pickUpList = pickUpList -> next;
        delete temp;
    }
    else
    {
        templateList<Entity> *temp = pickUpList->findPrevious(toDelete);
        templateList<Entity> *listToDelete = temp->next;
        temp->next = listToDelete->next;
        delete listToDelete;
    }
}

void ModuleTile::addToLightValue(int value)
{
    lightValue += value;
}

void ModuleTile::highlightTile()
{
    if(this->object != NULL)
    {
        double startX = centerX - Variables::tileSize/2 - Variables::offsetX;
        double startY = centerY - Variables::tileSize/2 - Variables::offsetY;
        al_draw_rectangle(startX, startY, startX + Variables::tileSize, startY + Variables::tileSize, al_map_rgb(255,255,0), 3);
        Coordinates * coords = new Coordinates();
        coords->X = centerX - Variables::tileSize/2;
        coords->Y = centerY - Variables::tileSize/2;
        coords->width = Variables::tileSize;
        coords->height = Variables::tileSize;
        if(CollisionDetector::isBasicCollision(coords, Variables::session->getAllEntities()->getPlayer()->getCoords()))
        {
            object->highlight();
        }
        delete coords;
    }
}