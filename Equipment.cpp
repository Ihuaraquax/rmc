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
    this->currentEnergy = 6000;
    this->energyConsumption = 0;
    this->energyRegeneration = 1;
    this->maxEnergy = 6000;
    this->resistance = new double[Variables::damageTypeCount];
    for(int i = 0; i < Variables::damageTypeCount; i++)this->resistance[i] = 0;
    this->imagePath = "images/noEquipmentInSlot.png";
}

Equipment::~Equipment() {
    delete []resistance;
}

void Equipment::update()
{
    currentEnergy += energyRegeneration;
    if(currentEnergy >= maxEnergy)currentEnergy = maxEnergy;
    if(active)
    {
        currentEnergy -= energyConsumption;
        specificUpdate();
    }
    if(currentEnergy <= 0)
    {
        currentEnergy = 0;
        deactivate();
    }
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

void Equipment::setActive(bool active) {
    if(active)activate();
    else deactivate();
}

int Equipment::getCurrentEnergy() const {
    return currentEnergy;
}

int Equipment::getMaxEnergy() const {
    return maxEnergy;
}

void Equipment::activate()
{
    active = true;
}

void Equipment::deactivate()
{
    active = false;
}

std::string Equipment::getFilePath()
{
   return ""; 
}

void Equipment::save(std::fstream& file)
{
    file << action << ' ' << armor << ' ' << currentEnergy << ' ' << energyConsumption << ' ' << energyRegeneration << ' ' << maxEnergy << ' ' << imagePath << ' ';
    if(active)file << 1 << ' ';
    else file << 0 << ' ';
    for(int i = 0; i < Variables::damageTypeCount; i++)file << resistance[i] << ' ';
}

void Equipment::load(std::fstream& file)
{
    file >> action >> armor >> currentEnergy >> energyConsumption >> energyRegeneration >> maxEnergy >> imagePath;
    int temp;
    file >> temp;
    if(temp == 1)active = true;
    else active = false;
    for(int i = 0; i < Variables::damageTypeCount; i++)file >> resistance[i];
}

std::string Equipment::getName() const {
    return name;
}

int Equipment::getEnergyConsumption() const {
    return energyConsumption;
}