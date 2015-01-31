/* 
 * File:   Turret.cpp
 * Author: Qb
 * 
 * Created on 31 styczeń 2015, 21:30
 */

#include "Turret.h"
#include "globalVariables.h"

Turret::Turret() {
    this->coords = new Coordinates();
    this->coords->X = 215;
    this->coords->Y = 215;
    this->coords->angle = 0;
    this->coords->height = 50;
    this->coords->width = 50;
    this->coords->speedX = 0;
    this->coords->speedY = 0;
    std::string lowerPartsPaths[] = {"images/turretLower.png"};
    std::string upperPartsPaths[] = {"images/turretUpper.png"};
    this->lowerPart = new Image(1, lowerPartsPaths, true);
    this->upperPart = new Image(1, upperPartsPaths, true);
    image = NULL;
    lowerPart->state = NORMAL;
    upperPart->state = NORMAL;
    health = 20;
    weapons = new Weapon*[2];
    weapons[0] = new Weapon();
    teamId = 1;
    possessedWeapons = 2;
}

void Turret::update()
{
    weapons[0]->update();
    if(Variables::currentFrame % 1 == 0)
    {
        coords->angle++;
        if(coords->angle > 360)coords->angle = 0;
    }
}

void Turret::display()
{
    double tempAngle = coords->angle;
    coords->angle = 0;
    lowerPart->display(coords);
    coords->angle = tempAngle;
    upperPart->display(coords);
}