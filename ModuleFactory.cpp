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
    setModuleRooms(module);
}

void ModuleFactory::setModuleBasicFloor(Module* module)
{
    Floor *floor = new Floor();
    Coordinates *coords = new Coordinates();
    coords->X = 0;
    coords->Y = 0;
    coords->height = Variables::tileSize * Variables::tilesPerRoom;
    coords->width = Variables::tileSize * Variables::tilesPerRoom;
    floor->setCoords(coords);
    std::string paths[1] = {"images/stoneFloor3.jpg"};
    Image *image = new Image(1, paths, false);
    image->state = REPEATING;
    floor->setImage(image);
}

void ModuleFactory::setModuleRooms(Module* module)
{
    int **tiles = createTiles();
    int roomCount = rand()%5 + 3;
    
    Room **rooms = RoomFactory::createRooms(roomCount, tiles);    
    
//    factory.OLDsetTileBarriers(module, roomCount, rooms, tiles);
    WallFactory::setObstacleWalls(module, roomCount, rooms, tiles);
    
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

void ModuleFactory::setTransferBlocks(Module* module, int side)
{
    int center = (Variables::tilesPerRoom /2) * Variables::tileSize;
    switch(side)
    {
        case 0:
            module->getModuleTileAt(center, 0)->setTransferDirection(side);
            module->getModuleTileAt(center + 1 * Variables::tileSize, 0)->setTransferDirection(side);
            module->getModuleTileAt(center - 1 * Variables::tileSize, 0)->setTransferDirection(side);
            module->getModuleTileAt(center - 2 * Variables::tileSize, 0)->setTransferDirection(side);
            break;
        case 1:
            module->getModuleTileAt(Variables::tilesPerRoom * Variables::tileSize - 1, center)->setTransferDirection(side);
            module->getModuleTileAt(Variables::tilesPerRoom * Variables::tileSize - 1, center + 1 * Variables::tileSize)->setTransferDirection(side);
            module->getModuleTileAt(Variables::tilesPerRoom * Variables::tileSize - 1, center - 1 * Variables::tileSize)->setTransferDirection(side);
            module->getModuleTileAt(Variables::tilesPerRoom * Variables::tileSize - 1, center - 2 * Variables::tileSize)->setTransferDirection(side);
            break;
        case 2:
            module->getModuleTileAt(center, Variables::tilesPerRoom * Variables::tileSize - 1)->setTransferDirection(side);
            module->getModuleTileAt(center + 1 * Variables::tileSize, Variables::tilesPerRoom * Variables::tileSize - 1)->setTransferDirection(side);
            module->getModuleTileAt(center - 1 * Variables::tileSize, Variables::tilesPerRoom * Variables::tileSize - 1)->setTransferDirection(side);
            module->getModuleTileAt(center - 2 * Variables::tileSize, Variables::tilesPerRoom * Variables::tileSize - 1)->setTransferDirection(side);
            break;
        case 3:
            module->getModuleTileAt(0, center)->setTransferDirection(side);
            module->getModuleTileAt(0, center + 1 * Variables::tileSize)->setTransferDirection(side);
            module->getModuleTileAt(0, center - 1 * Variables::tileSize)->setTransferDirection(side);
            module->getModuleTileAt(0, center - 2 * Variables::tileSize)->setTransferDirection(side);
            break;
    }
}