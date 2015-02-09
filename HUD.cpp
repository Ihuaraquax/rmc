/* 
 * File:   HUD.cpp
 * Author: Qb
 * 
 * Created on 8 luty 2015, 00:10
 */

#include "HUD.h"
#include "globalVariables.h"
#include "WeaponUI.h"

HUD::HUD() {
    this->coords = new Coordinates();
    coords->X = 0;
    coords->Y = Variables::RES_HEIGHT - 100;
    std::string path[] = {"images/HUDBackground.png"};
    background = new Image(1, path, false);
    mainWeaponUI = new WeaponUI(true);
    secondaryWeaponUI = new WeaponUI(false);
}


HUD::~HUD() {
    delete coords;
    delete background;
}

void HUD::display()
{
    int playerHealthLine = Variables::session->getAllEntities()->getPlayer()->getHealth() * 35;
    background->display(coords);
    al_draw_line(50, Variables::RES_HEIGHT - 75, 50 + playerHealthLine, Variables::RES_HEIGHT - 75, al_map_rgb(255,0,0), 3);
    mainWeaponUI->display();
    secondaryWeaponUI->display();
}

WeaponUI* HUD::getMainWeaponUI() const {
   return mainWeaponUI;
}

WeaponUI* HUD::getSecondaryWeaponUI() const {
    return secondaryWeaponUI;
}

void HUD::update()
{
    coords->X = 0 + Variables::offsetX;
    coords->Y = Variables::RES_HEIGHT - 100 + Variables::offsetY;
    mainWeaponUI->update();
    secondaryWeaponUI->update();
}

