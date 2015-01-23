/* 
 * File:   ModuleFactory.cpp
 * Author: Qb
 * 
 * Created on 24 listopad 2014, 19:02
 */

#include <list>

#include <iostream>
#include "ModuleFactory.h"
#include "WallFactory.h"
#include "Door.h"
#include "Wall.h"
#include "Floor.h"
#include "Coordinates.h"
#include "Image.h"
#include "globalVariables.h"

ModuleFactory::ModuleFactory() {
}

void ModuleFactory::setModuleBasics(Module* module)
{    
    setModuleBasicFloor(module);
    setModuleBasicWalls(module);
    setModuleRooms(module);
}

void ModuleFactory::setModuleBasicFloor(Module* module)
{
    Floor *floor = new Floor();
    Coordinates *coords = new Coordinates();
    coords->X = 0;
    coords->Y = 0;
    coords->height = 1000;
    coords->width = 1000;
    floor->setCoords(coords);
    std::string paths[1] = {"images/tile1.bmp"};
    Image *image = new Image(1, paths, false);
    image->state = REPEATING;
    floor->setImage(image);
    module->floorTiles.push_back(floor);
}

void ModuleFactory::setModuleBasicWalls(Module* module)
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
        module->walls.push_back(wall1);
        module->walls.push_back(wall2);
        module->walls.push_back(wall3);
        module->walls.push_back(wall4);
    }
}

void ModuleFactory::setModuleRooms(Module* module)
{
    int **tiles;
    int roomCount = 5;
    tiles = new int*[Variables::tilesPerRoom];
    for(int i = 0; i < Variables::tilesPerRoom; i++)
    {
        tiles[i] = new int[Variables::tilesPerRoom];
        for(int j = 0; j < Variables::tilesPerRoom; j++)tiles[i][j] = 0;
    }
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
    WallFactory factory;
    for(int i = 1; i < roomCount; i++)
    {
        std::list<Wall*> wallList = factory.getRoomWall(rooms[i], tiles);
        for(std::list<Wall*>::iterator i = wallList.begin(); i != wallList.end(); ++i)
        {
            Wall *temp = *i;
            module->walls.push_back(temp);
        }
        std::list<Door*> doorList = factory.getDoors();
        for(std::list<Door*>::iterator i = doorList.begin(); i != doorList.end(); ++i)
        {
            Door *temp = *i;
            module->doors.push_back(temp);
        }
    }
    
    module->moduleTiles = new ModuleTile*[Variables::tilesPerRoom * Variables::tilesPerRoom];
    for(int i = 0; i < Variables::tilesPerRoom; i++)
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            module->moduleTiles[i*Variables::tilesPerRoom + j] =
                    new ModuleTile(false, tiles[i][j],0);
        }
    module->addWallsToTiles();
    module->addDoorsToTiles();
    for(int i = 0; i < Variables::tilesPerRoom * Variables::tilesPerRoom; i++)
    {
        addNeighboursToTile(i,module->moduleTiles);
    }
    for(int i = 1; i < roomCount; i++)
    {
        delete rooms[i];
    }
    delete []rooms;
}

void ModuleFactory::getRoomSeedCoords(int& X, int& Y, int **tileTable, 
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

bool ModuleFactory::roomsAreMaxed(Room** rooms, int roomCount)
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

void ModuleFactory::addZeroToRooms(int** tileTable, Room **rooms)
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

int ModuleFactory::zerosCount(int** tileTable)
{
    int value = 0;
    for(int i = 0; i < Variables::tilesPerRoom; i++)
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            if(tileTable[i][j] == 0)value++;
        }
    return value;
}

void ModuleFactory::addNeighboursToTile(int tileNo, ModuleTile** moduleTiles)
{
    int X = tileNo / Variables::tilesPerRoom;
    int Y = tileNo % Variables::tilesPerRoom;
    int size = 0;
    ModuleTile **tileList = new ModuleTile*[8];
    if(isCorrect(X-1,Y-1))tileList[size++] = getTile(X-1,Y-1,moduleTiles);
    else tileList[size++] = NULL;
    if(isCorrect(X,Y-1))tileList[size++] = getTile(X,Y-1,moduleTiles);
    else tileList[size++] = NULL;
    if(isCorrect(X+1,Y-1))tileList[size++] = getTile(X+1,Y-1,moduleTiles);
    else tileList[size++] = NULL;
    if(isCorrect(X+1,Y))tileList[size++] = getTile(X+1,Y,moduleTiles);
    else tileList[size++] = NULL;
    if(isCorrect(X+1,Y+1))tileList[size++] = getTile(X+1,Y+1,moduleTiles);
    else tileList[size++] = NULL;
    if(isCorrect(X,Y+1))tileList[size++] = getTile(X,Y+1,moduleTiles);
    else tileList[size++] = NULL;
    if(isCorrect(X-1,Y+1))tileList[size++] = getTile(X-1,Y+1,moduleTiles);
    else tileList[size++] = NULL;
    if(isCorrect(X-1,Y))tileList[size++] = getTile(X-1,Y,moduleTiles);
    else tileList[size++] = NULL;
    moduleTiles[tileNo]->setAdjacentTilesCount(size);
    moduleTiles[tileNo]->setAdjacentTiles(tileList);
}

bool ModuleFactory::isCorrect(int X, int Y)
{
    bool value = true;
    if(X < 0 || X >= Variables::tilesPerRoom)value = false;
    if(Y < 0 || Y >= Variables::tilesPerRoom)value = false;
    return value;
}

ModuleTile *ModuleFactory::getTile(int X, int Y, ModuleTile** moduleTiles)
{
    int tileNo = X * Variables::tilesPerRoom + Y;
    return moduleTiles[tileNo];
}