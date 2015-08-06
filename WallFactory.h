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
    void  setObstacleWalls(Module *module, int roomCount, Room **rooms, int **tiles);
    void  setModuleBasicWalls(Module * module);
    void  deleteSingleWalls();
    void  addHoleWalls();
    void  generateCorners();
    void  generateWalls();
private:
    bool  isValidTile(int X,int Y, int **fieldTable, int roomTileID);
    std::list<Wall*>  getRoomWall(Room *room, int **fieldTable);
    std::list<Door*>  getDoors();
    int **temp;
};

#endif	/* WALLFACTORY_H */

