/* 
 * File:   Missle.cpp
 * Author: Qb
 * 
 * Created on 3 marzec 2015, 18:53
 */

#include "Missle.h"
#include "WeaponLoader.h"
#include "globalVariables.h"
#include "Explosion.h"
#include "CollisionDetector.h"

Missle::Missle(bool isMIRV) {
    this->coords = new Coordinates();
    this->coords->height = 20;
    this->coords->width = 20;
    std::string paths[] = {"images/missle.png"};
    this->image = new Image(1, paths, true);
    health = 1;
    image->state = NORMAL;
    threatLevel = 0;
    this->weapons = new Weapon*[1];
    this->weapons[0] = new Weapon();
    WeaponLoader::loadWeapon(weapons[0], 101);
    this->weapons[0]->setRange(45);
    MIRV = isMIRV;
}

void Missle::update()
{
    this->coords->X += this->coords->speedX;
    this->coords->Y += this->coords->speedY;
    if(Variables::currentFrame % 20 == 0)
    {
        this->coords->speedX *= 1.5;
        this->coords->speedY *= 1.5;
    }
    ModuleTile *currentTile = Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y);
    if(currentTile != NULL)
    {
        Wall *targetWall = CollisionDetector::isWallCollisions(currentTile, this);
        if(targetWall != NULL)
        {
            health--;
        }
        else
        {
            Entity *targetEntity = CollisionDetector::isEntityCollisions(currentTile, this);
            if(targetEntity != NULL && targetEntity->getTeamId() != this->teamId)
            {
                health--;
            }
            else
            {
                Door *targetDoor = CollisionDetector::isDoorCollision(currentTile, this);
                if(targetDoor != NULL)
                {
                    health--;
                }
            }
        }
    }
    else health = 0;
    range -= this->coords->speedX;
    range -= this->coords->speedY;
    if(range <= 0)health = 0;
}

void Missle::executeAgony()
{
    if(this->coords->X > 0 && this->coords->X < Variables::tileSize * Variables::tilesPerRoom)
    if(this->coords->Y > 0 && this->coords->Y < Variables::tileSize * Variables::tilesPerRoom)
    {
        if(MIRV)
        {
            weapons[0]->shoot(coords, coords, -1, 0, 0, 0);
        } else {
            Entity *explosion = new Explosion();
            dynamic_cast<Explosion*>(explosion)->setCoords(coords->X, coords->Y);
            dynamic_cast<Explosion*>(explosion)->dealDamage();
            Variables::session->getAllEntities()->addEntity(explosion);
        }
    }
}
bool Missle::isProjectile()
{
    return true;
}