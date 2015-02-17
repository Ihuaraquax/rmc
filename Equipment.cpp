/* 
 * File:   Equipment.cpp
 * Author: Qb
 * 
 * Created on 16 luty 2015, 20:43
 */

#include "Equipment.h"
#include "globalVariables.h"

Equipment::Equipment() {
    this->action = -1;
    this->active = false;
    this->armor = 0;
    this->currentEnergy = 100;
    this->energyConsumption = 0;
    this->energyRegeneration = 0;
    this->maxEnergy = 100;
    this->resistance = new double[Variables::damageTypeCount];
    for(int i = 0; i < Variables::damageTypeCount; i++)this->resistance[i] = 0;
    this->imagePath = "images/noEquipmentInSlot.png";
}

Equipment::~Equipment() {
    delete []resistance;
}

void Equipment::update()
{
    
}

void Equipment::specificUpdate()
{
    
}

std::string Equipment::getImagePath() const {
    return imagePath;
}

double Equipment::getResistance(int index) const {
    return resistance[index];
}

int Equipment::getArmor() const {
    return armor;
}

bool Equipment::isActive() const {
    return active;
}

int Equipment::getAction() const {
    return action;
}