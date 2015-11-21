/* 
 * File:   DoorFactory.cpp
 * Author: Qb
 * 
 * Created on 22 marzec 2015, 12:28
 */

#include "DoorFactory.h"
#include "globalVariables.h"
#include "ObstacleDoor.h"
#include "MapRuleChecker.h"

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
    for(int i = 0; i < Variables::tilesPerRoom - 1; i++)
        for(int j = 0; j < Variables::tilesPerRoom - 1; j++)
        {
            ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTiles()[i * Variables::tilesPerRoom + j];
            if(tile->getObstacle() != NULL)
            {
                if(MapRuleChecker::applyStandarizedRule(i,j,horizontalRuleArray))if(rand()% 15 == 0)
                {
                    Variables::session->getAllEntities()->deleteEntity(tile->getObstacle());
                    Variables::session->getAllEntities()->deleteEntity(tile->getAdjacentTiles()[3]->getObstacle());
                    
                    tile->deleteFromEntityList(tile->getObstacle());
                    tile->getAdjacentTiles()[3]->deleteFromEntityList(tile->getAdjacentTiles()[3]->getObstacle());
                    Entity *door = ObstacleDoor::CreateObstacleDoor(i * Variables::tileSize, j * Variables::tileSize);
                    Variables::session->getAllEntities()->addEntity(door);
                    dynamic_cast<ObstacleDoor*>(door)->setAngle(true);
                }
                if(MapRuleChecker::applyStandarizedRule(i,j,verticalRuleArray))if(rand()% 15 == 0)
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