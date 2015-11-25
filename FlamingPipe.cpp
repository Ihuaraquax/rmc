/* 
 * File:   FlamingPipe.cpp
 * Author: Adiutant
 * 
 * Created on 23 listopad 2015, 23:18
 */

#include "FlamingPipe.h"
#include "Animation.h"
#include "Entity.h"
#include "globalVariables.h"
#include "CollisionDetector.h"

FlamingPipe::FlamingPipe() {
    this->animation = new Animation();
    animation->setAnimation("images/flamepipe/flamePipeAnimation.png", 50, 150);
    this->coords = new Coordinates();
    this->coords->angle = 0;
    this->coords->width = Variables::tileSize;
    this->coords->height = Variables::tileSize * 3;
    this->coords->speedX = 0;
    this->coords->speedY = 0;
    health = 300;
    teamId = 0;
    maximumHealth = health;
    planCoords = new Coordinates();
}

FlamingPipe::FlamingPipe(const FlamingPipe& orig) {
}

FlamingPipe::~FlamingPipe() {
}

void FlamingPipe::display()
{
    animation->display(coords);
}

Entity *FlamingPipe::getFlamingPipe(double X, double Y)
{
    Entity *result = new FlamingPipe();
    result->getCoords()->X = X;
    result->getCoords()->Y = Y;
    return result;
}

void FlamingPipe::update()
{
    if(Variables::currentFrame%20 == 0)
    {
        ModuleTile *firstTile;
        double tileSize = Variables::tileSize;
        Coordinates *attackCoords = new Coordinates();
        if(this->coords->angle == 0)
        {
            attackCoords->X = coords->X;
            attackCoords->Y = coords->Y;
            attackCoords->width = tileSize;
            attackCoords->height = tileSize*2;
            
            firstTile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y);
        } 
        else if(coords->angle == 90) 
        {
            attackCoords->X = coords->X;
            attackCoords->Y = coords->Y + tileSize;
            attackCoords->width = tileSize*2;
            attackCoords->height = tileSize;
            firstTile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X + tileSize, coords->Y + tileSize);
        }
        else if(coords->angle == 180) 
        {            
            attackCoords->X = coords->X;
            attackCoords->Y = coords->Y + tileSize;
            attackCoords->width = tileSize;
            attackCoords->height = tileSize*2;
            
            firstTile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y + tileSize*2);
        }
        else
        {
            attackCoords->X = coords->X - tileSize;
            attackCoords->Y = coords->Y + tileSize;
            attackCoords->width = tileSize*2;
            attackCoords->height = tileSize;
            firstTile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y + tileSize);
        }
        if(firstTile != NULL)
        {
            templateList<Entity> *entityList = firstTile->getEntityList();
            while(entityList != NULL)
            {
                if(CollisionDetector::isBasicCollision(entityList->data->getCoords(), attackCoords))
                {
                    entityList->data->getHit(153, 1);
                }
                entityList = entityList->next;
            }
            for(int i = 0; i < 8; i++)
            {
                ModuleTile *adjacentTile = firstTile->getAdjacentTiles()[i];
                if(adjacentTile != NULL)
                {
                    entityList = adjacentTile->getEntityList();
                    while(entityList != NULL)
                    {
                        if(CollisionDetector::isBasicCollision(entityList->data->getCoords(), attackCoords))
                        {
                            entityList->data->getHit(153, 1);
                        }
                        entityList = entityList->next;
                    }
                }
            }
            
        }
        delete attackCoords;
    }
}