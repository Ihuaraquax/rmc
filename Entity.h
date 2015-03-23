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
#include "GenericBuffer.h"
#include "EntityShape.h"

class Entity {
public:
    Entity();
    virtual ~Entity();
    
    void virtual update();
    void virtual display();
    void virtual attack(int weapon);
    
    void virtual setStartingTile();
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
    double getValueOfBuffer(int type);
    void updateBuffers();
    void addBuffer(GenericBuffer *buffer);
    void setCoords(double X, double Y);
    EntityShape getShape() const;
    
    void adaptToModificators();
protected:
    void move(double X, double Y);
    Entity *isCollision();
    double getSmallestResistance();
    
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
    
    templateList<GenericBuffer> *bufferList;
    bool bleeds;
    EntityShape shape;
};

#endif	/* ENTITY_H */

