/* 
 * File:   Wall.cpp
 * Author: Qb
 * 
 * Created on 23 listopad 2014, 18:54
 */

#include "Wall.h"
#include "globalVariables.h"

Wall::Wall() {
    elementalResists = new double[Variables::damageTypeCount];
    health = 100;
    armor = 5;
    for(int i = 0; i < Variables::damageTypeCount; i++)this->elementalResists[i] = 0.5;
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
            al_map_rgb(health *2.55,0,0));
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

void Wall::getHit(int damage, int damageType)
{
    int damageInflicted = (damage - armor) * (1-elementalResists[damageType]);
    if(damageInflicted < 0)damageInflicted = 0;
    health -= damageInflicted;
}

int Wall::getWallSize() const {
    return wallSize;
}

void Wall::setWallSize(int wallSize) {
    this->wallSize = wallSize;
}

int Wall::getHealth() const {
    return health;
}

void Wall::setAsModuleBorderWall()
{
    
    for(int i = 0; i < Variables::damageTypeCount; i++)elementalResists[i] = 1;
    health = 10000;
    armor = 1000;
}