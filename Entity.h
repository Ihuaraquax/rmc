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
#include "Animation.h"
#include <fstream>

class Entity {
public:
    Entity();
    virtual ~Entity();
    
    void virtual update();
    void virtual display();
    void virtual displayPlan();
    void virtual attack(int weapon);
    
    void virtual setStartingTile();
    void virtual getHit(int damage, int damageType);
    
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
    void virtual setCoords(double X, double Y);
    EntityShape getShape() const;
    
    void virtual adaptToModificators();
    void virtual save(std::fstream &savefile);
    void virtual load(std::fstream &savefile);
    void saveGeneric(std::fstream &file);
    void virtual loadGeneric(std::fstream &file);
    void setPlanCoords(int X, int Y);
    
    void virtual RCUse();
    Entity* getIgnoreCollisionEntity() const;
    void setIgnoreCollisionEntity(Entity* ignoreCollisionEntity);
    Coordinates* getPlanCoords() const;
    int getModuleThreatLevel() const;
    std::string virtual getEntityType();
protected:
    void move(double X, double Y);
    Entity *isCollision();
    double getSmallestResistance();
    
    Image *image;
    Coordinates *coords;
    Coordinates *planCoords;
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
    double criticalDamage;
    double accuracy;
    
    templateList<GenericBuffer> *bufferList;
    bool bleeds;
    EntityShape shape;
    Entity *ignoreCollisionEntity;
    int moduleThreatLevel = 0;
    Animation *animation;
};

#endif	/* ENTITY_H */

