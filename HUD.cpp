/* 
 * File:   HUD.cpp
 * Author: Qb
 * 
 * Created on 8 luty 2015, 00:10
 */

#include "HUD.h"
#include "globalVariables.h"
#include "WeaponUI.h"
#include "Player.h"
#include "EquipmentUI.h"

HUD::HUD() {
    this->coords = new Coordinates();
    coords->X = 0;
    coords->Y = Variables::RES_HEIGHT - 120;
    std::string path[] = {"images/HUDBackground.png"};
    background = new Image(1, path, false);
    mainWeaponUI = new WeaponUI(true);
    secondaryWeaponUI = new WeaponUI(false);
    equipmentUI = new EquipmentUI();
}


HUD::~HUD() {
    delete coords;
    delete background;
    delete equipmentUI;
    delete mainWeaponUI;
    delete secondaryWeaponUI;
}

void HUD::display()
{
    int playerHealthLine = Variables::session->getAllEntities()->getPlayer()->getHealth() * 20;
    background->display(coords);
    al_draw_line(50, Variables::RES_HEIGHT - 75, 50 + playerHealthLine, Variables::RES_HEIGHT - 75, al_map_rgb(255,0,0), 3);
    mainWeaponUI->display();
    secondaryWeaponUI->display();
    displaySelectedSet();
    equipmentUI->display();
}

WeaponUI* HUD::getMainWeaponUI() const {
   return mainWeaponUI;
}

WeaponUI* HUD::getSecondaryWeaponUI() const {
    return secondaryWeaponUI;
}

EquipmentUI* HUD::getEquipmentUI() const {
    return equipmentUI;
}

void HUD::update()
{
    coords->X = 0 + Variables::offsetX;
    coords->Y = Variables::RES_HEIGHT - 120 + Variables::offsetY;
    mainWeaponUI->update();
    secondaryWeaponUI->update();
    equipmentUI->update();
}


void HUD::displaySelectedSet()
{
    int X = Variables::RES_WIDTH-403, Y = Variables::RES_HEIGHT - 115;
    int set = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->getSelecetedWeaponSet();
    if(set == 0)
    {
        al_draw_filled_rectangle(X, Y, X + 133, Y + 20, al_map_rgb(0,0,255));
    }
    else if(set == 1)
    {
        al_draw_filled_rectangle(X + 133, Y, X + 267, Y + 20, al_map_rgb(0,255,0));
    }
    else
    {
        al_draw_filled_rectangle(X + 267, Y, X + 400, Y + 20, al_map_rgb(255,0,0));
    }
}