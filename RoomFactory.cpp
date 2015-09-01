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
    for(int i = 0; i < roomCount; i++)
    {
        int X, Y;
        getRoomSeedCoords(X,Y, tiles, roomId);
        tiles[X][Y] = roomId+i;
        rooms[i] = new Room(X,Y,BASIC_ROOM, roomId, roomId+i+1);
    }
    while(!roomsAreMaxed(rooms, roomCount))
    {
        al_clear_to_color(al_map_rgb(0,0,0));
        for(int i = 0; i < roomCount; i++)rooms[i]->grow(tiles);
        for(int i = 0; i < roomCount; i++)rooms[i]->display();
        al_flip_display();
        Sleep(3);
    }
    return rooms;
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

bool RoomFactory::roomsAreMaxed(Room** rooms, int roomCount)
{
    bool value = false;
    if(roomCount == 0)value = true;
    for(int i = 0; i < roomCount; i++)
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