/* 
 * File:   WallFactory.cpp
 * Author: Qb
 * 
 * Created on 25 listopad 2014, 19:06
 */

#include <list>

#include "WallFactory.h"
#include "Coordinates.h"
#include "globalVariables.h"
#include "Obstacle.h"

WallFactory::WallFactory() {
}


bool WallFactory::isValidTile(int X, int Y, int **fieldTable, int roomTileID)
{
    int const MAX_FIELD_SIZE = Variables::tilesPerRoom-1;    
    bool result = false;
    
    if(X >= 0 && X <= MAX_FIELD_SIZE && Y >= 0 && Y <= MAX_FIELD_SIZE)
    {
        if(fieldTable[X][Y] != roomTileID)result = true;
    }
    
    return result;
}

bool WallFactory::isTaken(Coordinates* coords)
{
    bool result = false;
    for(std::list<Door*>::iterator i = doors.begin(); i != doors.end(); ++i)
    {
        Door* door = *i;
        Coordinates *temp =door->getCoords();
        if(temp->X == coords->X && temp->Y == coords->Y && 
           temp->height == coords->height && temp->width == coords->width)
                result = true;
        if(result)break;
    }
    for(std::list<Wall*>::iterator i = walls.begin(); i != walls.end(); ++i)
    {
        Wall* wall = *i;
        Coordinates *temp =wall->getCoords();
        if(temp->X == coords->X && temp->Y == coords->Y && 
           temp->height == coords->height && temp->width == coords->width)
                result = true;
        if(result)break;
    }
    return result;
}

void WallFactory::setModuleBasicWalls(Module* module)
{
    for(int i = 0; i < Variables::tilesPerRoom; i++)
    {
        Coordinates *coords1 = new Coordinates();
        coords1->X = 0;
        coords1->Y = Variables::tileSize * i;
        coords1->height = Variables::tileSize;
        coords1->width = 2;
        Coordinates *coords2 = new Coordinates();
        coords2->X = Variables::tileSize * i;
        coords2->Y = 0;
        coords2->height = 2;
        coords2->width = Variables::tileSize;
        Coordinates *coords3 = new Coordinates();
        coords3->X = Variables::tileSize * Variables::tilesPerRoom;
        coords3->Y = Variables::tileSize * i;
        coords3->height = Variables::tileSize;
        coords3->width = 2;
        Coordinates *coords4 = new Coordinates();
        coords4->X = Variables::tileSize * i;
        coords4->Y = Variables::tileSize * Variables::tilesPerRoom;
        coords4->height = 2;
        coords4->width = Variables::tileSize;
        Wall *wall1 = new Wall();
        wall1->setCoords(coords1);
        Wall *wall2 = new Wall();
        wall2->setCoords(coords2);
        Wall *wall3 = new Wall();
        wall3->setCoords(coords3);
        Wall *wall4 = new Wall();
        wall4->setCoords(coords4);
        wall1->setAsModuleBorderWall();
        wall2->setAsModuleBorderWall();
        wall3->setAsModuleBorderWall();
        wall4->setAsModuleBorderWall();
        module->walls.push_back(wall1);
        module->walls.push_back(wall2);
        module->walls.push_back(wall3);
        module->walls.push_back(wall4);
    }
}

void WallFactory::setObstacleWalls(Module* module, int roomCount, Room** rooms, int** tiles)
{
    setModuleBasicWalls(module);
    bool first = true;
    for(int j = 1; j < roomCount; j++)
    {
        Room *room = rooms[j];
        for(int i = 0; i < room->tileTableSize; i++)
        {
            int x = room->tilesX[i];
            int y = room->tilesY[i];

            if(isValidTile(x-1,y,tiles, room->roomTile) ||
               isValidTile(x+1,y,tiles, room->roomTile) ||
               isValidTile(x,y-1,tiles, room->roomTile) ||
               isValidTile(x,y+1,tiles, room->roomTile))
            {
                Entity *wall = new Obstacle(x * Variables::tileSize, y * Variables::tileSize);
                dynamic_cast<Obstacle*>(wall)->setAsWall();
                Variables::session->getAllEntities()->addEntity(wall);
            }
        }
    }
}