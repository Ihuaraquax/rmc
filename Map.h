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

class Map {
public:
    Map();
    ~Map();
    void createLevels();
    void loadLevels();
    
    void display();
    void update();
    Module* getCurrentModule() const;
    void switchModule(int side);
    AllEntities* getCurrentAllEntities() const;
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

