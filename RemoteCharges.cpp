/* 
 * File:   RemoteCharges.cpp
 * Author: Qb
 * 
 * Created on 17 marzec 2015, 21:46
 */

#include "RemoteCharges.h"
#include "Explosion.h"
#include "globalVariables.h"

RemoteCharges::RemoteCharges()
{
    this->coords = new Coordinates();
    this->coords->width = Variables::tileSize;
    this->coords->height = Variables::tileSize;
    this->coords->angle = 0;
    this->coords->speedX = 0;
    this->coords->speedY = 0;
    this->image = Variables::images->getByName("remoteCharges");
    this->image->state = NORMAL;
    health = 450;
    maximumHealth = health;
}

void RemoteCharges::setCoords(double X, double Y) {
    this->coords->X = X;
    this->coords->Y = Y;
    teamId = 0;
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->addToThreatLevel(threatLevel);
    signalId = 1;
}

void RemoteCharges::setSignalId(int signalId) {
    this->signalId = signalId;
}

int RemoteCharges::getSignalId() const {
    return signalId;
}


void RemoteCharges::update()
{
}

void RemoteCharges::executeAgony()
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

void RemoteCharges::save(std::fstream& file)
{
    file << "RC" << std::endl;
    saveGeneric(file);
    file << this->signalId << ' ';
}

void RemoteCharges::load(std::fstream& file)
{
    loadGeneric(file);
    file >> signalId;
}

Entity *RemoteCharges::CreateCharges(double X, double Y)
{
    Entity *charge = new RemoteCharges();
    if(X != -1 && Y != -1)charge->setCoords(X,Y);
    return charge;
}