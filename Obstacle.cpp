/* 
 * File:   Obstacle.cpp
 * Author: Qb
 * 
 * Created on 1 luty 2015, 12:48
 */

#include "Obstacle.h"

Obstacle::Obstacle(double X, double Y) {
    this->coords = new Coordinates();
    this->health = 100;
    this->armor = 1;
    this->coords->height = 50;
    this->coords->width = 50;
    this->coords->X = X;
    this->coords->Y = Y;
    std::string paths[] = {"images/table.png"};
    this->image = new Image(1, paths, true);
    this->image->state = NORMAL;
}


bool Obstacle::isBarricade()
{
    return true;
}