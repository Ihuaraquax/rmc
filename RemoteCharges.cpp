/* 
 * File:   RemoteCharges.cpp
 * Author: Qb
 * 
 * Created on 17 marzec 2015, 21:46
 */

#include "RemoteCharges.h"
#include "Explosion.h"
#include "globalVariables.h"

RemoteCharges::RemoteCharges(double X, double Y) {
    this->coords = new Coordinates();
    this->coords->X = X;
    this->coords->Y = Y;
    this->coords->angle = 0;
    this->coords->height = 50;
    this->coords->width = 50;
    this->coords->speedX = 0;
    this->coords->speedY = 0;
    std::string paths[] = {"images/remoteCharge.jpg"};
    this->image = new Image(1, paths, true);
    this->image->state = NORMAL;
    health = 450;
    teamId = 0;
    Variables::session->getMap()
            ->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->addToThreatLevel(threatLevel);
    maximumHealth = health;
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