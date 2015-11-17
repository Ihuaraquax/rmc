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
    void  setObstacleWalls(int **tiles);
    void  setModuleBasicWalls(Module * module);
    void  deleteSingleWalls();
    void  addHoleWalls();
    void  generateCorners();
    void  generateWalls();
    void  deleteThickWalls();
private:
    std::list<Wall*>  getRoomWall(Room *room, int **fieldTable);
    std::list<Door*>  getDoors();
    int **temp;
};

#endif	/* WALLFACTORY_H */

