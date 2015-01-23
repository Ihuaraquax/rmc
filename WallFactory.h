/* 
 * File:   WallFactory.h
 * Author: Qb
 *
 * Created on 25 listopad 2014, 19:06
 */

#ifndef WALLFACTORY_H
#define	WALLFACTORY_H
#include "Room.h"
#include "Wall.h"
#include "Door.h"
#include "Module.h"

class WallFactory {
public:
    WallFactory();
    void setTileBarriers(Module *module, int roomCount, Room **rooms, int **tiles);
private:
    Wall* isValidTile(int X,int Y, int **fieldTable, int roomTileID);
    bool isTaken(Coordinates *coords);
    std::list<Wall*> getRoomWall(Room *room, int **fieldTable);
    std::list<Door*> getDoors();
    void setModuleBasicWalls(Module * module);
    
    std::list<Door*> doors;
    std::list<Wall*> walls;
};

#endif	/* WALLFACTORY_H */

