/* 
 * File:   ExplosiveBarrel.cpp
 * Author: Qb
 * 
 * Created on 16 marzec 2015, 16:46
 */

#include "ExplosiveBarrel.h"
#include "globalVariables.h"
#include "Explosion.h"


void ExplosiveBarrel::setCoords(double X, double Y) {
    this->coords->X = X;
    this->coords->Y = Y;
}
ExplosiveBarrel::ExplosiveBarrel()
{
    this->coords = new Coordinates();
    this->coords->angle = 0;
    this->coords->width = Variables::tileSize;
    this->coords->height = Variables::tileSize;
    this->coords->speedX = 0;
    this->coords->speedY = 0;
    this->image = Variables::images->getByName("barrel");
    this->image->state = NORMAL;
    this->barrelType = 0;
    health = 300;
    teamId = 0;
    maximumHealth = health;
}

void ExplosiveBarrel::update()
{
    
}

void ExplosiveBarrel::executeAgony()
{
    Entity *explosion = new Explosion();
    Explosion *temp = dynamic_cast<Explosion*>(explosion);
    temp->setCoords(coords->X + coords->width/2, coords->Y + coords->height/2);
    temp->setDamageType(explosive);
    temp->setRadius(100);
    temp->setDamage(3000);
    temp->dealDamage();
    Variables::session->getAllEntities()->addEntity(explosion);
}

void ExplosiveBarrel::save(std::fstream& file)
{
    file << "EB" << std::endl;
    saveGeneric(file);
    file << barrelType << ' ';    
    file << std::endl;
}

void ExplosiveBarrel::load(std::fstream& file)
{
    loadGeneric(file);
    file >> barrelType;
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->setObstacle(this);
    this->setStartingTile();
}

Entity *ExplosiveBarrel::CreateBarrel(double X, double Y)
{
    Entity *explosiveBarrel = new ExplosiveBarrel();
    if(X != -1 && Y != -1)explosiveBarrel->setCoords(X,Y);
    return explosiveBarrel;
}