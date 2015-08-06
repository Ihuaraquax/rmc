/* 
 * File:   WeaponUI.cpp
 * Author: Qb
 * 
 * Created on 8 luty 2015, 13:38
 */

#include "WeaponUI.h"
#include "globalVariables.h"
#include "Player.h"
#include "TextDisplayer.h"
#include "CollisionDetector.h"

WeaponUI::WeaponUI(bool left) {
    this->leftDisplay = left;
    
    coords = new Coordinates();
    coords->X = 1024 - 205;
    if(leftDisplay)coords->X -= 200;
    coords->Y = Variables::RES_HEIGHT - 95;
    coords->width = 200;
    coords->height = 150;
    
    damageTypeCoords = new Coordinates();
    damageTypeCoords->X = 1024 - 50;
    if(leftDisplay)damageTypeCoords->X -= 200;
    damageTypeCoords->Y = Variables::RES_HEIGHT - 90;
    
    std::string damageTypePath = "images/normalDamageType.png";
    std::string noWeaponPath = "images/noWeapon.png";
    this->image = NULL;
    this->noWeapon = new Image(noWeaponPath, true);
    noWeapon->state = UI;
    this->damageTypeImage = new Image(damageTypePath, true);
    damageTypeImage->state = UI;
}


WeaponUI::~WeaponUI() {
    delete coords;
    delete image;
    delete noWeapon;
    delete damageTypeImage;
}

void WeaponUI::display()
{
    if(image != NULL)
    {
        if(leftDisplay)al_draw_filled_rectangle(1024 - 405, Variables::RES_HEIGHT - 95, 1024-5, Variables::RES_HEIGHT -5, al_map_rgb(75,75,75));
        else al_draw_filled_rectangle(1024 - 205, Variables::RES_HEIGHT - 95, 1024-5, Variables::RES_HEIGHT -5, al_map_rgb(75,75,75));
        image->display(coords);
        damageTypeImage->display(damageTypeCoords);        
        Player * player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
        
        double X = 1024 - 140;
        if(leftDisplay)X -= 200;
        double Y = Variables::RES_HEIGHT - 90;
        TextDisplayer::displayInt(X+25, Y, player->getAmmo(selectedWeapon->ammoType));
        TextDisplayer::displayText(X, Y, " / ");
        TextDisplayer::displayInt(X-25, Y, selectedWeapon->getAmmoCurrent());
        TextDisplayer::displayText(X+40, Y+65, selectedWeapon->getName());        
        displayReloadIndicator(X, Y);
    }
    else
    {
        noWeapon->display(coords);
    }
    Coordinates *mouseCoords = Variables::mouseCoords;
    if(CollisionDetector::isBasicCollision(mouseCoords, coords))
    {
        this->setToolTip();
    }
}

void WeaponUI::displayReloadIndicator(double X, double Y)
{
    if(selectedWeapon->reloading)
    {
        double ratio = 0.0 +selectedWeapon->timeToShoot;
        ratio /= selectedWeapon->reloadSpeed;            
        al_draw_arc(X+75, Y+10, 10, 0 - 90, (ratio * M_PI * 2), al_map_rgb(255,255,255), 2);
    }
}

void WeaponUI::update()
{
}

void WeaponUI::selectWeapon(Weapon* newWeapon)
{
    selectedWeapon = newWeapon;
    reloadImage();
}

void WeaponUI::reloadImage()
{
    if(image != NULL)delete image;    
    if(selectedWeapon != NULL)
    {
        std::string path = selectedWeapon->getDisplayPaths();
        image = new Image(path, true);
        image->state = UI;
    }
}

void WeaponUI::setToolTip()
{
    Variables::session->getTooltip()->setWeapon(selectedWeapon);
}