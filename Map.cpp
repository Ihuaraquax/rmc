/* 
 * File:   Map.cpp
 * Author: Qb
 * 
 * Created on 24 listopad 2014, 18:42
 */

#include <list>

#include "Map.h"
#include "ModuleFactory.h"

Map::Map() {
}

Map::~Map()
{
    for(std::list<Module*>::iterator i = modules.begin(); i != modules.end(); ++i)
    {
        Module *temp = *i;
        delete temp;
    }
}

void Map::createLevels()
{
    ModuleFactory factory;
    Module *newModule = new Module();
    factory.setModuleBasics(newModule);
    modules.push_back(newModule);
    currentModule = newModule;
}

void Map::loadLevels()
{
    
}

void Map::display()
{
    currentModule->display();
}

void Map::update()
{
    currentModule->update();
}

Module* Map::getCurrentModule() const {
    return currentModule;
}

