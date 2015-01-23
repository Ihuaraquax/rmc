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

class Entity {
public:
    Entity();
    Entity(const Entity& orig);
    virtual ~Entity();
    void virtual update();
    void display();
    void move(double X, double Y);
    bool isCollision(Coordinates *otherCoords);
    Entity* checkCollisions(std::list<Entity*> otherEntities);
    bool checkCollisions(std::list<Wall*> walls);
    bool checkCollisions(std::list<Door*> doors);
    void loadFile();
    void getHit(int damage, int damageType);
    Coordinates* getCoords() const;
    int getHealth() const;
    void attack(bool leftWeapon);
    int getTeamId() const;
    void setStartingTile();
protected:
    Image *image;
    Coordinates *coords;
    Weapon **weapons;
    bool projectile;
    int possessedWeapons;
    int health;
    double shootingAngle;
    int teamId;
};

#endif	/* ENTITY_H */

