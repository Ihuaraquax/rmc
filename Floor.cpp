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
    this->coords->width *= Variables::ScaleX * Variables::scale;
    this->coords->height *= Variables::ScaleY * Variables::scale;
}

void Floor::setImage(Image* image)
{
    this->floorPattern = image;
}

void Floor::update()
{
    
}

void Floor::displayPlan()
{
    floorPattern->display(planCoords);
}


void Floor::setPlanCoords(int X, int Y)
{
    planCoords->X = (coords->X + X * (Variables::tileSize * Variables::tilesPerRoom + 100));
    planCoords->Y = (coords->Y + Y * (Variables::tileSize * Variables::tilesPerRoom + 100));
}