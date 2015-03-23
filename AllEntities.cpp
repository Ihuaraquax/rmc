/* 
 * File:   AllEntities.cpp
 * Author: Qb
 * 
 * Created on 16 listopad 2014, 11:31
 */

#include "AllEntities.h"
#include "Player.h"
#include "Monster.h"
#include "Turret.h"
#include "globalVariables.h"
#include "Obstacle.h"
#include "Chest.h"
#include "Spawner.h"
#include "DistanceBuffer.h"
#include "BuffRod.h"
#include "ExplosiveBarrel.h"
#include "RemoteCharges.h"
#include "ObstacleDoor.h"
#include "DoorFactory.h"
#include <iostream>
  
AllEntities::AllEntities() {
    remoteCharges = NULL;
}

void AllEntities::init()
{
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
        temp->setStartingTile();
    }
    player = NULL;
    DoorFactory::createDoors();
    createObstacles();
    for(int i = 0; i < 1; i++)
    {
        Entity *monster = new Monster();
        entityList.push_back(monster);
    }
    for(int i = 0; i < 5; i++)
    {
        Entity *spawner = new Spawner();
        entityList.push_back(spawner);
    }
    for(int i = 0; i < 5; i++)
    {
        Entity *chest = new Chest();
        entityList.push_back(chest);
    }
}
AllEntities::~AllEntities()
{
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
        delete temp;
    }
    player = NULL;
}


void AllEntities::display()
{
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
        temp->display();
    }
    player->display();
}

void AllEntities::update()
{
    if(Variables::log == full)std::cout << " AllEntities Update ";
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
        temp->update();
    }
    player->update();
    if(Variables::log == full)std::cout << " AllEntities Update end ";
    deleteDead();
    if(Variables::log == full)std::cout << " AllEntities Delete ";
}

void AllEntities::collisions()
{
    
}

void AllEntities::loadFile()
{
    
}

void AllEntities::loadNew()
{
    
}

void AllEntities::addEntity(Entity* newEntity)
{
    newEntity->adaptToModificators();
    entityList.push_back(newEntity);
}

void AllEntities::deleteEntity(Entity* toDelete)
{
    entityList.remove(toDelete);
}

Entity* AllEntities::getPlayer() const {
    return player;
}

void AllEntities::deleteDead()
{
    std::list<Entity*>::iterator i = entityList.begin();
    while (i != entityList.end())
    {
        Entity *toDelete = *i;
        if (toDelete->getHealth() <= 0)
        {
            toDelete->executeAgony();
            if(toDelete == player)Variables::status = END;
            if(toDelete->isProjectile() == false)Variables::session->getMap()->getCurrentModule()
                ->getModuleTileAt(toDelete->getCoords()->X,toDelete->getCoords()->Y)
                ->deleteFromEntityList(toDelete);
            entityList.erase(i++);
            delete toDelete;
        }
        i++;
    }
}

void AllEntities::createObstacles()
{
    for(int i = 0; i < Variables::tilesPerRoom; i++)
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            bool isObstacle = (rand()%Variables::tileSize == 0);
            if(isObstacle && Variables::session->getMap()->getCurrentModule()->getModuleTileAt(i * Variables::tileSize, j * Variables::tileSize)->getObstacle() == NULL)
            {
                Entity *obstacle;
                if(rand()%5 == 0)obstacle = new ExplosiveBarrel(i * Variables::tileSize, j * Variables::tileSize, 0);
                else obstacle = new Obstacle(i * Variables::tileSize, j * Variables::tileSize);
                Variables::session->getMap()->getCurrentModule()->getModuleTileAt(i * Variables::tileSize, j * Variables::tileSize)->setObstacle(obstacle);
                this->addEntity(obstacle);
            }
        }
}

void AllEntities::addRemoteCharge(Entity* toAdd)
{
    templateList<Entity> *newCharge = new templateList<Entity>();
    newCharge->data = toAdd;
    newCharge->next = remoteCharges;
    remoteCharges = newCharge;
    addEntity(toAdd);
}

bool AllEntities::deleteRemoteCharge(int signalId)
{
    bool result = false;
    templateList<Entity> *temp = remoteCharges;
    while(temp != NULL)
    {
        if(dynamic_cast<RemoteCharges*>(temp->data)->getSignalId() == signalId)
        {
            result = true;
            templateList<Entity> *toDelete = temp;
            temp = temp->next;
            if(temp != remoteCharges) { remoteCharges->findPrevious(toDelete->data)->next = temp; }
            toDelete->data->executeAgony();
            deleteEntity(toDelete->data);
        }
        else temp = temp->next;
    }
    return result;
}

void AllEntities::applyModifiers()
{
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
        temp->adaptToModificators();
    }
}

void AllEntities::setPlayer(Entity* player) {
    this->player = player;
}