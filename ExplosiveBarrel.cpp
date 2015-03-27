/* 
 * File:   ExplosiveBarrel.cpp
 * Author: Qb
 * 
 * Created on 16 marzec 2015, 16:46
 */

#include "ExplosiveBarrel.h"
#include "globalVariables.h"
#include "Explosion.h"


ExplosiveBarrel::ExplosiveBarrel(double X, double Y, int type) {
    this->coords = new Coordinates();
    this->coords->X = X;
    this->coords->Y = Y;
    this->coords->angle = 0;
    this->coords->height = 50;
    this->coords->width = 50;
    this->coords->speedX = 0;
    this->coords->speedY = 0;
    std::string paths[] = {"images/barrel.png"};
    this->image = new Image(1, paths, true);
    this->image->state = NORMAL;
    health = 300;
    teamId = 0;
    Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->addToThreatLevel(threatLevel);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X,Y)->setObstacle(this);
    this->setStartingTile();
    maximumHealth = health;
    this->barrelType = type;
}

void ExplosiveBarrel::update()
{
    
}

void ExplosiveBarrel::executeAgony()
{
    Entity *explosion = new Explosion();
    Explosion *temp = dynamic_cast<Explosion*>(explosion);
    temp->setCoords(coords->X + coords->width/2, coords->Y + coords->height/2);
    temp->setDamageType(normal);
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