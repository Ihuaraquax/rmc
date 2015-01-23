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
                    leftWall->wallSize = wallSize;
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
                    rightWall->wallSize = wallSize;
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
                    upperWall->wallSize = wallSize;
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
                    lowerWall->wallSize = wallSize;
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