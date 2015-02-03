/* 
 * File:   AllEntities.h
 * Author: Qb
 *
 * Created on 16 listopad 2014, 11:31
 */

#ifndef ALLENTITIES_H
#define	ALLENTITIES_H
#include <list>
#include "Entity.h"

class AllEntities {
public:
    AllEntities();
    ~AllEntities();
    void update();
    void display();
    void collisions();
    void loadFile();
    void loadNew();
    void addEntity(Entity *newEntity);
    void deleteEntity(Entity *toDelete);
    Entity* getPlayer() const;
    void deleteDead();
    void createObstacles();
private:
    std::list<Entity*> entityList;
    Entity *player;
};

#endif	/* ALLENTITIES_H */

