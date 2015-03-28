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
    void static setObstacleWalls(Module *module, int roomCount, Room **rooms, int **tiles);
    void static setModuleBasicWalls(Module * module);
private:
    bool static isValidTile(int X,int Y, int **fieldTable, int roomTileID);
    std::list<Wall*> static getRoomWall(Room *room, int **fieldTable);
    std::list<Door*> static getDoors();
    void static deleteSingleWalls(int **temp);
    void static addHoleWalls(int **temp);
    void static generateCorners(int **temp);
    void static generateWalls(int **temp);
};

#endif	/* WALLFACTORY_H */

