/* 
 * File:   Wall.cpp
 * Author: Qb
 * 
 * Created on 23 listopad 2014, 18:54
 */

#include "Wall.h"
#include "globalVariables.h"

Wall::Wall() {
}

Wall::~Wall()
{
    delete coords;
}

void Wall::display()
{
    double X = coords->X - Variables::offsetX;
    double Y = coords->Y - Variables::offsetY;
    al_draw_filled_rectangle(X, Y, X + coords->width, Y + coords->height,
            al_map_rgb(255,0,0));
}

void Wall::update()
{
    
}

void Wall::setCoords(Coordinates* coords)
{
    this->coords = coords;
}

bool Wall::isOnCoords(int X, int Y)
{
    if(X == coords->X/wallSize && Y == coords->Y/wallSize)return true;
    return false;
}

Coordinates* Wall::getCoords() const {
    return coords;
}