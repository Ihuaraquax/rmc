/* 
 * File:   Floor.cpp
 * Author: Qb
 * 
 * Created on 24 listopad 2014, 18:52
 */

#include "Floor.h"
#include "globalVariables.h"
Floor::Floor() {
}

Floor::~Floor()
{
    delete coords;
    delete floorPattern;
}

void Floor::display()
{
    floorPattern->display(coords);
}

void Floor::setCoords(Coordinates* coords)
{
    this->coords = coords;
    this->coords->angle = 0;
    this->coords->width *= Variables::ScaleX;
    this->coords->height *= Variables::ScaleY;
}

void Floor::setImage(Image* image)
{
    this->floorPattern = image;
}

void Floor::update()
{
    
}

