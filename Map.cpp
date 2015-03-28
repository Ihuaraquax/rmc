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
    moduleX = 0;
    moduleY = 0;
    init(3);
}

void Map::init(int size)
{
    modulesTableSize = size;    
    
    modules = new Module**[modulesTableSize];
    allEntities = new AllEntities**[modulesTableSize];
    for(int i = 0; i < modulesTableSize; i++)
    {
        allEntities[i] = new AllEntities*[modulesTableSize];
        modules[i] = new Module*[modulesTableSize];
        for(int j = 0; j < modulesTableSize; j++)
        {
            modules[i][j] = new Module();
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
    
    for(int i = 0; i < modulesTableSize; i++)
    {
        for(int j = 0; j < modulesTableSize; j++)
        {
            currentAllEntities = allEntities[i][j];
            modules[i][j] = new Module();
            factory.setModuleBasics(modules[i][j]);
            currentModule = modules[i][j];
            allEntities[i][j]->init();
            allEntities[i][j]->applyModifiers();
        }
    }
    
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
    if(currentModule != modules[moduleY][moduleX])
    {
        allEntities[moduleY][moduleX]->setPlayer(currentAllEntities->getPlayer());
        currentModule = modules[moduleY][moduleX];
        currentAllEntities = allEntities[moduleY][moduleX];
    }
}

AllEntities* Map::getCurrentAllEntities() const {
    return currentAllEntities;
}

void Map::save(std::fstream& file)
{
    file << this->modulesTableSize << std::endl;
    for(int i = 0; i < this->modulesTableSize; i++)
    {
        for(int j = 0; j < this->modulesTableSize; j++)
        {
            this->modules[i][j]->save(file);
            this->allEntities[i][j]->save(file);
        }
    }
    file << "MC" << ' ' << moduleX  << ' ' << moduleY << std::endl;
    this->getCurrentAllEntities()->getPlayer()->save(file);
    file << std::endl;
}

void Map::load(std::fstream& file)
{
    file >> modulesTableSize;
    init(modulesTableSize);
    
    for(int i = 0; i < this->modulesTableSize; i++)
    {
        for(int j = 0; j < this->modulesTableSize; j++)
        {
            this->currentModule = modules[i][j];
            this->currentAllEntities = allEntities[i][j];
            this->modules[i][j]->load(file);
            this->allEntities[i][j]->load(file);
        }
    }
    std::string temp;
    file >> temp >> moduleX >> moduleY >> temp;
    currentModule = modules[moduleX][moduleY];
    currentAllEntities = allEntities[moduleX][moduleY];
    Entity *player = new Player(true);
    player->load(file);
    this->getCurrentAllEntities()->setPlayer(player);
}