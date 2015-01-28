/* 
 * File:   CollisionDetector.h
 * Author: Qb
 *
 * Created on 21 styczeń 2015, 20:14
 */

#ifndef COLLISIONDETECTOR_H
#define	COLLISIONDETECTOR_H
#include "Wall.h"
#include "Entity.h"
#include "Door.h"
#include "ModuleTile.h"

class CollisionDetector {
public:
    CollisionDetector();
    
    static bool isAnyCollision(ModuleTile *tile, Entity* target);
    static bool isNonEntityCollision(ModuleTile *tile, Entity* target);
    static Entity *isEntityCollisions(ModuleTile *tile, Entity* target);
    static Wall* isWallCollisions(ModuleTile *tile, Entity *target);
private:
    static bool isCollision(Coordinates *otherCoords, Coordinates *targetCoords);
    static Entity *checkCollisions(templateList<Entity> *otherEntities, Entity *target);
    static bool checkCollisions(Door **doors, Entity *target);
};

#endif	/* COLLISIONDETECTOR_H */

