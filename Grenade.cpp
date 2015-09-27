/* 
 * File:   Grenade.cpp
 * Author: Qb
 * 
 * Created on 3 marzec 2015, 18:53
 */

#include "Grenade.h"
#include "globalVariables.h"
#include "Explosion.h"
#include "CollisionDetector.h"

Grenade::Grenade() {
    this->coords = new Coordinates();
    this->coords->height = 16;
    this->coords->width = 16;
    this->image = Variables::images->getByName("grenade");
    health = 1;
    image->state = NORMAL;
    threatLevel = 0;
}

void Grenade::update()
{
    this->coords->X += this->coords->speedX;
    bounce(true);
    this->coords->Y += this->coords->speedY;
    bounce(false);
    if(Variables::currentFrame % 20 == 0)
    {
        this->coords->speedX *= 0.8;
        this->coords->speedY *= 0.8;
        floorBounce();
    }
    if(range > 0)
    {
        range--;
    }
    if(range == 0)health = 0;
}

void Grenade::bounce(bool horizontal)
{
    ModuleTile *currentTile = Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y);
    if(currentTile != NULL)
    {
        Entity *target = CollisionDetector::isEntityCollisions(currentTile, this);
        if(target != NULL)
        {
            if(horizontal)
            {
                this->coords->speedX *= -1;
                this->coords->X += this->coords->speedX;
            }
            else
            {
                this->coords->speedY *= -1;
                this->coords->Y += this->coords->speedY;
            }
            this->coords->speedX *= 0.7;
            this->coords->speedY *= 0.7;
        }
    }
    else
    {
        if(horizontal)
        {
            this->coords->speedX *= -1;
            this->coords->X += this->coords->speedX;
        }
        else
        {
            this->coords->speedY *= -1;
            this->coords->Y += this->coords->speedY;
        }
    }
}

void Grenade::floorBounce()
{
}

void Grenade::executeAgony()
{
    Entity *explosion = new Explosion();
    dynamic_cast<Explosion*>(explosion)->setCoords(coords->X, coords->Y);
    dynamic_cast<Explosion*>(explosion)->dealDamage();
    Variables::session->getAllEntities()->addEntity(explosion);
}

bool Grenade::isProjectile()
{
    return true;
}

int Grenade::getProjectileType()
{
    return 1;
}

void Grenade::multiplySpeed(double multiplier)
{
    double temp = sqrt(multiplier)/1000;
    this->coords->speedX *= temp;
    this->coords->speedY *= temp;
}