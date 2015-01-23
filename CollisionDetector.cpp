/* 
 * File:   CollisionDetector.cpp
 * Author: Qb
 * 
 * Created on 21 styczeń 2015, 20:14
 */

#include "CollisionDetector.h"

CollisionDetector::CollisionDetector() {
}

bool CollisionDetector::isAnyCollision(ModuleTile* tile, Entity* target)
{
    bool result = false;
    result = isNonEntityCollision(tile,target);
    if(result == false)result = isEntityCollisions(tile, target) != NULL;
    return result;
}

bool CollisionDetector::isNonEntityCollision(ModuleTile *tile, Entity* target)
{
    bool result = false;
    result = checkCollisions(tile->getWallList(), target);
    if(result == false)result = checkCollisions(tile->getDoorList(), target);
    return result;
}

Entity *CollisionDetector::isEntityCollisions(ModuleTile *tile, Entity* target)
{
    Entity *result = NULL;
    
    result = checkCollisions(tile->getEntityList(), target);
    if(result == NULL)for(int i = 0; i < tile->getAdjacentTilesCount(); i++)
    {
        if(tile->getAdjacentTiles()[i] != NULL)
            result =checkCollisions(tile->getAdjacentTiles()[i]->getEntityList(), target);
        if(result != NULL)break;
    }
    
    return result;
}

Entity* CollisionDetector::checkCollisions(templateList<Entity> *otherEntities, Entity *target)
{
    templateList<Entity> *temp = otherEntities;
    Entity* value = NULL;
    while(temp != NULL)
    {
        Coordinates *oCoords = temp->data->getCoords();
        if(temp->data != target)if(isCollision(oCoords, target->getCoords()))
        {
            value = temp->data;
        }
        if(value != NULL)break;
        temp = temp -> next;
    }
    return value;
}

bool CollisionDetector::checkCollisions(std::list<Wall*> walls, Entity *target)
{
    bool value = false;
    for(std::list<Wall*>::iterator i = walls.begin(); i != walls.end(); ++i)
    {
        Wall *temp = *i;
        Coordinates *oCoords = temp->getCoords();
        value = isCollision(oCoords, target->getCoords());
        if(value)break;
    }
    return value;
}

bool CollisionDetector::checkCollisions(std::list<Door*> doors, Entity *target)
{
    bool value = false;
    for(std::list<Door*>::iterator i = doors.begin(); i != doors.end(); ++i)
    {
        Door *temp = *i;
        Coordinates *oCoords = temp->getCoords();
        if(temp->isOpen() == false)value = isCollision(oCoords, target->getCoords());
        if(value)break;
    }
    return value;
}
bool CollisionDetector::isCollision(Coordinates *oCoords, Coordinates*targetCoords)
{
    bool value = true;
    if(oCoords->X + oCoords->width < targetCoords->X || oCoords->X > targetCoords->X  + targetCoords->width ||
       oCoords->Y + oCoords->height < targetCoords->Y || oCoords->Y  > targetCoords->Y + targetCoords->height)value = false;
    return value;
}