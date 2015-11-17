/* 
 * File:   Room.cpp
 * Author: Qb
 * 
 * Created on 23 listopad 2014, 18:54
 */

#include <list>

#include <iostream>
#include <cstdlib>
#include "Room.h"
#include "globalVariables.h"

Room::Room(int X, int Y, ROOM_TYPE type, int baseTileId, int roomTileId) {
    tilesX = new int[Variables::tilesPerRoom*Variables::tilesPerRoom];
    tilesY = new int[Variables::tilesPerRoom*Variables::tilesPerRoom];
    tilesX[0] = X;
    tilesY[0] = Y;
    tileTableSize = 1;
    roomType = type;
    baseTile = baseTileId;
    maxed = false;
    roomTile = roomTileId;
}

Room::Room(const Room& orig) {
}

Room::~Room() {
}

void Room::grow(int **tileTable)
{
    if(!maxed)
    {
        maxed = true;
        int tileId = rand()%tileTableSize;
        for(int i = 0; i < tileTableSize; i++)
        {
            bool roomGrew = tryToGrow(tilesX[tileId],tilesY[tileId], tileTable);
            if(roomGrew)
            {
                maxed = false;
                break;
            }
            tileId++;
            tileId %= tileTableSize;
        }
    }
}

bool Room::isValidTile(int X, int Y, int **tileTable)
{
    bool value = true;
    if(X < 0)value = false;
    if(Y < 0)value = false;
    if(X > Variables::tilesPerRoom-1)value = false;
    if(Y > Variables::tilesPerRoom-1)value = false;
    if(value == true)if(tileTable[X][Y] != baseTile)value = false;
    return value;
}

bool Room::tryToGrow(int X, int Y, int **tileTable)
{
    bool value = false;
    if(value == false)if(isValidTile(X-1, Y, tileTable))
    {
        addToTiles(X-1,Y);
        tileTable[X-1][Y] = this->roomTile;
        value = true;
    }
    if(value == false)if(isValidTile(X, Y-1, tileTable))
    {
        addToTiles(X,Y-1);
        tileTable[X][Y-1] = this->roomTile;
        value = true;
    }
    if(value == false)if(isValidTile(X+1, Y, tileTable))
    {
        addToTiles(X+1,Y);
        tileTable[X+1][Y] = this->roomTile;
        value = true;
    }
    if(value == false)if(isValidTile(X, Y+1, tileTable))
    {
        addToTiles(X,Y+1);
        tileTable[X][Y+1] = this->roomTile;
        value = true;
    }
    return value;
}

bool Room::isMaxed() const {
    return maxed;
}

void Room::setTiles(int** tilesTable)
{
    for(int i = 0; i < tileTableSize; i++)
    {
        tilesTable[tilesX[i]][tilesY[i]] = roomTile;
    }
}

void Room::addToTiles(int X, int Y)
{
    tilesX[tileTableSize] = X;
    tilesY[tileTableSize] = Y;
    tileTableSize++;
}

void Room::display()
{
    int color = (roomTile%10 + 1) *50;
    for(int i = 0; i < tileTableSize; i++)
    {
        double X = tilesX[i] * 30;
        double Y = tilesY[i] * 30;
        al_draw_filled_rectangle(X, Y, X+50, Y + 50, al_map_rgb(color,color,color));
    }
}

int Room::getRoomTile() const {
    return roomTile;
}