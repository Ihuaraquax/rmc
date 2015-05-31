/* 
 * File:   Attributes.cpp
 * Author: Qb
 * 
 * Created on 21 luty 2015, 18:02
 */

#include "Attributes.h"
#include "Session.h"
#include "Player.h"
#include "globalVariables.h"

Attributes::Attributes() {
    this->accuracy = 1;
    this->inteligence = 1;
    this->speed = 1;
    this->strength = 1;
    this->attributePointsLeft = 0;
    for(int i = 0; i < 4; i++)skillPointsLeft[i] = 1;
}

Attributes::~Attributes() {
}

int Attributes::getAccuracy() const {
    return accuracy;
}

int Attributes::getInteligence() const {
    return inteligence;
}

int Attributes::getSpeed() const {
    return speed;
}

int Attributes::getStrength() const {
    return strength;
}

void Attributes::addAccuracy(int toAdd)
{
    if(toAdd > 0 && this->attributePointsLeft > toAdd)
    {
        this->accuracy += toAdd;
        dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->recalculateAccuracy();
        attributePointsLeft -= toAdd;
    }
}

void Attributes::addInteligence(int toAdd)
{
    if(toAdd > 0 && this->attributePointsLeft > toAdd)
    {
        this->inteligence += toAdd;
        dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->recalculateCritical();
        attributePointsLeft -= toAdd;
    }
}

void Attributes::addSpeed(int toAdd)
{
    if(toAdd > 0 && this->attributePointsLeft > toAdd)
    {
        this->speed += toAdd;
        double temp = toAdd;
        temp /= 100;
        dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->coords->speedX += temp;
        dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->coords->speedY += temp;
        attributePointsLeft -= toAdd;
    }
}

void Attributes::addStrength(int toAdd)
{
    if(toAdd > 0 && this->attributePointsLeft > toAdd)
    {
        this->strength += toAdd;
        dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->health += toAdd;
        dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->maximumHealth += toAdd;
        attributePointsLeft -= toAdd;
    }
}

void Attributes::save(std::fstream& file)
{
    file << strength << ' ' << speed << ' ' << inteligence << ' ' << accuracy << ' ';
}

void Attributes::load(std::fstream& file)
{
    file >> strength >> speed >> inteligence >> accuracy;
}

void Attributes::addSkillPoints(int toAdd)
{
    this->attributePointsLeft += toAdd;
}