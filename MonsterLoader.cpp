/* 
 * File:   MonsterLoader.cpp
 * Author: Qb
 * 
 * Created on 9 marzec 2015, 18:23
 */

#include "MonsterLoader.h"
#include "WeaponLoader.h"
#include "Monster.h"
#include <iostream>
#include "globalVariables.h"

void MonsterLoader::loadMonster(Entity* entity, int type, int modifier)
{
    Monster *monster = dynamic_cast<Monster*>(entity);
    switch(type)
    {
        case 0:
            monster->coords->angle = 0;
            monster->coords->height = 25;
            monster->coords->width = 25;
            monster->coords->speedX = 1.7;
            monster->coords->speedY = 1.7;
            monster->image = Variables::images->getMonster1();
            monster->health = 500;
            monster->teamId = 0;
            WeaponLoader::loadWeapon(monster->weapons[0], 0);
            WeaponLoader::loadWeapon(monster->weapons[1], 0);
            monster->threatLevel = 10;
            Variables::session->getMap()->getCurrentModule()->getModuleTileAt(monster->coords->X,monster->coords->Y)->addToThreatLevel(monster->threatLevel);
            monster->setStartingTile();
            monster->expirience = 100;
            monster->maximumHealth = monster->health;
            break;
        case 1:
            monster->coords->angle = 0;
            monster->coords->height = 25;
            monster->coords->width = 25;
            monster->coords->speedX = 1.7;
            monster->coords->speedY = 1.7;
            monster->image = Variables::images->getMonster2();
            monster->health = 500;
            monster->teamId = 0;
            WeaponLoader::loadWeapon(monster->weapons[0], 0);
            WeaponLoader::loadWeapon(monster->weapons[1], 0);
            monster->threatLevel = 10;
            Variables::session->getMap()->getCurrentModule()->getModuleTileAt(monster->coords->X,monster->coords->Y)->addToThreatLevel(monster->threatLevel);
            monster->setStartingTile();
            monster->expirience = 100;
            monster->maximumHealth = monster->health;
            break;
        case 2:
            monster->coords->angle = 0;
            monster->coords->height = 25;
            monster->coords->width = 25;
            monster->coords->speedX = 1.7;
            monster->coords->speedY = 1.7;
            monster->image = Variables::images->getMonster3();
            monster->health = 500;
            monster->teamId = 0;
            WeaponLoader::loadWeapon(monster->weapons[0], 0);
            WeaponLoader::loadWeapon(monster->weapons[1], 0);
            monster->threatLevel = 10;
            Variables::session->getMap()->getCurrentModule()->getModuleTileAt(monster->coords->X,monster->coords->Y)->addToThreatLevel(monster->threatLevel);
            monster->setStartingTile();
            monster->expirience = 100;
            monster->maximumHealth = monster->health;
            break;
    }
    
//    switch(modifier)
//    {
//        case 0: monster->weapons[0]->setDamageType(normal);
//            break;
//        case 1: monster->weapons[0]->setDamageType(fire);
//            break;
//        case 2: monster->weapons[0]->setDamageType(electric);
//            break;
//        case 3: monster->weapons[0]->setDamageType(poison);
//            break;
//        case 4: monster->weapons[0]->setDamageType(cold);
//            break;
//        case 5: monster->coords->speedX *=2;
//                monster->coords->speedY *=2;
//                break;
//        case 6: monster->coords->speedX *=1.3;
//                monster->coords->speedY *=1.3;
//                monster->armor += 30;
//                monster->health *=3;
//                monster->maximumHealth *=3;
//                monster->expirience *= 2;
//                monster->criticalDamage *=2;
//                monster->coords->height *= 1.5;
//                monster->coords->width *= 1.5;
//                break;
//    }
}