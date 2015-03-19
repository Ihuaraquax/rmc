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

void Obstacle::setAsWall()
{
    delete image;
    delete damagedImage;
    delete damagedImage2;
    
    std::string paths[] = {"images/wall/stoneWall1.jpg"};
    std::string paths2[] = {"images/wall/stoneWall1Damaged.jpg"};
    std::string paths3[] = {"images/wall/stoneWall1Damaged2.jpg"};
    
    this->image = new Image(1, paths, true);
    this->damagedImage = new Image(1, paths2, true);
    this->damagedImage2 = new Image(1, paths3, true);
}

void Obstacle::setAsCornerWall(int corner)
{
    this->coords->angle = 0;
    for(int i = 0; i < corner-2; i++)coords->angle += 90;
    delete image;
    delete damagedImage;
    delete damagedImage2;
    
    std::string paths[] = {"images/wall/cornerWall1.png"};
    std::string paths2[] = {"images/wall/cornerWallDamaged.png"};
    std::string paths3[] = {"images/wall/cornerWallDamaged2.png"};
    
    this->image = new Image(1, paths, true);
    this->image->state = NORMAL;
    this->damagedImage = new Image(1, paths2, true);
    this->damagedImage->state = NORMAL;
    this->damagedImage2 = new Image(1, paths3, true);
    this->damagedImage2->state = NORMAL;
}


bool Obstacle::isBarricade()
{
    return true;
}

void Obstacle::setStartingTile()
{
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->addToEntityList(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->setObstacle(this);
}

void Obstacle::display()
{
    if(health >= maximumHealth * 0.75)image->display(coords);
    else if(health >= maximumHealth * 0.45)damagedImage->display(coords);
    else damagedImage2->display(coords);
}