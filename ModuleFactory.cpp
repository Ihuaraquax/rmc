/* 
 * File:   ModuleFactory.cpp
 * Author: Qb
 * 
 * Created on 24 listopad 2014, 19:02
 */

#include <list>

#include <iostream>
#include <fstream>
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
    std::string paths = "images/stoneFloor3.jpg";
    Image *image = new Image(paths, false);
    image->state = REPEATING;
    floor->setImage(image);
}

void ModuleFactory::setModuleRooms(Module* module)
{
    int **tiles = createTiles();
    Room ***rooms;
    rooms = new Room**[10];
    for(int i = 0; i < 10; i++)
    {
       rooms[i] = RoomFactory::createRooms(roomCount[i], tiles, i*10);    
    }
//    
////    factory.OLDsetTileBarriers(module, roomCount, rooms, tiles);
    for(int i = 0; i < 10; i++)
    {
        WallFactory::setObstacleWalls(module, roomCount[i], rooms[i], tiles);
    }
//    
    TileFactory::createModuleTiles(module, tiles);
//    for(int j = 0; j < 10; j++)
//    {
//        for(int i = 0; i < roomCount[i]; i++)
//        {
//            delete rooms[j][i];
//        }
//        delete []rooms[j];
//    }
//    delete []rooms;
}

int **ModuleFactory::createTiles()
{
    int **tiles;
    std::fstream file;
    file.open("mapTemplates/template1.txt", std::ios::in);
    tiles = new int*[Variables::tilesPerRoom];
    for(int i = 0; i < Variables::tilesPerRoom; i++)
    {
        tiles[i] = new int[Variables::tilesPerRoom];
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            file >> tiles[i][j];
        }
    }
    roomCount = new int[10];
    for(int i = 0; i < 10; i++) file >> roomCount[9-i];
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