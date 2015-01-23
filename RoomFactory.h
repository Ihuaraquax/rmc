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
    static Room **createRooms(int roomCount, int **tiles);
private:
    static void getRoomSeedCoords(int &X, int &Y, int **tileTable, int roomBaseTile);
    static bool roomsAreMaxed(Room **rooms, int roomCount);
    static void addZeroToRooms(int **tileTable, Room **rooms);
    static int zerosCount(int **tileTable);
};

#endif	/* ROOMFACTORY_H */

