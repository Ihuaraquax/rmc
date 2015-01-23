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
    void setModuleBasicWalls(Module * module);
    void setModuleRooms(Module *module);
    void getRoomSeedCoords(int &X, int &Y, int **tileTable, int roomBaseTile);
    bool roomsAreMaxed(Room **rooms, int roomCount);
    void addZeroToRooms(int **tileTable, Room **rooms);
    int zerosCount(int **tileTable);
    void  addNeighboursToTile(int tileNo, ModuleTile** moduleTiles);
    bool isCorrect(int X, int Y);
    ModuleTile *getTile(int X, int Y, ModuleTile** moduleTiles);
};

#endif	/* MODULEFACTORY_H */

