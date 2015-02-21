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
    aiValue = 0;
    maximumHealth = health;
}

Entity::~Entity() {
    ModuleTile *tile = Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y);
    if(tile != NULL)tile->addToThreatLevel(-threatLevel);
    delete coords;
    if(image != NULL)delete image;
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
        currentTile->addToThreatLevel(-threatLevel);
        newTile->addToEntityList(this);
        newTile->addToThreatLevel(threatLevel);
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

void Entity::attack(int weapon)
{
    weapons[weapon]->shoot(coords, targetCoords, teamId);
}

int Entity::getTeamId() const {
    return teamId;
}

void Entity::setStartingTile()
{
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->addToEntityList(this);
}


bool Entity::isProjectile()
{
    return false;
}

bool Entity::isBarricade()
{
    return false;
}

int Entity::getAiValue() const {
    return aiValue;
}

void Entity::executeAgony()
{
    
}

int Entity::getArmor() const {
    return armor;
}

void Entity::heal(int healAmount)
{
    this->health += healAmount;
    if(this->health > this->maximumHealth) health = maximumHealth;
}