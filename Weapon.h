/* 
 * File:   Weapon.h
 * Author: Qb
 *
 * Created on 6 styczeń 2015, 12:50
 */

#ifndef WEAPON_H
#define	WEAPON_H
#include "Coordinates.h"
#include "DamageTypeEnum.h"

class Weapon {
public:
    Weapon();
    void update();
    void shoot(Coordinates *coords, int angle, int team);
    void reload();
private:
    int ammoMax;
    int ammoCurrent;
    int reloadSpeed;
    int damage;
    DAMAGE_TYPE damageType;
    int cooldown;
    int timeToShoot;
    bool reloading;
};

#endif	/* WEAPON_H */

