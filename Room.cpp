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

void Room::display(int green)
{
    for(int i = 0; i < tileTableSize; i++)
    {
        int X = (tilesX[i] * Variables::tileSize) - Variables::offsetX;
        int Y = (tilesY[i] * Variables::tileSize) - Variables::offsetY;
        switch(green){
            case 1:al_draw_filled_rectangle(X+5, Y+5, X+45, Y+45, al_map_rgb(255,0,255));
                break;
            case 2:al_draw_filled_rectangle(X+5, Y+5, X+45, Y+45, al_map_rgb(0,255,255));
                break;
            case 3:al_draw_filled_rectangle(X+5, Y+5, X+45, Y+45, al_map_rgb(30,30,30));
                break;
            case 4:al_draw_filled_rectangle(X+5, Y+5, X+45, Y+45, al_map_rgb(255,255,255));
                break;
            case 5:al_draw_filled_rectangle(X+5, Y+5, X+45, Y+45, al_map_rgb(255,255,0));
                break;
        }
    }
}

void Room::grow(int **tileTable)
{
    if(!maxed)
       {
        bool tileTaken = false;
        int tile = rand()%tileTableSize;
        int repetitionCheck = tile;
        
        while(tileTaken == false)
        {
            int X = tilesX[tile];
            int Y = tilesY[tile];
            if(isValidTile(X,Y, tileTable))tileTaken = true;
            else
            {
                tile++;
                tile %= tileTableSize;
                if(tile == repetitionCheck || tileTableSize == 1)
                {
                    tileTaken = true;
                    maxed = true;
                }
            }
        }
    }
}

bool Room::isValidTile(int X, int Y, int **tileTable)
{
    bool value = false;
    
    int const MAX_FIELD_SIZE = Variables::tilesPerRoom-1;
    
    if(value == false && X > 0)
    {
        if(tileTable[X-1][Y] == this->baseTile) 
        {
            tileTable[X-1][Y] = this->roomTile;
            value = true;
            addToTiles(X-1,Y);
        }
    }
    
    if(value == false && X < MAX_FIELD_SIZE)
    {
        if(tileTable[X+1][Y] == this->baseTile) 
        {
            tileTable[X+1][Y] = this->roomTile;
            value = true;
            addToTiles(X+1,Y);
        }
    }
    if(value == false && Y > 0)
    {
        if(tileTable[X][Y-1] == this->baseTile) 
        {
            tileTable[X][Y-1] = this->roomTile;
            value = true;
            addToTiles(X,Y-1);
        }
    }
    if(value == false && Y < MAX_FIELD_SIZE)
    {
        if(tileTable[X][Y+1] == this->baseTile) 
        {
            tileTable[X][Y+1] = this->roomTile;
            value = true;
            addToTiles(X,Y+1);
        }
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