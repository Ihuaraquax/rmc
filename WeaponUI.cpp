/* 
 * File:   WeaponUI.cpp
 * Author: Qb
 * 
 * Created on 8 luty 2015, 13:38
 */

#include "WeaponUI.h"
#include "globalVariables.h"
#include "Player.h"

WeaponUI::WeaponUI(bool left) {
    this->leftDisplay = left;
    
    coords = new Coordinates();
    coords->X = Variables::RES_WIDTH - 205;
    if(leftDisplay)coords->X -= 200;
    coords->Y = Variables::RES_HEIGHT - 95;
    
    damageTypeCoords = new Coordinates();
    damageTypeCoords->X = Variables::RES_WIDTH - 50;
    if(leftDisplay)damageTypeCoords->X -= 200;
    damageTypeCoords->Y = Variables::RES_HEIGHT - 90;
    
    std::string damageTypePaths[] = {"images/normalDamageType.png"};
    std::string noWeaponPaths[] = {"images/noWeapon.png"};
    this->image = NULL;
    this->noWeapon = new Image(1, noWeaponPaths, true);
    noWeapon->state = UI;
    this->damageTypeImage = new Image(1, damageTypePaths, true);
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
        if(leftDisplay)al_draw_filled_rectangle(Variables::RES_WIDTH - 405, Variables::RES_HEIGHT - 95, Variables::RES_WIDTH-5, Variables::RES_HEIGHT -5, al_map_rgb(75,75,75));
        else al_draw_filled_rectangle(Variables::RES_WIDTH - 205, Variables::RES_HEIGHT - 95, Variables::RES_WIDTH-5, Variables::RES_HEIGHT -5, al_map_rgb(75,75,75));
        image->display(coords);
        damageTypeImage->display(damageTypeCoords);

        char ammoMax[6], ammoLeft[4];
        itoa(dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->getAmmo(selectedWeapon->ammoType) ,ammoMax, 10);
        itoa(selectedWeapon->getAmmoCurrent(), ammoLeft, 10);
        double X = Variables::RES_WIDTH - 140;
        if(leftDisplay)X -= 200;
        double Y = Variables::RES_HEIGHT - 90;
        al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X + 25, Y, ALLEGRO_ALIGN_CENTER, ammoMax);
        al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y, ALLEGRO_ALIGN_CENTER, " / ");
        al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X - 25, Y, ALLEGRO_ALIGN_CENTER, ammoLeft);
        
        char *name = new char[selectedWeapon->getName().length()+1];
        strcpy(name, selectedWeapon->getName().c_str());
        al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X + 40, Y+65, ALLEGRO_ALIGN_CENTER, name);
        
        displayReloadIndicator(X, Y);
    }
    else
    {
        noWeapon->display(coords);
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
    if(image != NULL)delete image;
    if(newWeapon != NULL)
    {
        std::string paths[] = {selectedWeapon->getDisplayPaths()};
        image = new Image(1, paths, true);
        image->state = UI;
    }
}