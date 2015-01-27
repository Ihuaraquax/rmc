/* 
 * File:   TileFactory.cpp
 * Author: Qb
 * 
 * Created on 21 styczeń 2015, 21:33
 */

#include "TileFactory.h"
#include "globalVariables.h"

TileFactory::TileFactory() {
}

void TileFactory::addNeighboursToTile(int tileNo, ModuleTile** moduleTiles)
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
    moduleTiles[tileNo]->setAdjacentTiles(tileList);
}

ModuleTile *TileFactory::getTile(int X, int Y, ModuleTile** moduleTiles)
{
    int tileNo = X * Variables::tilesPerRoom + Y;
    return moduleTiles[tileNo];
}

bool TileFactory::isCorrect(int X, int Y)
{
    bool value = true;
    if(X < 0 || X >= Variables::tilesPerRoom)value = false;
    if(Y < 0 || Y >= Variables::tilesPerRoom)value = false;
    return value;
}

void TileFactory::defineTilesSides(Module* module)
{
    
    module->addWallsToTiles();
    module->addDoorsToTiles();
    for(int i = 0; i < Variables::tilesPerRoom * Variables::tilesPerRoom; i++)
    {
        TileFactory::addNeighboursToTile(i,module->moduleTiles);
    }
}

void TileFactory::createModuleTiles(Module* module, int **tiles)
{
    module->moduleTiles = new ModuleTile*[Variables::tilesPerRoom * Variables::tilesPerRoom];
    for(int i = 0; i < Variables::tilesPerRoom; i++)
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            module->moduleTiles[i*Variables::tilesPerRoom + j] =
                    new ModuleTile(false, tiles[i][j],0);
        }
    defineTilesSides(module);
}