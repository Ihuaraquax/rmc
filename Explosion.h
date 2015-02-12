/* 
 * File:   Explosion.h
 * Author: Qb
 *
 * Created on 10 luty 2015, 19:24
 */

#ifndef EXPLOSION_H
#define	EXPLOSION_H
#include "Entity.h"

class Explosion : public Entity{
public:
    Explosion();
    virtual ~Explosion();
    void update();
    void display();
    void dealDamage();
    
    void setCoords(double X, double Y);
    void setRadius(int radius);
    void setDamageType(DAMAGE_TYPE damageType);
    void setDamage(int damage);
private:
    int damage;
    DAMAGE_TYPE damageType;
    int radius;
};

#endif	/* EXPLOSION_H */

