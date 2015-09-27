/* 
 * File:   Obstacle.cpp
 * Author: Qb
 * 
 * Created on 1 luty 2015, 12:48
 */

#include "Obstacle.h"
#include "globalVariables.h"

Obstacle::Obstacle()
{
    this->health = 1000;
    this->maximumHealth = health;
    this->coords = new Coordinates();
    this->coords->width = Variables::tileSize;
    this->coords->height = Variables::tileSize;
    this->coords->angle = 0;
    this->coords->speedX = 0;
    this->coords->speedY = 0;
    this->image = Variables::images->getByName("table");
    this->damagedImage = Variables::images->getByName("tableDamaged1");
    this->damagedImage2 = Variables::images->getByName("tableDamaged2");
    image->state = NORMAL;
    damagedImage->state = NORMAL;
    damagedImage2->state = NORMAL;
    isWall = false;
    bleeds = false;
    this->armor = 1;
    for(int i = 0; i < Variables::damageTypeCount; i++)elementalResists[i] = 0.5;
    elementalResists[explosive] = 0;
}

void Obstacle::setCoords(double X, double Y) {
    this->coords->X = X;
    this->coords->Y = Y;
    maximumHealth = health;
}

void Obstacle::setAsWall()
{
    this->image = Variables::images->getByName("stoneWall1");
    this->damagedImage = Variables::images->getByName("stoneWall1Damaged");
    this->damagedImage2 = Variables::images->getByName("stoneWall1Damaged2");
    isWall = true;
}

void Obstacle::setAsCornerWall(int corner)
{
    shape = triangle;
    isWall = true;
    this->coords->angle = 0;
    for(int i = 0; i < corner-2; i++)coords->angle += 90;
    
    this->image = Variables::images->getByName("cornerWall1");
    this->damagedImage = Variables::images->getByName("cornerWallDamaged");
    this->damagedImage2 = Variables::images->getByName("cornerWallDamaged2");
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

void Obstacle::save(std::fstream& file)
{
    if(isWall)
    {
        if(this->shape == rectangle)file << "WA" << std::endl;
        else file << "CW" << std::endl;
    }
    else
    {
        file << "OB" << std::endl;
    }
    saveGeneric(file);
    file << std::endl;
}

void Obstacle::load(std::fstream& file)
{
    loadGeneric(file);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->setObstacle(this);
}

Entity *Obstacle::CreateObstacle(double X, double Y)
{
    Entity *obstacle = new Obstacle();
    if(X != -1 && Y != -1)obstacle->setCoords(X,Y);
    return obstacle;
}

void Obstacle::displayPlan()
{
    if(health >= maximumHealth * 0.75)image->display(planCoords);
    else if(health >= maximumHealth * 0.45)damagedImage->display(planCoords);
    else damagedImage2->display(planCoords);
}