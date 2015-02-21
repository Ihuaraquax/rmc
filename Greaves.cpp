/* 
 * File:   Greaves.cpp
 * Author: Qb
 * 
 * Created on 16 luty 2015, 19:52
 */

#include "Greaves.h"
#include "Player.h"
#include "globalVariables.h"

Greaves::Greaves() {
}

Greaves::~Greaves() {
}


void Greaves::specificUpdate()
{
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    switch(action){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
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

void Greaves::activate()
{
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    active = true;
    switch(action){
        case 1:
            break;
        case 2: player->elementalResists[electric] += this->resistance[electric];
            break;
        case 3:
            break;
        case 4: player->armor += armor;
            break;
        case 5: player->coords->speedX +=2;
         player->coords->speedY +=2;
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
    }
}

void Greaves::deactivate()
{
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    active = false;
    switch(action){
        case 1:
            break;
        case 2: player->elementalResists[electric] -= this->resistance[electric];
            break;
        case 3:
            break;
        case 4: player->armor -= armor;
            break;
        case 5: player->coords->speedX -=2;
         player->coords->speedY -=2;
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
    }
}