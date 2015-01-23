/* 
 * File:   Entity.cpp
 * Author: Qb
 * 
 * Created on 4 listopad 2014, 22:37
 */

#include "Entity.h"
#include "Coordinates.h"
#include "Image.h"
#include "globalVariables.h"
#include "ModuleTile.h"
#include "CollisionDetector.h"

Entity::Entity() {
    armor = 0;
    elementalResists = new double[Variables::damageTypeCount];
    for(int i = 0; i < Variables::damageTypeCount; i++)this->elementalResists[i] = 0.5;
}

Entity::~Entity() {
    delete coords;
    delete image;
}

void Entity::display(){
    image->display(coords);
}

void Entity::move(double X, double Y){
    ModuleTile *currentTile = Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y);
    
    this->coords->X += X * this->coords->speedX;
    ModuleTile *newTile = Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y);
    if(CollisionDetector::isAnyCollision(newTile, this))
    {
        this->coords->X -= X * this->coords->speedX;;
    }
    
    
    this->coords->Y += Y * this->coords->speedY;
    newTile = Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y);
    if(CollisionDetector::isAnyCollision(newTile, this))
    {
        this->coords->Y -= Y * this->coords->speedY;;
    }
    
    newTile = Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y);
    if(currentTile != newTile)
    {
        currentTile->deleteFromEntityList(this);
        newTile->addToEntityList(this);
    }
}

void Entity::update(){
    
}


Coordinates* Entity::getCoords() const {
    return coords;
}

int Entity::getHealth() const {
    return health;
}

void Entity::getHit(int damage, int damageType)
{
    int damageInflicted = (damage - armor) * (1-elementalResists[damageType]);
    if(damageInflicted < 0)damageInflicted = 0;
    health -= damageInflicted;
}

void Entity::attack(bool leftWeapon)
{
    if(leftWeapon)weapons[0]->shoot(coords, shootingAngle, teamId);
    else weapons[1]->shoot(coords, shootingAngle, teamId);
}

int Entity::getTeamId() const {
    return teamId;
}

void Entity::setStartingTile()
{
    ModuleTile *currentTile = Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y);
    currentTile->addToEntityList(this);
}


bool Entity::isProjectile()
{
    return false;
}