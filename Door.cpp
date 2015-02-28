/* 
 * File:   Door.cpp
 * Author: Qb
 * 
 * Created on 23 listopad 2014, 18:54
 */

#include "Door.h"
#include "globalVariables.h"

Door::Door(Coordinates *coords) {
    this->coords = coords;
    open = false;
    elementalResists = new double[Variables::damageTypeCount];
    health = 100;
    armor = 5;
    for(int i = 0; i < Variables::damageTypeCount; i++)this->elementalResists[i] = 0.5;
}


Door::~Door() {
    delete coords;
}

void Door::display()
{
    double X = coords->X - Variables::offsetX;
    double Y = coords->Y - Variables::offsetY;
    if(open)al_draw_filled_rectangle(X, Y, X + coords->width, Y + coords->height,
            al_map_rgb(0,255,0));
    else al_draw_filled_rectangle(X, Y, X + coords->width, Y + coords->height,
            al_map_rgb(0,0,255));
}

void Door::update()
{
    
}

Coordinates* Door::getCoords() const {
    return coords;
}

void Door::setOpen(bool open) {
    this->open = open;
}

bool Door::isOpen() const {
    return open;
}
void Door::getHit(int damage, int damageType)
{
    int damageInflicted = (damage - armor) * (1-elementalResists[damageType]);
    if(damageInflicted < 0)damageInflicted = 0;
    health -= damageInflicted;
}

int Door::getHealth() const {
    return health;
}

void Door::use()
{
    open = !open;
}