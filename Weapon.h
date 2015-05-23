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
    friend class WeaponUI;
public:
    Weapon();
    void update();
    void shoot(Coordinates *shooterCoords, Coordinates *targetCoords, int team, int shooterCriticalChance, double shooterCriticalDamage, double accuracy);
    void shoot(Coordinates *shooterCoords, int team, int shooterCriticalChance, double shooterCriticalDamage, double accuracy);
    void reload();
    double getAngle(Coordinates *shooterCoords, Coordinates *targetCoords);
    int getCurrentTargetSize() const;
    int getAmmoCurrent() const;
    int getAmmoMax() const;
    std::string getDisplayPaths() const;
    std::string getName() const;
    
    void setReloadable(bool reloadable);
    void setPlayerIsWielder(bool playerIsWielder);
    int getAmmoType() const;
    void setAmmoCurrent(int ammoCurrent);
    int getWeaponId() const;
    void setRange(int range);
    void setDamageType(DAMAGE_TYPE damageType);
    void createBlast(Coordinates *shooterCoords);
private:
    void shootMIRV(Coordinates *shooterCoords, int team);
    void decreaseAmmo();
    
    int weaponId;
    int ammoMax;
    int ammoCurrent;
    int reloadSpeed;
    int damage;
    DAMAGE_TYPE damageType;
    int cooldown;
    int timeToShoot;
    bool reloading;
    double defaultTargetSize;
    double currentTargetSize;
    double targetSizeIncrement;
    double targetSizeDecrement;
    double targetSizeIncrementSlowDownPoint;
    int projectileCount;
    int range;
    int ammoType;
    int special;
    int weight;
    std::string name;
    std::string displayPaths;
    int criticalChance;
    double criticalDamage;
    bool playerIsWielder;
    bool reloadable;
};

#endif	/* WEAPON_H */

