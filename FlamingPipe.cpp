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
//    if(Variables::currentFrame == 0)
//    {
        ModuleTile *firstTile, *secondTile;
        double tileSize = Variables::tileSize;
        if(this->coords->angle == 0)
        {
            firstTile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y - tileSize);
            secondTile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y - tileSize * 2);
        } 
        else if(coords->angle == 90) 
        {
            firstTile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X - tileSize, coords->Y);
            secondTile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X - tileSize * 2, coords->Y);
        }
        else if(coords->angle == 180) 
        {
            firstTile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y + tileSize);
            secondTile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y + tileSize * 2);
        }
        else
        {
            firstTile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X + tileSize, coords->Y);
            secondTile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X + tileSize * 2, coords->Y);
        }
        if(firstTile != NULL)
        {
            templateList<Entity> *entityList = firstTile->getEntityList();
            while(entityList != NULL)
            {
                entityList->data->getHit(153, 1);
                entityList = entityList->next;
            }
        }
        if(secondTile != NULL)
        {
            templateList<Entity> *entityList = secondTile->getEntityList();
            while(entityList != NULL)
            {
                entityList->data->getHit(153, 1);
                entityList = entityList->next;
            }
        }
//    }
}