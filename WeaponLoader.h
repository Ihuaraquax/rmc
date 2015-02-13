/* 
 * File:   WeaponLoader.h
 * Author: Qb
 *
 * Created on 12 luty 2015, 18:05
 */

#ifndef WEAPONLOADER_H
#define	WEAPONLOADER_H
#include "Weapon.h"

class WeaponLoader {
    
public:
    WeaponLoader();
    void static loadWeapon(Weapon *weapon, int newWeaponId);
private:
};

#endif	/* WEAPONLOADER_H */

