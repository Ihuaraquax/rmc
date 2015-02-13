/* 
 * File:   Projectile.cpp
 * Author: Qb
 * 
 * Created on 6 styczeń 2015, 12:56
 */

#include "Projectile.h"
#include "globalVariables.h"
#include "CollisionDetector.h"
#include "Explosion.h"

Projectile::Projectile() {
    this->coords = new Coordinates();
    this->coords->height = 16;
    this->coords->width = 16;
    std::string paths[] = {"images/bullet.png"};
    this->image = new Image(1, paths, true);
    health = 1;
    image->state = NORMAL;
    threatLevel = 0;
}

Projectile::~Projectile() {
}

void Projectile::update()
{
    this->coords->X += this->coords->speedX;
    this->coords->Y += this->coords->speedY;
    ModuleTile *currentTile = Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y);
    if(currentTile != NULL)
    {
        Wall *targetWall = CollisionDetector::isWallCollisions(currentTile, this);
        if(targetWall != NULL)
        {
            targetWall->getHit(damage, damageType);
            if(targetWall->getHealth() <= 0)
            {
                currentTile->deleteWall(targetWall);
                Variables::session->getMap()->getCurrentModule()->deleteWall(targetWall);
            }
            health--;
        }
        else
        {
            Entity *targetEntity = CollisionDetector::isEntityCollisions(currentTile, this);
            if(targetEntity != NULL && targetEntity->getTeamId() != this->teamId)
            {
                health--;
                targetEntity->getHit(damage, damageType);
            }
            else
            {
                Door *targetDoor = CollisionDetector::isDoorCollision(currentTile, this);
                if(targetDoor != NULL)
                {
                    health--;
                    targetDoor->getHit(damage, damageType);
                    if(targetDoor->getHealth() <= 0)
                    {
                        currentTile->deleteDoor(targetDoor);
                        Variables::session->getMap()->getCurrentModule()->deleteDoor(targetDoor);
                    }
                }
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

void Projectile::setValues(Coordinates *coords, int damage, DAMAGE_TYPE damageType, int angle, int teamID, int range)
{
    this->coords->X = coords->X + coords->width/2;
    this->coords->Y = coords->Y + coords->height/2;
    this->coords->angle = angle;
    this->damage = damage;
    this->damageType = damageType;
    this->teamId = teamID;
    Variables::giveFactors(angle, this->coords->speedX, this->coords->speedY);
    double speed = rand()% 20;
    speed /=10;
    speed += 4;
    this->coords->speedX *= speed;
    this->coords->speedY *= speed;
    this->range = range;
}

void Projectile::hit(Entity* target)
{
    target->getHit(damage, damageType);
}

bool Projectile::isProjectile()
{
    return true;
}

void Projectile::executeAgony()
{
}