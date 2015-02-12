/* 
 * File:   Explosion.cpp
 * Author: Qb
 * 
 * Created on 10 luty 2015, 19:24
 */

#include "Explosion.h"
#include "globalVariables.h"

Explosion::Explosion() {
    this->coords = new Coordinates();
    damage = 100;
    damageType = normal;
    radius = 70;
    health = 240;
    image = NULL;
}

void Explosion::setCoords(double X, double Y)
{
    this->coords->X = X;
    this->coords->Y = Y;
}

void Explosion::setRadius(int radius) {
    this->radius = radius;
}

void Explosion::setDamageType(DAMAGE_TYPE damageType) {
    this->damageType = damageType;
}

void Explosion::setDamage(int damage) {
    this->damage = damage;
}


Explosion::~Explosion() {
}

void Explosion::update()
{
    health--;
}

void Explosion::display()
{
    al_draw_circle(coords->X - Variables::offsetX, coords->Y - Variables::offsetY, radius - health/10, al_map_rgb(200,200,200), 25 - health/10);
}

void Explosion::dealDamage()
{
    ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y);
    templateList<Entity> *entityList = tile->getEntityList();
    while(entityList != NULL)
    {
        entityList->data->getHit(damage, damageType);
        entityList = entityList->next;
    }
    for(int i = 0; i < 4; i++)
    {
        if(tile->getDoorList()[i] != NULL)tile->getDoorList()[i]->getHit(damage, damageType);
        if(tile->getWallList()[i] != NULL)tile->getWallList()[i]->getHit(damage, damageType);
    }
    for(int i = 0; i < 8; i++)
    {
        ModuleTile *nextTile = tile->getAdjacentTiles()[i];
        if(nextTile != NULL)
        {
            entityList = nextTile->getEntityList();
            while(entityList != NULL)
            {
                entityList->data->getHit(damage, damageType);
                entityList = entityList->next;
            }
            for(int j = 0; j < 4; j++)
            {
                if(nextTile->getDoorList()[j] != NULL)nextTile->getDoorList()[j]->getHit(damage, damageType);
                if(nextTile->getWallList()[j] != NULL)nextTile->getWallList()[j]->getHit(damage, damageType);
            }
        }
    }
}