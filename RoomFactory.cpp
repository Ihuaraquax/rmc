/* 
 * File:   RoomFactory.cpp
 * Author: Qb
 * 
 * Created on 21 styczeń 2015, 21:33
 */

#include "RoomFactory.h"
#include "globalVariables.h"

RoomFactory::RoomFactory() {
}

Room **RoomFactory::createRooms(int roomCount, int **tiles, int roomId)
{
    Room **rooms = new Room*[roomCount];
    int **residualTiles = new int*[Variables::tilesPerRoom];
    for(int i = 0; i < Variables::tilesPerRoom; i++)
    {
        residualTiles[i] = new int[Variables::tilesPerRoom];
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            residualTiles[i][j] = tiles[i][j];
        }
    }
    for(int i = 0; i < roomCount; i++)
    {
        int X, Y;
        getRoomSeedCoords(X,Y, tiles, roomId);
        tiles[X][Y] = roomId+i+1;
        rooms[i] = new Room(X,Y,BASIC_ROOM, roomId, roomId+i+1);
    }
    while(!roomsAreMaxed(tiles, roomId))
    {
        growRooms(roomCount, tiles, rooms, residualTiles);
        translateArrays(tiles, residualTiles);
        al_clear_to_color(al_map_rgb(0,0,0));
        for(int i = 0; i < roomCount; i++)rooms[i]->display();
        al_flip_display();
    }
    return rooms;
}

void RoomFactory::growRooms(int roomCount, int **tiles, Room **rooms, int **residualTiles)
{
    for(int i = 0; i < Variables::tilesPerRoom; i++)
    {
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            if(tiles[i][j] != -100 && tiles[i][j] % 10 == 0){
                int adjacentRoom = isTileAdjacentToRoom(tiles, i, j);
                int roomId = -1;
                for(int index = 0; index < roomCount; index++){
                    if(rooms[index]->getRoomTile() == adjacentRoom)roomId = index;
                }
                if(adjacentRoom >= 0){
                    rooms[roomId]->addToTiles(i,j);
                }
                if(adjacentRoom != -1){
                    residualTiles[i][j] = adjacentRoom;
                }
            }
        }
    }
}

void RoomFactory::translateArrays(int **tiles, int **residualTiles)
{
    for(int i = 0; i < Variables::tilesPerRoom; i++)
    {
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            tiles[i][j] = residualTiles[i][j];
        }
    }
}

int RoomFactory::isTileAdjacentToRoom(int **tiles, int X, int Y)
{
    int result = -1;
    int temp = 0;
    int roomBaseId = tiles[X][Y];
    if(X > 0)
    {
        int leftTile = tiles[X-1][Y];
        if(leftTile / 10 == roomBaseId && leftTile %10 != 0)
        {
            if(result != leftTile)temp++;
            result = leftTile;
        }
    }
    if(Y > 0)
    {        
        int upTile = tiles[X][Y-1];
        if(upTile / 10 == roomBaseId && upTile %10 != 0)
        {
            if(result != upTile)temp++;
            result = upTile;
        }
    }
    if(X < Variables::tilesPerRoom-1)
    {
        int rightTile = tiles[X+1][Y];
        if(rightTile / 10 == roomBaseId && rightTile %10 != 0)
        {
            if(result != rightTile)temp++;
            result = rightTile;
        }
    }
    if(Y < Variables::tilesPerRoom-1)
    {
        int downTile = tiles[X][Y+1];
        if(downTile / 10 == roomBaseId && downTile %10 != 0)
        {
            if(result != downTile)temp++;
            result = downTile;
        }
    }
//    if(temp > 1)result = -100;
    return result;
}

void RoomFactory::getRoomSeedCoords(int& X, int& Y, int **tileTable, int roomBaseTile)
{
    bool isInvalid = true;
    do
    {
        X = rand()%Variables::tilesPerRoom;
        Y = rand()%Variables::tilesPerRoom;
        if(tileTable[X][Y] == roomBaseTile)isInvalid = false;
    }while(isInvalid);
}

bool RoomFactory::roomsAreMaxed(int **tiles, int roomId)
{
    bool value = true;
    for(int i = 0; i < Variables::tilesPerRoom; i++)
    {
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            if(tiles[i][j] == -1 || (tiles[i][j] >= 0 && tiles[i][j] % 10 == 0) && tiles[i][j] / 10 == roomId){
                value = false;
            }
        }
    }
    return value;
}

void RoomFactory::addZeroToRooms(int** tileTable, Room **rooms)
{
    while(zerosCount(tileTable) > 0)
    {
        for(int i = 0; i < Variables::tilesPerRoom; i++)
            for(int j = 0; j < Variables::tilesPerRoom; j++)
            {
                if(tileTable[i][j] == 0)
                {
                    if(i > 0 && tileTable[i-1][j])
                    {
                        tileTable[i][j] = tileTable[i-1][j];
                        rooms[tileTable[i][j]]->addToTiles(i,j);
                    }
                    else if(j > 0 && tileTable[i][j-1])
                    {
                        tileTable[i][j] = tileTable[i][j-1];
                        rooms[tileTable[i][j]]->addToTiles(i,j);
                    }
                    else if(i < Variables::tilesPerRoom-1 && tileTable[i+1][j])
                    {
                        tileTable[i][j] = tileTable[i+1][j];
                        rooms[tileTable[i][j]]->addToTiles(i,j);
                    }
                    else if(j < Variables::tilesPerRoom-1 && tileTable[i][j+1])
                    {
                        tileTable[i][j] = tileTable[i][j+1];
                        rooms[tileTable[i][j]]->addToTiles(i,j);
                    }
                }
            }
    }
}

int RoomFactory::zerosCount(int** tileTable)
{
    int value = 0;
    for(int i = 0; i < Variables::tilesPerRoom; i++)
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            if(tileTable[i][j] == 0)value++;
        }
    return value;
}