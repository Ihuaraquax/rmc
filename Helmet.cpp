/* 
 * File:   Helmet.cpp
 * Author: Qb
 * 
 * Created on 16 luty 2015, 19:52
 */

#include "Helmet.h"
#include "globalVariables.h"
#include "Player.h"

Helmet::Helmet() {
}

Helmet::~Helmet() {
}

void Helmet::specificUpdate()
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
        case 7: player->weapons[player->selecetedWeaponSet * 2]->update();
         player->weapons[player->selecetedWeaponSet * 2 + 1]->update();
            break;
        case 8:
            break;
    }
}

void Helmet::activate()
{
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    active = true;
    switch(action){
        case 1:
            break;
        case 2: player->recalculateAccuracy();
            break;
        case 3:
            break;
        case 4: player->armor += armor;
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

void Helmet::deactivate()
{
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    active = false;
    switch(action){
        case 1:
            break;
        case 2: player->recalculateAccuracy();
            break;
        case 3:
            break;
        case 4: player->armor -= armor;
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