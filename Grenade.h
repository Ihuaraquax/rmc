/* 
 * File:   Grenade.h
 * Author: Qb
 *
 * Created on 3 marzec 2015, 18:53
 */

#ifndef GRENADE_H
#define	GRENADE_H
#include "Projectile.h"

class Grenade : public Projectile {
public:
    Grenade();
    void executeAgony();
    void update();
    bool isProjectile();
    void bounce(bool horizontal);
    void floorBounce();
    int getProjectileType();
    void multiplySpeed(double multiplier);
private:
    int radius;
};

#endif	/* GRENADE_H */

