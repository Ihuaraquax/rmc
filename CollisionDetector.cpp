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
    if(result == NULL)
    {
        for(int i = 0; i < 8; i++)
        {
            if(tile->getAdjacentTiles()[i] != NULL)
                result =checkCollisions(tile->getAdjacentTiles()[i]->getEntityList(), target);
            if(result != NULL)break;
        }
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
        if(temp->data != target)
        {
            if(temp->data->getShape() == rectangle)if(isBasicCollision(oCoords, target->getCoords()))
            {
                value = temp->data;
            }
            if(temp->data->getShape() == triangle)if(isSquareTriangleCollision(oCoords, target->getCoords()))
            {
                value = temp->data;
            }
        }
        if(value == target->getIgnoreCollisionEntity())value = NULL;
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
            if(isBasicCollision(oCoords, target->getCoords()))value = temp;
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
                    if(isBasicCollision(oCoords, target->getCoords()))value = temp;
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
            if(isBasicCollision(doors[i]->getCoords(), target->getCoords()))
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
            if(temp->isOpen() == false)value = isBasicCollision(oCoords, target->getCoords());
            if(value)break;
        }
    }
    return value;
}
bool CollisionDetector::isBasicCollision(Coordinates *oCoords, Coordinates*targetCoords)
{
    bool value = true;
    if(oCoords->X + oCoords->width < targetCoords->X || oCoords->X > targetCoords->X  + targetCoords->width ||
       oCoords->Y + oCoords->height < targetCoords->Y || oCoords->Y  > targetCoords->Y + targetCoords->height)value = false;
    return value;
}

bool CollisionDetector::isSquareTriangleCollision(Coordinates *otherCoords, Coordinates *targetCoords)
{
    bool result = isBasicCollision(otherCoords, targetCoords);
    if(result == true)
    {
        if(otherCoords->angle == 0)
        {
            if((targetCoords->X - otherCoords->X) + (targetCoords->Y - otherCoords->Y) > (otherCoords->width/2 + otherCoords->height/2))result = false;
        } else if(otherCoords->angle == 90)
        {
            if((otherCoords->X - targetCoords->X + targetCoords->width) + (targetCoords->Y - otherCoords->Y) > (otherCoords->width/2 + otherCoords->height/2))result = false;
        } else if(otherCoords->angle == 180)
        {
            if((otherCoords->X - targetCoords->X + targetCoords->width) + (otherCoords->Y - targetCoords->Y + targetCoords->height) > (otherCoords->width/2 + otherCoords->height/2))result = false;
        } else if(otherCoords->angle == 270)
        {
            if((targetCoords->X - otherCoords->X) + (otherCoords->Y - targetCoords->Y + targetCoords->height) > (otherCoords->width/2 + otherCoords->height/2))result = false;
        }
    }
    return result;
}