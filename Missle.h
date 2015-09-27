/* 
 * File:   Missle.h
 * Author: Qb
 *
 * Created on 3 marzec 2015, 18:53
 */

#ifndef MISSLE_H
#define	MISSLE_H
#include "Projectile.h"

class Missle : public Projectile {
public:
    Missle(bool isMIRV);
    void executeAgony();
    void update();
    bool isProjectile();
    void setRange(int range);
    int getProjectileType();
private:
    bool MIRV;
};

#endif	/* MISSLE_H */

