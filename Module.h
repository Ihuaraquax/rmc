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
friend class TileFactory;
friend class WallFactory;
public:
    Module();
    ~Module();
    void display();
    void update();
    void updateTileAiTarget(int X, int Y);
    bool isObstructed(int X, int Y);
    ModuleTile *getModuleTileAt(int X, int Y);
    void addWallsToTiles();
    void addDoorsToTiles();
    void deleteWall(Wall *toDelete);
    void deleteDoor(Door *toDelete);
    int getIndexOfModule(ModuleTile *tile);
private:
    void resetTileAiValues(int X, int Y);
    void displayModuleTileAI();
    void displayModuleThreatLevel();
    void displayObstacles();
    void displayRoomBorders();
    std::list<Wall*> walls;
    std::list<Door*> doors;
    std::list<Floor*> floorTiles;
    ModuleTile **moduleTiles;
    
    int getModuleIndex(int X, int Y);
};

#endif	/* MODULE_H */

