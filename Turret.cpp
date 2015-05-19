/* 
 * File:   Turret.cpp
 * Author: Qb
 * 
 * Created on 31 styczeń 2015, 21:30
 */

#include "Turret.h"
#include "globalVariables.h"
#include "WeaponLoader.h"

Turret::Turret() {    
    this->coords = new Coordinates();
    this->coords->width = Variables::tileSize;
    this->coords->height = Variables::tileSize;
    this->coords->speedX = 0;
    this->coords->speedY = 0;
    std::string lowerPartsPath = "images/turretLower.png";
    std::string upperPartsPath = "images/turretUpper.png";
    this->lowerPart = new Image(lowerPartsPath, true);
    this->upperPart = new Image(upperPartsPath, true);
    lowerPart->state = NORMAL;
    upperPart->state = NORMAL;
    image = NULL;
    targetCoords = new Coordinates();
    health = 200;
    maximumHealth = health;
    armor = 10;
    active = false;
    
    possessedWeapons = 1;
    weapons = new Weapon*[1];
    weapons[0] = new Weapon();
    WeaponLoader::loadWeapon(weapons[0], 25);
    
    targetCoords = new Coordinates();
}

void Turret::setTestValues()
{
    this->coords->X = 200;
    this->coords->Y = 200;
    this->coords->angle = -1;
    image = NULL;
    teamId = 1;
    range = 500;
    aiValue = 100;
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->propagateTurret(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->setObstacle(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->addToEntityList(this);
    currentThreatLevel = 0;
    targetAngle = -1;
}
void Turret::setCoords(double X, double Y)
{
    this->coords = new Coordinates();
    this->coords->X = X;
    this->coords->Y = Y;
    this->coords->angle = -1;
    teamId = 1;
    range = 500;
    aiValue = 100;
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->propagateTurret(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->setObstacle(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->addToEntityList(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->setRemoteAccessObject(this);
    currentThreatLevel = 0;
    targetAngle = -1;
}

void Turret::setCurrentThreatLevel(int currentThreatLevel) {
    this->currentThreatLevel = currentThreatLevel;
}

int Turret::getCurrentThreatLevel() const {
    return currentThreatLevel;
}

void Turret::update()
{
    if(active)
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
    this->updateBuffers();
}

void Turret::attack(int weapon)
{
    weapons[weapon]->shoot(coords, teamId, criticalChance, criticalDamage, accuracy);
}

bool Turret::turnRight()
{
    bool result = false;
    
    int tempTargetAngle = ceil(targetAngle) +180;
    tempTargetAngle %= 360;
    int delta = 180 - ceil(coords->angle);
    tempTargetAngle += delta;
    if(tempTargetAngle < 180)result = true;
    
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
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->setRemoteAccessObject(NULL);
}

void Turret::save(std::fstream& file)
{
    file << "TU" << std::endl;
    this->saveGeneric(file);
    file << std::endl;
}

void Turret::load(std::fstream& file)
{
    loadGeneric(file);
    
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->propagateTurret(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->setObstacle(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->addToEntityList(this);
}

Entity *Turret::CreateTurret(double X, double Y)
{
    Entity *turret = new Turret();
    if(X != -1 && Y != -1) dynamic_cast<Turret*>(turret)->setCoords(X,Y);
    return turret;
}

void Turret::setActive(bool active) {
    this->active = active;
}

bool Turret::isActive() const {
    return active;
}

void Turret::RCUse()
{
    active = !active;
}