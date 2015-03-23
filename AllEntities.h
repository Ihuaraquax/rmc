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
    void init();
    void update();
    void display();
    void loadFile();
    void loadNew();
    void addEntity(Entity *newEntity);
    void deleteEntity(Entity *toDelete);
    Entity* getPlayer() const;
    
    void addRemoteCharge(Entity *toAdd);
    bool deleteRemoteCharge(int signalId);
    void applyModifiers();
private:
    void deleteDead();
    void createObstacles();
    void createDoors();
    void collisions();
    
    std::list<Entity*> entityList;
    templateList<Entity> *remoteCharges;
    Entity *player;
};

#endif	/* ALLENTITIES_H */

