/* 
 * File:   HUD.h
 * Author: Qb
 *
 * Created on 8 luty 2015, 00:10
 */

#ifndef HUD_H
#define	HUD_H
#include "Image.h"
#include "Coordinates.h"
#include "WeaponUI.h"

class HUD {
public:
    HUD();
    virtual ~HUD();
    void update();
    void display();
    WeaponUI* getMainWeaponUI() const;
    WeaponUI* getSecondaryWeaponUI() const;
private:
    Image *background;
    Coordinates *coords;
    WeaponUI *mainWeaponUI;
    WeaponUI *secondaryWeaponUI;
};

#endif	/* HUD_H */

