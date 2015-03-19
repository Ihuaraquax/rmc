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
#include "Chest.h"
#include "AllDecals.h"

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
    ModuleTile** getModuleTiles() const;
    
    void useChest();
    AllDecals* getAllDecals() const;
private:
    void resetTileAiValues(int X, int Y);
    void displayModuleTileAI();
    void displayModuleThreatLevel();
    void displayObstacles();
    std::list<Wall*> walls;
    std::list<Door*> doors;
    std::list<Floor*> floorTiles;
    std::list<Chest*> chests;
    ModuleTile **moduleTiles;
    
    int getModuleIndex(int X, int Y);
    void displayBuffs();
    AllDecals *allDecals;
};

#endif	/* MODULE_H */

