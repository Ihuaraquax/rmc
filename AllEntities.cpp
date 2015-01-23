/* 
 * File:   AllEntities.cpp
 * Author: Qb
 * 
 * Created on 16 listopad 2014, 11:31
 */

#include "AllEntities.h"
#include "Player.h"
#include "Monster.h"
#include "globalVariables.h"
#include <iostream>
  
AllEntities::AllEntities() {
    player = new Player();
    entityList.push_back(player);
    for(int i = 0; i < 10; i++)
    {
        Entity *monster = new Monster();
        entityList.push_back(monster);
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
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
        temp->update();
    }
    deleteDead();
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
        if (toDelete->getHealth()==0)
        {
            if(toDelete->isProjectile() == false)Variables::session->getMap()->getCurrentModule()
                ->getModuleTileAt(toDelete->getCoords()->X,toDelete->getCoords()->Y)
                ->deleteFromEntityList(toDelete);
            entityList.erase(i++);
            delete toDelete;
        }
        i++;
    }
}

void AllEntities::setStartingTile()
{
    for(std::list<Entity*>::iterator i = entityList.begin(); i != entityList.end(); ++i)
    {
        Entity *temp = *i;
//        temp->setStartingTile();
    }
}