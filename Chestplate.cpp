/* 
 * File:   Chestplate.cpp
 * Author: Qb
 * 
 * Created on 16 luty 2015, 19:52
 */

#include "Chestplate.h"
#include "globalVariables.h"
#include "Player.h"

Chestplate::Chestplate() {
}

Chestplate::~Chestplate() {
}


void Chestplate::specificUpdate()
{
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    switch(action){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4: if(Variables::currentFrame == 0)player->heal(1);
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
    }
}

void Chestplate::activate()
{
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    active = true;
    switch(action){
        case 1: player->armor += armor;
            break;
        case 2:
            break;
        case 3: player->elementalResists[fire] += this->resistance[normal];
         player->elementalResists[fire] += this->resistance[fire]; 
         player->elementalResists[fire] += this->resistance[electric];
         player->elementalResists[fire] += this->resistance[poison];
         player->elementalResists[fire] += this->resistance[cold];
         player->elementalResists[fire] += this->resistance[explosive];
            break;
        case 4:
            break;
        case 5: player->elementalResists[fire] += this->resistance[fire];
         player->elementalResists[fire] += this->resistance[cold];
            break;
        case 6:  player->heal(50);
            break;
        case 7: player->elementalResists[explosive] += this->resistance[explosive];
            break;
        case 8: 
            break;
    }
}

void Chestplate::deactivate()
{
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    active = false;
    switch(action){
        case 1: player->armor -= armor;
            break;
        case 2:
            break;
        case 3: player->elementalResists[fire] -= this->resistance[normal];
         player->elementalResists[fire] -= this->resistance[fire]; 
         player->elementalResists[fire] -= this->resistance[electric];
         player->elementalResists[fire] -= this->resistance[poison];
         player->elementalResists[fire] -= this->resistance[cold];
         player->elementalResists[fire] -= this->resistance[explosive];
            break;
        case 4:
            break;
        case 5: player->elementalResists[fire] -= this->resistance[fire];
         player->elementalResists[fire] -= this->resistance[cold];
            break;
        case 6: 
            break;
        case 7: player->elementalResists[explosive] -= this->resistance[explosive];
            break;
        case 8:
            break;
    }
}

std::string Chestplate::getFilePath()
{
    return "fixtures/chestplates.txt";
}