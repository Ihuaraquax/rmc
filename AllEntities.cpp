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
    player = new Player();
    entityList.push_back(player);
    createDoors();
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
    Entity *barrel = new ExplosiveBarrel(150, 200, 0);
    this->addEntity(barrel);
}

void AllEntities::createDoors()
{
    for(int i = 1; i < Variables::tilesPerRoom - 1; i++)
        for(int j = 1; j < Variables::tilesPerRoom - 1; j++)
        {
            ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTiles()[i * Variables::tilesPerRoom + j];
            if(tile->getObstacle() != NULL)
            {
                if(tile->getAdjacentTiles()[7]->getObstacle() == NULL && tile->getAdjacentTiles()[3]->getObstacle() != NULL &&
                   tile->getAdjacentTiles()[3]->getAdjacentTiles()[3] != NULL && tile->getAdjacentTiles()[3]->getAdjacentTiles()[3]->getObstacle() == NULL)if(rand()% 15 == 0)
                {
                    this->deleteEntity(tile->getObstacle());
                    this->deleteEntity(tile->getAdjacentTiles()[3]->getObstacle());
                    
                    tile->deleteFromEntityList(tile->getObstacle());
                    tile->getAdjacentTiles()[3]->deleteFromEntityList(tile->getAdjacentTiles()[3]->getObstacle());
                    Entity *door = new ObstacleDoor(i * Variables::tileSize, j * Variables::tileSize);
                    this->addEntity(door);
                    dynamic_cast<ObstacleDoor*>(door)->setAngle(true);
                }
                if(tile->getAdjacentTiles()[1]->getObstacle()== NULL && tile->getAdjacentTiles()[5]->getObstacle() != NULL &&
                   tile->getAdjacentTiles()[5]->getAdjacentTiles()[5] != NULL && tile->getAdjacentTiles()[5]->getAdjacentTiles()[5]->getObstacle() == NULL)if(rand()% 15 == 0)
                {
                    this->deleteEntity(tile->getObstacle());
                    this->deleteEntity(tile->getAdjacentTiles()[5]->getObstacle());
                    
                    tile->deleteFromEntityList(tile->getObstacle());
                    tile->getAdjacentTiles()[5]->deleteFromEntityList(tile->getAdjacentTiles()[5]->getObstacle());
                    Entity *door = new ObstacleDoor(i * Variables::tileSize, j * Variables::tileSize);
                    this->addEntity(door);
                    dynamic_cast<ObstacleDoor*>(door)->setAngle(false);
                }
            }
        }
    
}

AllEntities::~AllEntities()
{
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
        delete temp;
    }
}


void AllEntities::display()
{
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
        temp->display();
    }
}

void AllEntities::update()
{
    if(Variables::log == full)std::cout << " AllEntities Update ";
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
        temp->update();
    }
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
                Entity *obstacle = new Obstacle(i * Variables::tileSize, j * Variables::tileSize);
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