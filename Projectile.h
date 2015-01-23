/* 
 * File:   Projectile.h
 * Author: Qb
 *
 * Created on 6 styczeń 2015, 12:56
 */

#ifndef PROJECTILE_H
#define	PROJECTILE_H
#include "Entity.h"

class Projectile : public Entity {
public:
    Projectile();
    Projectile(const Projectile& orig);
    virtual ~Projectile();
    void update();
    void setValues(Coordinates *coords, int damage, int damageType, int angle, int teamId);
    void hit (Entity *target);
private:
    int damage;
    int damageType;
};

#endif	/* PROJECTILE_H */

