/* 
 * File:   WallFactory.cpp
 * Author: Qb
 * 
 * Created on 25 listopad 2014, 19:06
 */

#include <list>

#include "WallFactory.h"
#include "Coordinates.h"
#include "globalVariables.h"
#include "Obstacle.h"

WallFactory::WallFactory() {
    temp = new int*[Variables::tilesPerRoom];
    for(int i = 0; i < Variables::tilesPerRoom; i++)
    {
        temp[i] = new int[Variables::tilesPerRoom];
        for(int j = 0; j < Variables::tilesPerRoom; j++)temp[i][j] = 0;
    }
}

void WallFactory::setModuleBasicWalls(Module* module)
{
    for(int i = 0; i < Variables::tilesPerRoom; i++)
    {
        Coordinates *coords1 = new Coordinates();
        coords1->X = 0;
        coords1->Y = Variables::tileSize * i;
        coords1->height = Variables::tileSize;
        coords1->width = 2;
        Coordinates *coords2 = new Coordinates();
        coords2->X = Variables::tileSize * i;
        coords2->Y = 0;
        coords2->height = 2;
        coords2->width = Variables::tileSize;
        Coordinates *coords3 = new Coordinates();
        coords3->X = Variables::tileSize * Variables::tilesPerRoom;
        coords3->Y = Variables::tileSize * i;
        coords3->height = Variables::tileSize;
        coords3->width = 2;
        Coordinates *coords4 = new Coordinates();
        coords4->X = Variables::tileSize * i;
        coords4->Y = Variables::tileSize * Variables::tilesPerRoom;
        coords4->height = 2;
        coords4->width = Variables::tileSize;
        Wall *wall1 = new Wall();
        wall1->setCoords(coords1);
        Wall *wall2 = new Wall();
        wall2->setCoords(coords2);
        Wall *wall3 = new Wall();
        wall3->setCoords(coords3);
        Wall *wall4 = new Wall();
        wall4->setCoords(coords4);
        wall1->setAsModuleBorderWall();
        wall2->setAsModuleBorderWall();
        wall3->setAsModuleBorderWall();
        wall4->setAsModuleBorderWall();
        module->walls.push_back(wall1);
        module->walls.push_back(wall2);
        module->walls.push_back(wall3);
        module->walls.push_back(wall4);
    }
}

void WallFactory::setObstacleWalls(int** tiles)
{
    for(int i = 0; i < Variables::tilesPerRoom; i++)
    {
        for(int j = 0; j < Variables::tilesPerRoom; j++){
            int tileValue = tiles[i][j];
            if(i > 0 && tiles[i-1][j] != tileValue)temp[i][j] = 1;
            if(i < Variables::tilesPerRoom-1 && tiles[i+1][j] != tileValue)temp[i][j] = 1;
            if(j > 0 && tiles[i][j-1] != tileValue)temp[i][j] = 1;
            if(j < Variables::tilesPerRoom-1 && tiles[i][j+1] != tileValue)temp[i][j] = 1;
        }
    }
}

void WallFactory::generateCorners()
{
    for(int i = 1; i < Variables::tilesPerRoom-1; i++)
    {
        for(int j = 1; j < Variables::tilesPerRoom-1; j++)
        {
            if(temp[i][j] == 1)
            {
                int neighbours = 4;
                if(temp[i-1][j] == 0)neighbours--;
                if(temp[i][j-1] == 0)neighbours--;
                if(temp[i+1][j] == 0)neighbours--;
                if(temp[i][j+1] == 0)neighbours--;
                
                if(neighbours == 2)
                {
                    if(temp[i-1][j] > 0 && temp[i][j-1] > 0)temp[i][j] = 2;
                    if(temp[i+1][j] > 0 && temp[i][j-1] > 0)temp[i][j] = 3;
                    if(temp[i+1][j] > 0 && temp[i][j+1] > 0)temp[i][j] = 4;
                    if(temp[i-1][j] > 0 && temp[i][j+1] > 0)temp[i][j] = 5;
                }
            }
        }
    }
}

void WallFactory::deleteSingleWalls()
{
    for(int i = 0; i < Variables::tilesPerRoom; i++)
    {
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            if(temp[i][j] == 1)
            {
                int neighbours = 4;
                if(i-1 >= 0 && !temp[i-1][j] == 0)neighbours--;
                if(j-1 >= 0 && !temp[i][j-1] == 0)neighbours--;
                if(i+1 < Variables::tilesPerRoom && !temp[i+1][j] == 0)neighbours--;
                if(j-1 >= Variables::tilesPerRoom && !temp[i][j+1] == 0)neighbours--;
                
                if(neighbours == 1)temp[i][j] = 0;
            }
        }
    }
}


void WallFactory::addHoleWalls()
{
    for(int i = 1; i < Variables::tilesPerRoom-1; i++)
    {
        for(int j = 1; j < Variables::tilesPerRoom-1; j++)
        {
            if(temp[i][j] == 0)
            {
                int neighbours = 4;
                if(temp[i-1][j] == 0)neighbours--;
                if(temp[i][j-1] == 0)neighbours--;
                if(temp[i+1][j] == 0)neighbours--;
                if(temp[i][j+1] == 0)neighbours--;
                
                if(neighbours >= 3)temp[i][j] = 1;
            }
        }
    }
}

void WallFactory::generateWalls()
{
    for(int i = 0; i < Variables::tilesPerRoom; i++)
    {
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            if(temp[i][j] == 1)
            {
                Entity *wall = Obstacle::CreateObstacle(i * Variables::tileSize, j * Variables::tileSize);
                dynamic_cast<Obstacle*>(wall)->setAsWall();
                Variables::session->getAllEntities()->addEntity(wall);
            }
            else if(temp[i][j] > 1)
            {
                Entity *wall = Obstacle::CreateObstacle(i * Variables::tileSize, j * Variables::tileSize);
                dynamic_cast<Obstacle*>(wall)->setAsCornerWall(temp[i][j]);
                Variables::session->getAllEntities()->addEntity(wall);
            }
        }
    }
}

void WallFactory::deleteThickWalls()
{
    // TO DO BETTER 
//    for(int i = 0; i < Variables::tilesPerRoom; i++)
//    {
//        for(int j = 0; j < Variables::tilesPerRoom; j++)
//        {
//            if(temp[i][j] == 1)
//            {
//                int neighboursCount = 0;
//                int straightNeighboursCount = 0;
//                if(i > 0)
//                {
//                    if(temp[i-1][j] > 0)
//                    {
//                        neighboursCount++;
//                        straightNeighboursCount++;
//                    }
//                    if(j > 0 && temp[i-1][j-1] > 0)
//                    {
//                        neighboursCount++;
//                    }
//                    if(j < Variables::tilesPerRoom-1 && temp[i-1][j+1] > 0)
//                    {
//                        neighboursCount++;
//                    }
//                }
//                if(i < Variables::tilesPerRoom -1)
//                {
//                    if(temp[i+1][j] > 0)
//                    {
//                        neighboursCount++;
//                        straightNeighboursCount++;
//                    }
//                    if(j > 0 && temp[i+1][j-1] > 0)
//                    {
//                        neighboursCount++;
//                    }
//                    if(j < Variables::tilesPerRoom-1 && temp[i+1][j+1] > 0)
//                    {
//                        neighboursCount++;
//                    }
//                }
//                if(j > 0)
//                {
//                    if(temp[i][j-1] > 0)
//                    {
//                        neighboursCount++;
//                        straightNeighboursCount++;
//                    }
//                    if(i > 0 && temp[i-1][j-1] > 0)
//                    {
//                        neighboursCount++;
//                    }
//                    if(i < Variables::tilesPerRoom-1&& temp[i+1][j-1] > 0)
//                    {
//                        neighboursCount++;
//                    }
//                }
//                if(j < Variables::tilesPerRoom -1)
//                {
//                    if(temp[i][j+1] > 0)
//                    {
//                        neighboursCount++;
//                        straightNeighboursCount++;
//                    }
//                    if(i > 0 && temp[i-1][j+1] > 0)
//                    {
//                        neighboursCount++;
//                    }
//                    if(i < Variables::tilesPerRoom-1 && temp[i+1][j+1] > 0)
//                    {
//                        neighboursCount++;
//                    }
//                }
//                if(straightNeighboursCount == 3 && neighboursCount == 7)temp[i][j] = 0;
//            }
//        }
//    }
}