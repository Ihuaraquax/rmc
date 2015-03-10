/* 
 * File:   AiTileAdjacentSetter.cpp
 * Author: Qb
 * 
 * Created on 10 marzec 2015, 19:28
 */

#include "AiTileAdjacentSetter.h"

void AiTileAdjacentSetter::setAdjacentTiles(ModuleTile* tile)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            if(i - 1 > 0 && j - 1 > 0)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(0, AiTileAdjacentSetter::getTileAt(tile,i - 1, j - 1));
            else if(j == 0 && tile->adjacentTiles[0] != NULL)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(0, tile->adjacentTiles[0]->getAiTileAt(3,3));
            else if(tile->adjacentTiles[1] != NULL)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(0, tile->adjacentTiles[1]->getAiTileAt(3, j-1));
            else AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(0, NULL);
            
            if(j - 1 > 0)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(1, AiTileAdjacentSetter::getTileAt(tile,i, j - 1));
            else if(tile->adjacentTiles[1] != NULL)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(1, tile->adjacentTiles[1]->getAiTileAt(3, j));
            else AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(1, NULL);
            
            if(i + 1 < 4 && j - 1 > 0)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(2, AiTileAdjacentSetter::getTileAt(tile,i + 1, j - 1));
            else if(j == 3 && tile->adjacentTiles[2] != NULL)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(2, tile->adjacentTiles[2]->getAiTileAt(3,0));
            else if(tile->adjacentTiles[1] != NULL)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(2, tile->adjacentTiles[1]->getAiTileAt(3, j+1));
            else AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(2, NULL);
            
            if(i + 1 < 4)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(3, AiTileAdjacentSetter::getTileAt(tile,i + 1, j));
            else if(tile->adjacentTiles[3] != NULL)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(3, tile->adjacentTiles[3]->getAiTileAt(i, 0));
            else AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(3, NULL);
            
            if(i + 1 < 4 && j + 1 < 4)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(4, AiTileAdjacentSetter::getTileAt(tile,i + 1, j - 1));
            else if(j == 3 && tile->adjacentTiles[4] != NULL)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(4, tile->adjacentTiles[4]->getAiTileAt(0,0));
            else if(tile->adjacentTiles[5] != NULL)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(4, tile->adjacentTiles[5]->getAiTileAt(0, j+1));
            else AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(4, NULL);
            
            if(j + 1 < 4)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(5, AiTileAdjacentSetter::getTileAt(tile,i, j+1));
            else if(tile->adjacentTiles[5] != NULL)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(5, tile->adjacentTiles[5]->getAiTileAt(0, j));
            else AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(5, NULL);
            
            if(i - 1 > 0 && j + 1 < 4)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(6, AiTileAdjacentSetter::getTileAt(tile,i - 1, j + 1));
            else if(j == 3 && tile->adjacentTiles[6] != NULL)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(6, tile->adjacentTiles[6]->getAiTileAt(0,3));
            else if(tile->adjacentTiles[5] != NULL)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(6, tile->adjacentTiles[5]->getAiTileAt(0, j-1));
            else AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(6, NULL);
            
            if(i - 1 > 0)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(7, AiTileAdjacentSetter::getTileAt(tile,i - 1, j));
            else if(tile->adjacentTiles[7] != NULL)AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(5, tile->adjacentTiles[7]->getAiTileAt(i, 3));
            else AiTileAdjacentSetter::getTileAt(tile,i,j)->setAdjacentTile(7, NULL);
        }
    
}

AiTile *AiTileAdjacentSetter::getTileAt(ModuleTile* tile, int X, int Y)
{
    return tile->aiTiles[X * 4 + Y];
}