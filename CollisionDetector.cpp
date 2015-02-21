/* 
 * File:   CollisionDetector.cpp
 * Author: Qb
 * 
 * Created on 21 styczeń 2015, 20:14
 */

#include "CollisionDetector.h"
#include "templateList.h"
#include "globalVariables.h"

CollisionDetector::CollisionDetector() {
}

bool CollisionDetector::isAnyCollision(ModuleTile* tile, Entity* target)
{
    bool result = false;
    result = isNonEntityCollision(tile,target);
    if(result == false)result = isEntityCollisions(tile, target) != NULL;
    if(target->getCoords()->X > Variables::tileSize * Variables::tilesPerRoom-26)result = true;
    return result;
}

bool CollisionDetector::isNonEntityCollision(ModuleTile *tile, Entity* target)
{
    if(isWallCollisions(tile, target) != NULL)return true;
    return checkCollisions(tile->getDoorList(), target);
}

Entity *CollisionDetector::isEntityCollisions(ModuleTile *tile, Entity* target)
{
    Entity *result = NULL;
    
    result = checkCollisions(tile->getEntityList(), target);
    if(result == NULL)for(int i = 0; i < 8; i++)
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

Wall *CollisionDetector::isWallCollisions(ModuleTile* tile, Entity* target)
{
    Wall* value = NULL;
    Wall **walls = tile->getWallList();
    for(int i = 0; i < 4; i++)
    {
        Wall *temp = walls[i];
        if(temp != NULL)
        {
            Coordinates *oCoords = temp->getCoords();
            if(isCollision(oCoords, target->getCoords()))value = temp;
            if(value != NULL)break;
        }
    }
    for(int j = 0; j < 8; j++)
    {
        if(tile->getAdjacentTiles()[j] != NULL)
        {
            walls = tile->getAdjacentTiles()[j]->getWallList();            
            for(int i = 0; i < 4; i++)
            {
                Wall *temp = walls[i];
                if(temp != NULL)
                {
                    Coordinates *oCoords = temp->getCoords();
                    if(isCollision(oCoords, target->getCoords()))value = temp;
                    if(value != NULL)break;
                }
            }
        }
        if(value != NULL)break;
    }
    return value;
}

Door *CollisionDetector::isDoorCollision(ModuleTile* tile, Entity* target)
{
    Door *value = NULL;
    
    Door **doors = tile->getDoorList();
    for(int i = 0; i < 4; i++)
    {
        if(doors[i] != NULL)if(doors[i]->isOpen() == false)
            if(isCollision(doors[i]->getCoords(), target->getCoords()))
        {
            value = doors[i];
            break;
        }
    }
    
    return value;
}

bool CollisionDetector::checkCollisions(Door **doors, Entity *target)
{
    bool value = false;
    for(int i = 0; i < 4; i++)
    {
        Door *temp = doors[i];
        if(temp != NULL)
        {
            Coordinates *oCoords = temp->getCoords();
            if(temp->isOpen() == false)value = isCollision(oCoords, target->getCoords());
            if(value)break;
        }
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