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
    radius = 20;
    health = 190;
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

void Explosion::dealDamageInSmallArea()
{
    ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y);
    if(tile != NULL)
    {
        dealDamageInTile(tile->getEntityList(), tile->getWallList(), tile->getDoorList());
        for(int i = 0; i < 8; i++)
        {
            ModuleTile *nextTile = tile->getAdjacentTiles()[i];
            if(nextTile != NULL)
            {
                dealDamageInTile(nextTile->getEntityList(), nextTile->getWallList(), nextTile->getDoorList());
            }
        }
    }
}

void Explosion::dealDamageInLargeArea()
{
    for(int i = 0; i < Variables::tilesPerRoom * Variables::tilesPerRoom; i++)
    {
        ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTiles()[i];
        if(Variables::squaredProximity(tile->getCenterX(), tile->getCenterY(), coords->X, coords->Y) <= radius * radius)
            dealDamageInTile(tile->getEntityList(), tile->getWallList(), tile->getDoorList());
    }
    
}

void Explosion::dealDamage()
{
    if(radius <= Variables::tileSize)this->dealDamageInSmallArea();
    else this->dealDamageInLargeArea();
}

void Explosion::dealDamageInTile(templateList<Entity>* entityList, Wall** walls, Door** doors)
{
    while(entityList != NULL)
    {
        entityList->data->getHit(damage, damageType);
        entityList = entityList->next;
    }
    for(int j = 0; j < 4; j++)
    {
        if(walls[j] != NULL)walls[j]->getHit(damage, damageType);
        if(doors[j] != NULL)doors[j]->getHit(damage, damageType);
    }
}