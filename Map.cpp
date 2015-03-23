/* 
 * File:   Map.cpp
 * Author: Qb
 * 
 * Created on 24 listopad 2014, 18:42
 */

#include <list>

#include "Map.h"
#include "ModuleFactory.h"
#include "Player.h"

Map::Map() {
    modulesTableSize = 3;
    moduleX = 1;
    moduleY = 1;
    
    
    modules = new Module**[modulesTableSize];
    allEntities = new AllEntities**[modulesTableSize];
    for(int i = 0; i < modulesTableSize; i++)
    {
        allEntities[i] = new AllEntities*[modulesTableSize];
        modules[i] = new Module*[modulesTableSize];
        for(int j = 0; j < modulesTableSize; j++)
        {
            modules[i][j] = NULL;
            allEntities[i][j] = new AllEntities();
        }
    }
}

Map::~Map()
{
    for(int i = 0; i < modulesTableSize; i++)
    {
        for(int j = 0; j < modulesTableSize; j++)
        {
            if(allEntities[i][j] != NULL)delete allEntities[i][j];
            if(modules[i][j] != NULL)delete modules[i][j];
        }
            
        delete []allEntities[i];
        delete []modules[i];
    }
    delete []allEntities;
    delete []modules;
}

void Map::createLevels()
{
    
    ModuleFactory factory;
    Module *newModule = new Module();
    currentAllEntities = allEntities[1][1];
    factory.setModuleBasics(newModule);
    modules[1][1] = newModule;
    currentModule = modules[1][1];
    allEntities[1][1]->init();
    allEntities[1][1]->applyModifiers();
    
    Module *newModule2 = new Module();
    currentAllEntities = allEntities[1][0];
    factory.setModuleBasics(newModule2);
    modules[1][0] = newModule2;
    currentModule = modules[1][0];
    allEntities[1][0]->init();
    allEntities[1][0]->applyModifiers();
    
    currentModule = modules[moduleX][moduleY];
    currentAllEntities = allEntities[moduleX][moduleY];
    
    Entity *player = new Player();
    currentAllEntities->setPlayer(player);
}

void Map::loadLevels()
{
    
}

void Map::display()
{
    currentModule->display();
    currentAllEntities->display();
}

void Map::update()
{
    currentModule->update();
    currentAllEntities->update();
}

Module* Map::getCurrentModule() const {
    return currentModule;
}

void Map::switchModule(int side)
{
    switch(side)
    {
        case 0: if(moduleY != 0) moduleY--;
            break;
        case 1: if(moduleX != modulesTableSize-1)moduleX++;
            break;
        case 2: if(moduleY != modulesTableSize-1)moduleY++;
            break;
        case 3: if(moduleX != 0) moduleX--;
            break;
    }
    if(currentModule != modules[moduleX][moduleY])
    {
        allEntities[moduleX][moduleY]->setPlayer(currentAllEntities->getPlayer());
        currentModule = modules[moduleX][moduleY];
        currentAllEntities = allEntities[moduleX][moduleY];
    }
}

AllEntities* Map::getCurrentAllEntities() const {
    return currentAllEntities;
}