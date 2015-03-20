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
#include "TimedBuffer.h"
#include "DistanceBuffer.h"
#include "BloodSplatter.h"

Entity::Entity() {
    armor = 0;
    elementalResists = new double[Variables::damageTypeCount];
    for(int i = 0; i < Variables::damageTypeCount; i++)this->elementalResists[i] = 0.0;
    aiValue = 0;
    maximumHealth = health;
    criticalChance = 0;
    criticalDamage = 0;
    accuracy = 0;
    bufferList = NULL;
    bleeds= false;
    shape = rectangle;
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
    
    double speedX = this->coords->speedX + this->getValueOfBuffer(0);
    double speedY = this->coords->speedY + this->getValueOfBuffer(0);
    
    ModuleTile *currentTile = Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y);
    
    this->coords->X += X * speedX;
    ModuleTile *newTile = Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y);
    if(CollisionDetector::isAnyCollision(newTile, this))
    {
        this->coords->X -= X * speedX;
    }
    
    
    this->coords->Y += Y * speedY;
    newTile = Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y);
    if(CollisionDetector::isAnyCollision(newTile, this))
    {
        this->coords->Y -= Y * speedY;
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
    else if (bleeds)
    {
        Decal *decal = new BloodSplatter(coords->X, coords->Y);
        Variables::session->getMap()->getCurrentModule()->getAllDecals()->addDecal(decal);
    }
    health -= damageInflicted;
}

void Entity::attack(int weapon)
{
    if(weapons[weapon]->getWeaponId() != -1)weapons[weapon]->shoot(coords, targetCoords, teamId, criticalChance, criticalDamage, accuracy);
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

double Entity::getValueOfBuffer(int type)
{
    double result = 0;
    templateList<GenericBuffer> *buffers = this->bufferList;
    while(buffers != NULL)
    {
        if(buffers->data->GetBuffType() == type)result += buffers->data->GetBuffValue();
        buffers = buffers->next;
    }
    buffers = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->getBufferList();
    
    while(buffers != NULL)
    {
        if(buffers->data->GetBuffType() == type)
        {
            DistanceBuffer *distanceBuffer = static_cast<DistanceBuffer*>(buffers->data);
            if(distanceBuffer->isInRange(coords->X, coords->Y))result += buffers->data->GetBuffValue();
        }
        buffers = buffers->next;
    }
    return result;
}

void Entity::updateBuffers()
{
    templateList<GenericBuffer> *buffers = this->bufferList;
    while(buffers != NULL)
    {
        static_cast<TimedBuffer*>(buffers->data)->SetBuffTime(static_cast<TimedBuffer*>(buffers->data)->GetBuffTime()-1);
        if(static_cast<TimedBuffer*>(buffers->data)->GetBuffTime() == 0)
        {
            templateList<GenericBuffer> *toDelete = buffers;
            buffers = buffers->next;
            if(toDelete != bufferList)this->bufferList->findPrevious(toDelete->data)->next = buffers;
            else bufferList = buffers;
            delete toDelete->data;
            delete toDelete;
        }
        else buffers = buffers->next;
    }
}

void Entity::addBuffer(GenericBuffer* buffer)
{
    templateList<GenericBuffer> *newBuffer = new templateList<GenericBuffer>();
    newBuffer->data = buffer;
    newBuffer->next = bufferList;
    bufferList = newBuffer;
}

void Entity::setCoords(double X, double Y)
{
    coords->X = X;
    coords->Y = Y;
}

EntityShape Entity::getShape() const {
    return shape;
}