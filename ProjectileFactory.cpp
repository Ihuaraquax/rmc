/* 
 * File:   ProjectileFactory.cpp
 * Author: Qb
 * 
 * Created on 4 marzec 2015, 20:02
 */

#include "ProjectileFactory.h"
#include "Projectile.h"
#include "Missle.h"
#include "Grenade.h"

Entity *ProjectileFactory::provideProjectile(int weaponId, int weaponModificator)
{
    Entity *projectile;
    if(weaponId == 3 || weaponId == 19) projectile = new Grenade();
    else if(weaponId == 9 || weaponId == 101)projectile = new Missle(false);
    else if(weaponId == 33)projectile = new Missle(true);
    else projectile = new Projectile();
    return projectile;
}