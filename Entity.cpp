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

Entity::Entity() {
}

Entity::Entity(const Entity& orig) {
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
    if(checkCollisions(newTile->getWallList()) ||
       checkCollisions(newTile->getDoorList()) ||
       checkCollisions(newTile->getEntitiesFromsLists()) != NULL)
    {
        this->coords->X -= X * this->coords->speedX;;
    }
    
    
    this->coords->Y += Y * this->coords->speedY;
    newTile = Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y);
    if(checkCollisions(newTile->getWallList()) ||
       checkCollisions(newTile->getDoorList()) ||
       checkCollisions(newTile->getEntitiesFromsLists()) != NULL)
    {
        this->coords->Y -= Y * this->coords->speedY;;
    }
    
    if(currentTile != newTile)
    {
        currentTile->deleteFromEntityList(this);
        newTile->addToEntityList(this);
    }
}

void Entity::update(){
    
}

bool Entity::isCollision(Coordinates* oCoords)
{
    bool value = true;
    if(oCoords->X + oCoords->width < coords->X || oCoords->X > coords->X  + coords->width ||
       oCoords->Y + oCoords->height < coords->Y || oCoords->Y  > coords->Y + coords->height)value = false;
    return value;
}

void Entity::loadFile()
{
    
}

Coordinates* Entity::getCoords() const {
    return coords;
}

int Entity::getHealth() const {
    return health;
}

Entity* Entity::checkCollisions(std::list<Entity*> otherEntities)
{
    Entity* value = NULL;
    for(std::list<Entity*>::iterator i = otherEntities.begin(); i != otherEntities.end(); ++i)
    {
        Entity *temp = *i;
        Coordinates *oCoords = temp->getCoords();
        if(temp != this)if(isCollision(oCoords))value = temp;
        if(value != NULL)break;
    }
    return value;
}

bool Entity::checkCollisions(std::list<Wall*> walls)
{
    bool value = false;
    for(std::list<Wall*>::iterator i = walls.begin(); i != walls.end(); ++i)
    {
        Wall *temp = *i;
        Coordinates *oCoords = temp->getCoords();
        value = isCollision(oCoords);
        if(value)break;
    }
    return value;
}

bool Entity::checkCollisions(std::list<Door*> doors)
{
    bool value = false;
    for(std::list<Door*>::iterator i = doors.begin(); i != doors.end(); ++i)
    {
        Door *temp = *i;
        Coordinates *oCoords = temp->getCoords();
        if(temp->isOpen() == false)value = isCollision(oCoords);
        if(value)break;
    }
    return value;
}

void Entity::getHit(int damage, int damageType)
{
    health -= damage;
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