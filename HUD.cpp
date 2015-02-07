/* 
 * File:   HUD.cpp
 * Author: Qb
 * 
 * Created on 8 luty 2015, 00:10
 */

#include "HUD.h"
#include "globalVariables.h"

HUD::HUD() {
    this->coords = new Coordinates();
    coords->X = 0;
    coords->Y = Variables::RES_HEIGHT - 100;
    std::string path[] = {"images/HUDBackground.png"};
    background = new Image(1, path, false);
}


HUD::~HUD() {
    delete coords;
    delete background;
}

void HUD::display()
{
    int playerHealthLine = Variables::session->getAllEntities()->getPlayer()->getHealth() * 40;
    background->display(coords);
    al_draw_line(50, Variables::RES_HEIGHT - 75, 50 + playerHealthLine, Variables::RES_HEIGHT - 75, al_map_rgb(255,0,0), 3);
}

void HUD::update()
{
    coords->X = 0 + Variables::offsetX;
    coords->Y = Variables::RES_HEIGHT - 100 + Variables::offsetY;
}

