/* 
 * File:   DoorFactory.cpp
 * Author: Qb
 * 
 * Created on 22 marzec 2015, 12:28
 */

#include "DoorFactory.h"
#include "globalVariables.h"
#include "ObstacleDoor.h"

void DoorFactory::createDoors()
{
    int verticalRuleArray[5][5] = {
        {-1,-1,-1,-1,-1},
        {-1, 0, 1, 0,-1},
        {-1, 0, 1, 0,-1},
        {-1, 0, 1, 0,-1},
        {-1,-1,-1,-1,-1}
    };
    int horizontalRuleArray[5][5] = {
        {-1,-1,-1,-1,-1},
        {-1, 0, 0, 0,-1},
        {-1, 1, 1, 1,-1},
        {-1, 0, 0, 0,-1},
        {-1,-1,-1,-1,-1}
    };
    for(int i = 1; i < Variables::tilesPerRoom - 1; i++)
        for(int j = 1; j < Variables::tilesPerRoom - 1; j++)
        {
            ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTiles()[i * Variables::tilesPerRoom + j];
            if(tile->getObstacle() != NULL)
            {
                if(isRuleApplicable(i,j,horizontalRuleArray))if(rand()% 15 == 0)
                {
                    Variables::session->getAllEntities()->deleteEntity(tile->getObstacle());
                    Variables::session->getAllEntities()->deleteEntity(tile->getAdjacentTiles()[3]->getObstacle());
                    
                    tile->deleteFromEntityList(tile->getObstacle());
                    tile->getAdjacentTiles()[3]->deleteFromEntityList(tile->getAdjacentTiles()[3]->getObstacle());
                    Entity *door = ObstacleDoor::CreateObstacleDoor(i * Variables::tileSize, j * Variables::tileSize);
                    Variables::session->getAllEntities()->addEntity(door);
                    dynamic_cast<ObstacleDoor*>(door)->setAngle(true);
                }
                if(isRuleApplicable(i,j,verticalRuleArray))if(rand()% 15 == 0)
                {
                    Variables::session->getAllEntities()->deleteEntity(tile->getObstacle());
                    Variables::session->getAllEntities()->deleteEntity(tile->getAdjacentTiles()[5]->getObstacle());
                    
                    tile->deleteFromEntityList(tile->getObstacle());
                    tile->getAdjacentTiles()[5]->deleteFromEntityList(tile->getAdjacentTiles()[5]->getObstacle());
                    Entity *door = ObstacleDoor::CreateObstacleDoor(i * Variables::tileSize, j * Variables::tileSize);
                    Variables::session->getAllEntities()->addEntity(door);
                    dynamic_cast<ObstacleDoor*>(door)->setAngle(false);
                }
            }
        }
}


// -1 cokolwiek
//  0 brak ściany
//  1 ściana
bool DoorFactory::isRuleApplicable(int x, int y, int rule[5][5])
{
    bool horizontalResult = true;    
    ModuleTile **temp = Variables::session->getMap()->getCurrentModule()->getModuleTiles();
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            int X = x+i-2, Y = y+j-2;
            if(X >= 0 && X < Variables::tilesPerRoom && Y >= 0 && Y < Variables::tilesPerRoom)
            {
                if(rule[i][j] == 0 && temp[X * Variables::tilesPerRoom + Y]->getObstacle() != NULL)
                {
                    horizontalResult = false;
                    break;
                }
                if(rule[i][j] == 1 && temp[X * Variables::tilesPerRoom + Y]->getObstacle() == NULL)
                {
                    horizontalResult = false;
                    break;
                }
            }
            if(horizontalResult == false)break;
        }
    }
    return horizontalResult;
}