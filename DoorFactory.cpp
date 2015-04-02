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
    for(int i = 1; i < Variables::tilesPerRoom - 1; i++)
        for(int j = 1; j < Variables::tilesPerRoom - 1; j++)
        {
            ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTiles()[i * Variables::tilesPerRoom + j];
            if(tile->getObstacle() != NULL)
            {
                if(tile->getAdjacentTiles()[7]->getObstacle() == NULL && tile->getAdjacentTiles()[3]->getObstacle() != NULL &&
                   tile->getAdjacentTiles()[3]->getAdjacentTiles()[3] != NULL && tile->getAdjacentTiles()[3]->getAdjacentTiles()[3]->getObstacle() == NULL)if(rand()% 15 == 0)
                {
                    Variables::session->getAllEntities()->deleteEntity(tile->getObstacle());
                    Variables::session->getAllEntities()->deleteEntity(tile->getAdjacentTiles()[3]->getObstacle());
                    
                    tile->deleteFromEntityList(tile->getObstacle());
                    tile->getAdjacentTiles()[3]->deleteFromEntityList(tile->getAdjacentTiles()[3]->getObstacle());
                    Entity *door = ObstacleDoor::CreateObstacleDoor(i * Variables::tileSize, j * Variables::tileSize);
                    Variables::session->getAllEntities()->addEntity(door);
                    dynamic_cast<ObstacleDoor*>(door)->setAngle(true);
                }
                if(tile->getAdjacentTiles()[1]->getObstacle()== NULL && tile->getAdjacentTiles()[5]->getObstacle() != NULL &&
                   tile->getAdjacentTiles()[5]->getAdjacentTiles()[5] != NULL && tile->getAdjacentTiles()[5]->getAdjacentTiles()[5]->getObstacle() == NULL)if(rand()% 15 == 0)
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