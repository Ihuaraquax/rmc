/* 
 * File:   Explosives.cpp
 * Author: Qb
 * 
 * Created on 16 marzec 2015, 17:35
 */

#include "Explosives.h"
#include "globalVariables.h"
#include "Explosion.h"

Explosives::Explosives(double X, double Y) {
    this->coords = new Coordinates();
    this->coords->X = X;
    this->coords->Y = Y;
    this->coords->angle = 0;
    this->coords->height = 50;
    this->coords->width = 50;
    this->coords->speedX = 0;
    this->coords->speedY = 0;
    std::string paths[] = {"images/dynamite.png"};
    this->image = new Image(1, paths, true);
    this->image->state = NORMAL;
    health = 450;
    teamId = 0;
    Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->addToThreatLevel(threatLevel);
    maximumHealth = health;
}

void Explosives::update()
{
    health--;
}

void Explosives::executeAgony()
{
    Entity *explosion = new Explosion();
    Explosion *temp = dynamic_cast<Explosion*>(explosion);
    temp->setCoords(coords->X, coords->Y);
    temp->setDamageType(explosive);
    temp->setRadius(175);
    temp->setDamage(5000);
    temp->dealDamage();
    Variables::session->getAllEntities()->addEntity(explosion);
}

void Explosives::save(std::fstream& file)
{
    file << "EX" << std::endl;
    saveGeneric(file);
    file << std::endl;
}