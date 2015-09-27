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
    this->image = Variables::images->getByName("bullet");
    health = 1;
    image->state = NORMAL;
    threatLevel = 0;
    explode = false;
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
            if(targetEntity != NULL )
            {
                if(targetEntity->getTeamId() == this->teamId)
                {
                    if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[1] != 0 && targetEntity != this->shooter)
                    {
                        health--;
                        targetEntity->getHit(damage, damageType);
                        if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[34] != 0)shooter->heal(damage/10);
                    } else if (Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[2] != 0 && targetEntity != this->shooter)
                    {
                        health--;
                        targetEntity->heal(damage);
                    }
                } else 
                {
                    health--;
                    targetEntity->getHit(damage, damageType); 
                }
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
    if(range != 0 && health == 0)
    {
        if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[70] != 0 && rand()%10 == 0)
        {
            health = 1;
            coords->speedX *= -1;
            coords->speedY *= -1;
        }
    }
}

void Projectile::setValues(Coordinates *coords, int damage, DAMAGE_TYPE damageType, int angle, int teamID, int range)
{
    this->coords->X = coords->X;
    this->coords->Y = coords->Y;
    this->coords->angle = angle;
    this->damage = damage;
    this->damageType = damageType;
    this->teamId = teamID;
    Variables::giveFactors(angle, this->coords->speedX, this->coords->speedY);
    double speed = 0.0 + rand()% 20;
    speed /=10;
    speed += 12;
    this->coords->speedX *= speed;
    this->coords->speedY *= speed;
    this->range = range;
}

void Projectile::hit(Entity* target)
{
    target->getHit(damage, damageType);
    target->getHit(additionalDamage, additionalDamageType);
}

bool Projectile::isProjectile()
{
    return true;
}

void Projectile::executeAgony()
{
    if(explode)
    {
        Entity *explosion = new Explosion();
        dynamic_cast<Explosion*>(explosion)->setCoords(coords->X, coords->Y);
        dynamic_cast<Explosion*>(explosion)->setShooter(shooter);
        dynamic_cast<Explosion*>(explosion)->dealDamage();
        Variables::session->getAllEntities()->addEntity(explosion);
    }
    else if(Variables::session->getMap()->getCurrentModule()->getModificatorsTable()[32] != 0)
    {
        Entity *explosion = new Explosion();
        dynamic_cast<Explosion*>(explosion)->setCoords(coords->X, coords->Y);
        dynamic_cast<Explosion*>(explosion)->setDamage(damage *0.2);
        dynamic_cast<Explosion*>(explosion)->setShooter(shooter);
        dynamic_cast<Explosion*>(explosion)->dealDamage();
        Variables::session->getAllEntities()->addEntity(explosion);
    }
}

void Projectile::setRange(int range) {
    this->range = range;
}

void Projectile::setAdditionalDamage(int additionalDamage, int additionalDamageType) {
    this->additionalDamage = additionalDamage;
    this->additionalDamageType = additionalDamageType;
}

int Projectile::getDamage() const {
    return damage;
}

void Projectile::setDamage(int damage) {
    this->damage = damage;
}

void Projectile::setShooter(Entity* shooter) {
    this->shooter = shooter;
    this->ignoreCollisionEntity = shooter;
}


int Projectile::getProjectileType()
{
    return 0;
}