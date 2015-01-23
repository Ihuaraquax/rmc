/* 
 * File:   Weapon.cpp
 * Author: Qb
 * 
 * Created on 6 styczeń 2015, 12:50
 */

#include "Weapon.h"
#include "globalVariables.h"
#include "Projectile.h"

Weapon::Weapon() {
    ammoMax = 100;
    ammoCurrent = 100;
    reloadSpeed = 120;
    damage = 10;
    cooldown = 20;
    timeToShoot = 0;
    reloading = false;
    damageType = normal;
}

void Weapon::update()
{
    if(timeToShoot > 0)timeToShoot--;
    if(ammoCurrent == 0 && !reloading)reload();
    if(timeToShoot == 0 && reloading)
    {
        ammoCurrent = ammoMax;
        reloading = false;
    }
}

void Weapon::shoot(Coordinates *coords, int angle, int team)
{
    if(!reloading && timeToShoot == 0)
    {
        ammoCurrent--;
        timeToShoot = cooldown;
        Entity *bullet = new Projectile();;
        dynamic_cast<Projectile*>(bullet)->setValues(coords, damage, damageType, angle, team);
        Variables::session->getAllEntities()->addEntity(bullet);
    }
}

void Weapon::reload()
{
    timeToShoot = reloadSpeed;
    reloading = true;
}