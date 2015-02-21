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

void Chestplate::activate()
{
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    active = true;
    switch(action){
        case 1: player->armor += 100;
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

void Chestplate::deactivate()
{
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    active = false;
    switch(action){
        case 1: player->armor -= 100;
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