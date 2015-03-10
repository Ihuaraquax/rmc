/* 
 * File:   AiTileAdjacentSetter.h
 * Author: Qb
 *
 * Created on 10 marzec 2015, 19:28
 */

#ifndef AITILEADJACENTSETTER_H
#define	AITILEADJACENTSETTER_H
#include "ModuleTile.h"
#include "AiTile.h"
class AiTileAdjacentSetter {
public:
    static void setAdjacentTiles(ModuleTile *tile);
private:
    static AiTile *getTileAt(ModuleTile *tile, int X, int Y);
};

#endif	/* AITILEADJACENTSETTER_H */

