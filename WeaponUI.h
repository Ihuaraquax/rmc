/* 
 * File:   WeaponUI.h
 * Author: Qb
 *
 * Created on 8 luty 2015, 13:38
 */

#ifndef WEAPONUI_H
#define	WEAPONUI_H
#include "Weapon.h"
#include "Image.h"
#include "Coordinates.h"

class WeaponUI {
public:
    WeaponUI(bool left);
    virtual ~WeaponUI();
    void selectWeapon(Weapon *newWeapon);
    void display();
    void update();
private:
    bool leftDisplay;
    Weapon *selectedWeapon;
    Image *image;
    Image *damageTypeImage;
    Image *noWeapon;
    Coordinates *coords;
    Coordinates *damageTypeCoords;
};

#endif	/* WEAPONUI_H */
