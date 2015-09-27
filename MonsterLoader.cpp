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
//    switch(type)
//    {
//        case 0:
//            monster->coords->angle = 0;
//            monster->coords->height = 25;
//            monster->coords->width = 25;
//            monster->coords->speedX = 1.7;
//            monster->coords->speedY = 1.7;
//            monster->image = Variables::images->getByName("monster1");
//            monster->health = 500;
//            monster->teamId = 0;
//            WeaponLoader::loadWeapon(monster->weapons[0], 0);
//            WeaponLoader::loadWeapon(monster->weapons[1], 0);
//            monster->threatLevel = 10;
//            monster->maximumHealth = monster->health;
//            break;
//        case 1:
//            monster->coords->angle = 0;
//            monster->coords->height = 25;
//            monster->coords->width = 25;
//            monster->coords->speedX = 1.7;
//            monster->coords->speedY = 1.7;
//            monster->image = Variables::images->getByName("monster2");
//            monster->health = 500;
//            monster->teamId = 0;
//            WeaponLoader::loadWeapon(monster->weapons[0], 0);
//            WeaponLoader::loadWeapon(monster->weapons[1], 0);
//            monster->threatLevel = 10;
//            monster->maximumHealth = monster->health;
//            break;
//        case 2:
//            monster->coords->angle = 0;
//            monster->coords->height = 25;
//            monster->coords->width = 25;
//            monster->coords->speedX = 1.7;
//            monster->coords->speedY = 1.7;
//            monster->image = Variables::images->getByName("monster3");
//            monster->health = 500;
//            monster->teamId = 0;
//            WeaponLoader::loadWeapon(monster->weapons[0], 0);
//            WeaponLoader::loadWeapon(monster->weapons[1], 0);
//            monster->threatLevel = 10;
//            monster->maximumHealth = monster->health;
//            break;
//    }
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(monster->coords->X,monster->coords->Y)->addToThreatLevel(monster->threatLevel);
    monster->setStartingTile();
}