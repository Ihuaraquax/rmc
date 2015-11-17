/* 
 * File:   RoomFactory.h
 * Author: Qb
 *
 * Created on 21 styczeń 2015, 21:33
 */

#ifndef ROOMFACTORY_H
#define	ROOMFACTORY_H
#include "Room.h"

class RoomFactory {
public:
    RoomFactory();
    static Room **createRooms(int roomCount, int **tiles, int roomId);
private:
    static void getRoomSeedCoords(int &X, int &Y, int **tileTable, int roomBaseTile);
    static bool roomsAreMaxed(int **tiles, int roomId);
    static void addZeroToRooms(int **tileTable, Room **rooms);
    static int zerosCount(int **tileTable);
    static void growRooms(int roomCount, int **tiles, Room **rooms, int **residualTiles);
    static int isTileAdjacentToRoom(int **tiles, int X, int Y);
    static void translateArrays(int **tiles, int **residualTiles);
};

#endif	/* ROOMFACTORY_H */

