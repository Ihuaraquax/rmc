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

WallFactory::WallFactory() {
}

void WallFactory::setTileBarriers(Module* module, int roomCount, Room **rooms, int **tiles)
{
    setModuleBasicWalls(module);
    
    for(int i = 1; i < roomCount; i++)
    {
        std::list<Wall*> wallList = getRoomWall(rooms[i], tiles);
        for(std::list<Wall*>::iterator i = wallList.begin(); i != wallList.end(); ++i)
        {
            Wall *temp = *i;
            module->walls.push_back(temp);
        }
        std::list<Door*> doorList = getDoors();
        for(std::list<Door*>::iterator i = doorList.begin(); i != doorList.end(); ++i)
        {
            Door *temp = *i;
            module->doors.push_back(temp);
        }
    }
}

std::list<Wall*> WallFactory::getRoomWall(Room* room, int **fieldTable)
{
    std::list<Wall*> wallList;
    bool first = true;
    for(int i = 0; i < room->tileTableSize; i++)
    {
        int x = room->tilesX[i];
        int y = room->tilesY[i];
        
        Wall *leftWall = isValidTile(x-1,y,fieldTable, room->roomTile);
        Wall *rightWall = isValidTile(x+1,y,fieldTable, room->roomTile);
        Wall *upperWall = isValidTile(x,y-1,fieldTable, room->roomTile);
        Wall *lowerWall = isValidTile(x,y+1,fieldTable, room->roomTile);
        
        int wallSize = 50;
        
        if(leftWall != NULL)
        {
            Coordinates *coords = new Coordinates();
            coords->X = x * wallSize;
            coords->Y = y * wallSize;
            coords->width = 2;
            coords->height = wallSize;
            if(isTaken(coords) == false)
            {
                int isDoor = rand()%10;
                if(isDoor == 0 || first)
                {
                    Door *newDoor = new Door(coords);
                    doors.push_back(newDoor);
                    first = false;
                }
                else 
                {
                    leftWall->setCoords(coords);
                    leftWall->setWallSize(wallSize);
                    wallList.push_back(leftWall);
                    walls.push_back(leftWall);
                }
            }
        }
        if(rightWall != NULL)
        {
            Coordinates *coords = new Coordinates();
            coords->X = (x+1) * wallSize;
            coords->Y = y * wallSize;
            coords->width = 2;
            coords->height = wallSize;
            
            if(isTaken(coords) == false)
            {
                int isDoor = rand()%10;
                if(isDoor == 0 || first)
                {
                    Door *newDoor = new Door(coords);
                    doors.push_back(newDoor);
                    first = false;
                }
                else 
                {
                    rightWall->setCoords(coords);
                    rightWall->setWallSize(wallSize);
                    wallList.push_back(rightWall);
                    walls.push_back(rightWall);
                }
            }
        }
        if(upperWall != NULL)
        {
            Coordinates *coords = new Coordinates();
            coords->X = x * wallSize;
            coords->Y = y * wallSize;
            coords->width = wallSize;
            coords->height = 2;
            
            if(isTaken(coords) == false)
            {
                int isDoor = rand()%10;
                if(isDoor == 0 || first)
                {
                    Door *newDoor = new Door(coords);
                    doors.push_back(newDoor);
                    first = false;
                }
                else 
                {
                    upperWall->setCoords(coords);
                    upperWall->setWallSize(wallSize);
                    wallList.push_back(upperWall);
                    walls.push_back(upperWall);
                }
            }
        }
        if(lowerWall != NULL)
        {
            Coordinates *coords = new Coordinates();
            coords->X = x * wallSize;
            coords->Y = (y+1) * wallSize;
            coords->width = wallSize;
            coords->height = 2;
            
            if(isTaken(coords) == false)
            {
                int isDoor = rand()%10;
                if(isDoor == 0 || first)
                {
                    Door *newDoor = new Door(coords);
                    doors.push_back(newDoor);
                    first = false;
                }
                else 
                {
                    lowerWall->setCoords(coords);
                    lowerWall->setWallSize(wallSize);
                    wallList.push_back(lowerWall);
                    walls.push_back(lowerWall);
                }
            }
        }
        
    }
    
    return wallList;
}

Wall* WallFactory::isValidTile(int X, int Y, int **fieldTable, int roomTileID)
{
    int const MAX_FIELD_SIZE = Variables::tilesPerRoom-1;    
    Wall *wall = NULL;
    
    if(X >= 0 && X <= MAX_FIELD_SIZE && Y >= 0 && Y <= MAX_FIELD_SIZE)
    {
        if(fieldTable[X][Y] != roomTileID)wall = new Wall();
    }
    
    return wall;
}

std::list<Door*> WallFactory::getDoors()
{
    return doors;
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
        coords1->Y = 50 * i;
        coords1->height = 50;
        coords1->width = 2;
        Coordinates *coords2 = new Coordinates();
        coords2->X = 50 * i;
        coords2->Y = 0;
        coords2->height = 2;
        coords2->width = 50;
        Coordinates *coords3 = new Coordinates();
        coords3->X = 1000;
        coords3->Y = 50 * i;
        coords3->height = 50;
        coords3->width = 2;
        Coordinates *coords4 = new Coordinates();
        coords4->X = 50 * i;
        coords4->Y = 1000;
        coords4->height = 2;
        coords4->width = 50;
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