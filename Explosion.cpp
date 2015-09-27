/* 
 * File:   Explosion.cpp
 * Author: Qb
 * 
 * Created on 10 luty 2015, 19:24
 */

#include "Explosion.h"
#include "globalVariables.h"
#include "LightSource.h"

Explosion::Explosion() {
    this->coords = new Coordinates();
    damage = 100;
    if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[71] == 1)damage *= 0.2;
    damageType = normal;
    radius = 20;
    health = 190;
    image = NULL;
}

void Explosion::setCoords(double X, double Y)
{
    this->coords->X = X;
    this->coords->Y = Y;
    
    
    LightSource *source = new LightSource("images/explosionLightSource.png");
    source->getCoords()->X = coords->X;
    source->getCoords()->Y = coords->Y;
    source->setTime(55);
    source->increaseTileLightValue();
    Variables::session->getMap()->getAllLightSources()->addSource(source);
}

void Explosion::setRadius(int radius) {
    this->radius = radius;
}

void Explosion::setDamageType(DAMAGE_TYPE damageType) {
    this->damageType = damageType;
}

void Explosion::setDamage(int damage) {
    this->damage = damage;
    if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[71] == 1)this->damage *= 0.2;
}

void Explosion::setShooter(Entity* shooter) {
    this->shooter = shooter;
}


Explosion::~Explosion() {
}

void Explosion::update()
{
    health--;
}

void Explosion::display()
{
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
        if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[0] == 0)
        {
            entityList->data->getHit(damage, damageType);
            if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[34] != 0)shooter->heal(damage/10);
        }
        else entityList->data->heal(damage);
        entityList = entityList->next;
    }
    for(int j = 0; j < 4; j++)
    {
        if(walls[j] != NULL)
        {
            walls[j]->getHit(damage, damageType);
            if(walls[j]->getHealth() <= 0)
            {
                Wall *toDelete = walls[j];
                Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->deleteWall(toDelete);
                Variables::session->getMap()->getCurrentModule()->deleteWall(toDelete);
            }
        }
    }
}