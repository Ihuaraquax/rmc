/* 
 * File:   Obstacle.cpp
 * Author: Qb
 * 
 * Created on 1 luty 2015, 12:48
 */

#include "Obstacle.h"
#include "globalVariables.h"

Obstacle::Obstacle(double X, double Y) {
    this->coords = new Coordinates();
    this->health = 1000;
    this->maximumHealth = health;
    this->armor = 1;
    this->coords->height = Variables::tileSize;
    this->coords->width = Variables::tileSize;
    this->coords->X = X;
    this->coords->Y = Y;
    for(int i = 0; i < Variables::damageTypeCount; i++)elementalResists[i] = 0.5;
    std::string paths[] = {"images/table.png"};
    std::string paths2[] = {"images/tableDamaged1.png"};
    std::string paths3[] = {"images/tableDamaged2.png"};
    this->image = new Image(1, paths, true);
    this->damagedImage = new Image(1, paths2, true);
    this->damagedImage2 = new Image(1, paths3, true);
    this->image->state = NORMAL;
    maximumHealth = health;
}


bool Obstacle::isBarricade()
{
    return true;
}

void Obstacle::display()
{
    if(health >= maximumHealth * 0.75)image->display(coords);
    else if(health >= maximumHealth * 0.45)damagedImage->display(coords);
    else damagedImage2->display(coords);
}