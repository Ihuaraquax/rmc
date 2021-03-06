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
#include "PlayerBaseValues.h"

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
        if(accuracy%10 == 0)dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->getSkills()->addSkillPoints(2, 1);
    }
}

void Attributes::addInteligence(int toAdd)
{
    if(toAdd > 0 && this->attributePointsLeft > toAdd)
    {
        this->inteligence += toAdd;
        dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->recalculateCritical();
        attributePointsLeft -= toAdd;
        if(inteligence%10 == 0)dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->getSkills()->addSkillPoints(1, 1);
    }
}

void Attributes::addSpeed(int toAdd)
{
    if(toAdd > 0 && this->attributePointsLeft > toAdd)
    {
        Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
        this->speed += toAdd;
        double temp = toAdd;
        temp /= 100;
        player->coords->speedX += temp;
        player->coords->speedY += temp;
        player->baseValues.speed += temp;
        attributePointsLeft -= toAdd;
        if(speed%10 == 0)dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->getSkills()->addSkillPoints(3, 1);
    }
}

void Attributes::addStrength(int toAdd)
{
    if(toAdd > 0 && this->attributePointsLeft > toAdd)
    {
        Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
        this->strength += toAdd;
        player->health += toAdd;
        player->maximumHealth += toAdd;
        player->baseValues.health += toAdd;
        player->baseValues.maxHealth += toAdd;
        attributePointsLeft -= toAdd;
        if(strength%10 == 0)dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->getSkills()->addSkillPoints(0, 1);
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