/* 
 * File:   Map.h
 * Author: Qb
 *
 * Created on 24 listopad 2014, 18:42
 */

#ifndef MAP_H
#define	MAP_H
#include "Module.h"

class Map {
public:
    Map();
    ~Map();
    void createLevels();
    void loadLevels();
    
    void display();
    void update();
    Module* getCurrentModule() const;    
private:
    std::list<Module*> modules;
    Module *currentModule;
};

#endif	/* MAP_H */

