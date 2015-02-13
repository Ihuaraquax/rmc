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
#include <iostream>

class Weapon {
    friend class WeaponLoader;
public:
    Weapon();
    void update();
    void shoot(Coordinates *shooterCoords, Coordinates *targetCoords, int team);
    void reload();
    double getAngle(Coordinates *shooterCoords, Coordinates *targetCoords);
    int getCurrentTargetSize() const;
    int getAmmoCurrent() const;
    int getAmmoMax() const;
    std::string getDisplayPaths() const;
private:
    int ammoMax;
    int ammoCurrent;
    int reloadSpeed;
    int damage;
    DAMAGE_TYPE damageType;
    int cooldown;
    int timeToShoot;
    bool reloading;
    int defaultTargetSize;
    int currentTargetSize;
    int targetSizeIncrement;
    int targetSizeDecrement;
    int targetSizeIncrementSlowDownPoint;
    int projectileCount;
    int range;
    int ammoType;
    int special;
    int weight;
    std::string name;
    std::string displayPaths;
};

#endif	/* WEAPON_H */

