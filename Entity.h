/* 
 * File:   Entity.h
 * Author: Qb
 *
 * Created on 4 listopad 2014, 22:37
 */

#ifndef ENTITY_H
#define	ENTITY_H
#include <list>
#include "Image.h"
#include "Coordinates.h"
#include "Wall.h"
#include "Door.h"
#include "Weapon.h"
#include "templateList.h"
#include "DamageTypeEnum.h"

class Entity {
public:
    Entity();
    virtual ~Entity();
    
    void virtual update();
    void virtual display();
    void attack(int weapon);
    
    void setStartingTile();
    void getHit(int damage, int damageType);
    
    Coordinates* getCoords() const;
    int getHealth() const;
    int getTeamId() const;
    bool virtual isProjectile();
protected:
    void move(double X, double Y);
    Entity *isCollision();
    
    Image *image;
    Coordinates *coords;
    Weapon **weapons;
    int possessedWeapons;
    int health;
    Coordinates *targetCoords;
    int teamId;
    double *elementalResists;
    int armor;
    int threatLevel;
};

#endif	/* ENTITY_H */

