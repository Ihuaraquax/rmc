/* 
 * File:   TileFactory.h
 * Author: Qb
 *
 * Created on 21 styczeń 2015, 21:33
 */

#ifndef TILEFACTORY_H
#define	TILEFACTORY_H
#include "ModuleTile.h"
#include "Module.h"

class TileFactory {
public:
    TileFactory();
    static void createModuleTiles(Module *module, int **tiles);
    static void defineTilesSides(Module *module);
private:
    static ModuleTile *getTile(int X, int Y, ModuleTile** moduleTiles);
    static bool isCorrect(int X, int Y);
    static void addNeighboursToTile(int tileNo, ModuleTile** moduleTiles);
};

#endif	/* TILEFACTORY_H */

