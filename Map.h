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
#include <fstream>

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
    
    void save(std::fstream &file);
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

