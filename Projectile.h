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
    virtual ~Projectile();
    void update();
    void setValues(Coordinates *coords, int damage, DAMAGE_TYPE damageType, int angle, int teamId, int range);
    void hit (Entity *target);
    bool isProjectile();
    void virtual executeAgony();
    void virtual setRange(int range);
    
    void setAdditionalDamage(int additionalDamage, int additionalDamageType);
    int getDamage() const;
    void setDamage(int damage);
protected :
    int damage;
    int damageType;
    int additionalDamage;
    int additionalDamageType;
    int range;
    bool explode;
};

#endif	/* PROJECTILE_H */

