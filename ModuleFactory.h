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
    void static setTransferBlocks(Module *module, int side);
private:
    void setModuleBasicFloor(Module * module);
    void setModuleRooms(Module *module);
    int **createTiles();
    int *roomCount;
};

#endif	/* MODULEFACTORY_H */

