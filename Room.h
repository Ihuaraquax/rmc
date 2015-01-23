/* 
 * File:   Room.h
 * Author: Qb
 *
 * Created on 23 listopad 2014, 18:54
 */

#ifndef ROOM_H
#define	ROOM_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

enum ROOM_TYPE
{
    BASIC_ROOM, ONE_ENTRY_CORRIDOR, JAIL_CELL, ARMORY, MEDBAY, SERVER_ROOM
};

class Room {
    friend class WallFactory;
public:
    Room(int X, int Y, ROOM_TYPE type, int baseTileId, int roomTileId);
    Room(const Room& orig);
    virtual ~Room();
    void grow(int **tileTable);
    void display(int green);
    bool isValidTile(int X, int Y, int **tileTable);
    bool isMaxed() const;
    void setTiles(int **tilesTable);
    void addToTiles(int X, int Y);
private:
    int baseTile;
    int *tilesX;
    int *tilesY;
    int tileTableSize;
    ROOM_TYPE roomType;
    int roomTile;
    bool maxed;
};

#endif	/* ROOM_H */

