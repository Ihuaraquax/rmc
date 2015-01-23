/* 
 * File:   Module.h
 * Author: Qb
 *
 * Created on 23 listopad 2014, 18:54
 */

#ifndef MODULE_H
#define	MODULE_H
#include "Wall.h"
#include "Door.h"
#include "Floor.h"
#include "Room.h"
#include "ModuleTile.h"

class Module {
friend class ModuleFactory;
public:
    Module();
    ~Module();
    void display();
    void update();
    void updateTileAiValue(int X, int Y);
    bool isObstructed(int X, int Y);
    ModuleTile *getModuleTileAt(int X, int Y);
    void addWallsToTiles();
    void addDoorsToTiles();
private:
    void resetTileAiValues(int X, int Y);
    void displayModuleTileAI();
    std::list<Wall*> walls;
    std::list<Door*> doors;
    std::list<Floor*> floorTiles;
    ModuleTile **moduleTiles;
};

#endif	/* MODULE_H */

