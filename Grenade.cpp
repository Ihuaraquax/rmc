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
    this->coords->Y += this->coords->speedY;
    if(Variables::currentFrame % 20 == 0)
    {
        this->coords->speedX -= 0.1;
        this->coords->speedY -= 0.1;
    }
    ModuleTile *currentTile = Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y);
    if(currentTile != NULL)
    {
        Entity *target = CollisionDetector::isEntityCollisions(currentTile, this);
        if(target != NULL)
        {
            if(target->getCoords()->height > target->getCoords()->width)this->coords->speedX *= -1;
            else this->coords->speedY *= -1;
            this->coords->speedX *= 0.7;
            this->coords->speedY *= 0.7;
        }
        else
        {
            Door *targetDoor = CollisionDetector::isDoorCollision(currentTile, this);
            if(targetDoor != NULL)
            {
                if(target->getCoords()->height > target->getCoords()->width)this->coords->speedX *= -1;
                else this->coords->speedY *= -1;
                this->coords->speedX *= 0.7;
                this->coords->speedY *= 0.7;
            }
        }
    }
    else health = 0;
    if(range > 0)
    {
        range--;
        if(range == 0)health = 0;
    }
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