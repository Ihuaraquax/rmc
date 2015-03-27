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
    this->accuracy += toAdd;
    dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->recalculateAccuracy();
}

void Attributes::addInteligence(int toAdd)
{
    this->inteligence += toAdd;
    dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->recalculateCritical();
}

void Attributes::addSpeed(int toAdd)
{
    this->speed += toAdd;
    double temp = toAdd;
    temp /= 100;
    dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->coords->speedX += temp;
    dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->coords->speedY += temp;
}

void Attributes::addStrength(int toAdd)
{
    this->strength += toAdd;
    dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->health += toAdd;
    dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->maximumHealth += toAdd;
}

void Attributes::save(std::fstream& file)
{
    file << strength << ' ' << speed << ' ' << inteligence << ' ' << accuracy << ' ';
}