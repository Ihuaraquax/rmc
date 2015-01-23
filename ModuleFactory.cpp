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
#include "TileFactory.h"
#include "RoomFactory.h"

ModuleFactory::ModuleFactory() {
}

void ModuleFactory::setModuleBasics(Module* module)
{    
    setModuleBasicFloor(module);
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

void ModuleFactory::setModuleRooms(Module* module)
{
    int **tiles = createTiles();
    int roomCount = 5;
    
    Room **rooms = RoomFactory::createRooms(roomCount, tiles);    
    
    WallFactory factory;
    factory.setTileBarriers(module, roomCount, rooms, tiles);
    
    TileFactory::createModuleTiles(module, tiles);
    for(int i = 1; i < roomCount; i++)
    {
        delete rooms[i];
    }
    delete []rooms;
}

int **ModuleFactory::createTiles()
{
    int **tiles;
    tiles = new int*[Variables::tilesPerRoom];
    for(int i = 0; i < Variables::tilesPerRoom; i++)
    {
        tiles[i] = new int[Variables::tilesPerRoom];
        for(int j = 0; j < Variables::tilesPerRoom; j++)tiles[i][j] = 0;
    }
    return tiles;
}