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
    open = true;
}

Door::Door(const Door& orig) {
}

Door::~Door() {
//    delete coords;
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