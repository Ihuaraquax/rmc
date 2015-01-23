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

Room **RoomFactory::createRooms(int roomCount, int **tiles)
{
    Room **rooms = new Room*[roomCount];
    for(int i = 1; i < roomCount; i++)
    {
        int X, Y;
        getRoomSeedCoords(X,Y, tiles, 0);
        tiles[X][Y] = i;
        rooms[i] = new Room(X,Y,BASIC_ROOM, 0, i);
    }
    while(!roomsAreMaxed(rooms, roomCount))
    {
        for(int i = 1; i < roomCount; i++)rooms[i]->grow(tiles);
    }
    addZeroToRooms(tiles, rooms);
    return rooms;
}

void RoomFactory::getRoomSeedCoords(int& X, int& Y, int **tileTable, 
        int roomBaseTile)
{
    bool isInvalid = true;
    do
    {
        X = rand()%Variables::tilesPerRoom;
        Y = rand()%Variables::tilesPerRoom;
        if(tileTable[X][Y] == roomBaseTile)isInvalid = false;
    }while(isInvalid);
}

bool RoomFactory::roomsAreMaxed(Room** rooms, int roomCount)
{
    bool value = false;
    for(int i = 1; i < roomCount; i++)
    {
        if(rooms[i]->isMaxed())
        {
            value = true;
            break; 
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