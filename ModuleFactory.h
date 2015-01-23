/* 
 * File:   ModuleFactory.h
 * Author: Qb
 *
 * Created on 24 listopad 2014, 19:02
 */

#ifndef MODULEFACTORY_H
#define	MODULEFACTORY_H
#include "Module.h"
#include "ModuleTile.h"

class ModuleFactory {
public:
    ModuleFactory();
    void setModuleBasics(Module *module);
private:
    void setModuleBasicFloor(Module * module);
    void setModuleRooms(Module *module);
    int **createTiles();
};

#endif	/* MODULEFACTORY_H */

