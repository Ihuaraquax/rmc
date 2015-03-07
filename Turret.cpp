/* 
 * File:   Turret.cpp
 * Author: Qb
 * 
 * Created on 31 styczeń 2015, 21:30
 */

#include "Turret.h"
#include "globalVariables.h"

Turret::Turret() {
    this->coords = new Coordinates();
    this->coords->X = 200;
    this->coords->Y = 200;
    this->coords->angle = -1;
    this->coords->height = Variables::tileSize;
    this->coords->width = Variables::tileSize;
    this->coords->speedX = 0;
    this->coords->speedY = 0;
    std::string lowerPartsPaths[] = {"images/turretLower.png"};
    std::string upperPartsPaths[] = {"images/turretUpper.png"};
    this->lowerPart = new Image(1, lowerPartsPaths, true);
    this->upperPart = new Image(1, upperPartsPaths, true);
    image = NULL;
    lowerPart->state = NORMAL;
    upperPart->state = NORMAL;
    health = 20;
    armor = 0;
    weapons = new Weapon*[2];
    weapons[0] = new Weapon();
    teamId = 1;
    possessedWeapons = 2;
    range = 500;
    aiValue = 100;
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->propagateTurret(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->setObstacle(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->addToEntityList(this);
    currentThreatLevel = 0;
    targetAngle = -1;
    targetCoords = new Coordinates();
    maximumHealth = health;
}
Turret::Turret(double X, double Y) {
    this->coords = new Coordinates();
    this->coords->X = X;
    this->coords->Y = Y;
    this->coords->angle = -1;
    this->coords->height = Variables::tileSize;
    this->coords->width = Variables::tileSize;
    this->coords->speedX = 0;
    this->coords->speedY = 0;
    std::string lowerPartsPaths[] = {"images/turretLower.png"};
    std::string upperPartsPaths[] = {"images/turretUpper.png"};
    this->lowerPart = new Image(1, lowerPartsPaths, true);
    this->upperPart = new Image(1, upperPartsPaths, true);
    image = NULL;
    lowerPart->state = NORMAL;
    upperPart->state = NORMAL;
    health = 20;
    armor = 0;
    weapons = new Weapon*[2];
    weapons[0] = new Weapon();
    teamId = 1;
    possessedWeapons = 2;
    range = 500;
    aiValue = 100;
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->propagateTurret(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->setObstacle(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->addToEntityList(this);
    currentThreatLevel = 0;
    targetAngle = -1;
    targetCoords = new Coordinates();
    maximumHealth = health;
}

void Turret::setCurrentThreatLevel(int currentThreatLevel) {
    this->currentThreatLevel = currentThreatLevel;
}

int Turret::getCurrentThreatLevel() const {
    return currentThreatLevel;
}

void Turret::update()
{
    weapons[0]->update();
    if(targetAngle != -1)
    {
        if(ceil(targetAngle) != ceil(coords->angle))
        {
            if(!turnRight())coords->angle++;
            else coords->angle--;
        }
        this->attack(0);
        targetAngle = -1;
    }
    currentThreatLevel = 0;
}

bool Turret::turnRight()
{
    bool result = false;
    
    if(coords->angle < 180)
    {
        if(targetAngle <= coords->angle + 180)result = true;
    }
    else
    {
        if(targetAngle > coords->angle || targetAngle < (coords->angle - 180))result = true;
    }
    
    return result;
}

void Turret::display()
{
    double tempAngle = coords->angle;
    coords->angle = 0;
    lowerPart->display(coords);
    coords->angle = tempAngle;
    upperPart->display(coords);
}

void Turret::setRange(int range) {
    this->range = range;
}

int Turret::getRange() const {
    return range;
}

void Turret::setTargetAngle(double targetAngle, double X, double Y) {
    this->targetAngle = targetAngle;
    targetCoords->X = X;
    targetCoords->Y = Y;
}

double Turret::getTargetAngle() const {
    return targetAngle;
}

void Turret::executeAgony()
{
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->deleteTurret(this);
}