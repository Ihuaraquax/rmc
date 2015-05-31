/* 
 * File:   Map.h
 * Author: Qb
 *
 * Created on 24 listopad 2014, 18:42
 */

#ifndef MAP_H
#define	MAP_H
#include "Module.h"
#include "AllEntities.h"
#include "AllLightSources.h"
#include <fstream>

class Map {
public:
    Map();
    ~Map();
    void init(int size);
    void createLevels();
    void setTransferBlocks();
    void loadLevels();
    
    void display();
    void displayPlan();
    void setPlanCoords();
    void update();
    Module* getCurrentModule() const;
    void switchModule(int side);
    AllEntities* getCurrentAllEntities() const;
    
    void save(std::fstream &file);
    void load(std::fstream &file);
    void setOffest();
    int getModuleY() const;
    int getModuleX() const;
    int getModulesTableSize() const;
    AllLightSources* getAllLightSources() const;
    void displayLight();
private:
    Module ***modules;
    AllEntities ***allEntities;
    Module *currentModule;
    AllEntities *currentAllEntities;
    int modulesTableSize;
    int moduleX;
    int moduleY;
};

#endif	/* MAP_H */

