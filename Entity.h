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
    bool virtual isBarricade();
    
    int getAiValue() const;
    void virtual executeAgony();
    int getArmor() const;
    
    void heal(int healAmount);
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
    int aiValue;
    int maximumHealth;
    
    int criticalChance;
    int criticalDamage;
    double accuracy;
};

#endif	/* ENTITY_H */

