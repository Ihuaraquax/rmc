/* 
 * File:   WeaponLoader.cpp
 * Author: Qb
 * 
 * Created on 12 luty 2015, 18:05
 */

#include "WeaponLoader.h"
#include <iostream>
#include <fstream>

WeaponLoader::WeaponLoader() {
}

void WeaponLoader::loadWeapon(Weapon* weapon, int newWeaponId)
{
    weapon->weaponId = newWeaponId;
    weapon->reloadable = true;
    if(newWeaponId == -1)loadNone(weapon);
    else
    {
        std::fstream file;
        file.open("fixtures/weapons.txt", std::ios::in);
        int temp;
        file >> temp;
        while(temp != newWeaponId)
        {
            std::string tempString = " ";
            std::getline(file, tempString);
            file >> temp;
        }
        file >> weapon->name >> weapon->damage >> weapon->ammoMax >> weapon->ammoType
             >> weapon->reloadSpeed >> weapon->cooldown >> temp
             >> weapon->weight >> weapon->targetSizeIncrement
             >> weapon->targetSizeDecrement >> weapon->defaultTargetSize
             >> weapon->projectileCount >> weapon->displayPaths;
        weapon->ammoCurrent = weapon->ammoMax;  

        switch(temp)
        {
            case 0: weapon->damageType = normal;
                break;
            case 1: weapon->damageType = fire;
                break;
            case 2: weapon->damageType = electric;
                break;
            case 3: weapon->damageType = poison;
                break;
            case 4: weapon->damageType = cold;
                break;
            case 5: weapon->damageType = explosive;
                break;
        }
    }
    
}

void WeaponLoader::displayLogsToConsole(Weapon* weapon)
{
    std::cout << "name: " <<  weapon->name << "\n damage: " << weapon->damage << "\n ammoMax: " << weapon->ammoMax << "\n ammoType: " << weapon->ammoType
         << "\n reload speed: " << weapon->reloadSpeed << "\n cooldown: " << weapon->cooldown //  << "\n damageType: " << temp
         << "\n weight: " << weapon->weight << "\n target size increment: " << weapon->targetSizeIncrement
         << "\n target size decrement: " << weapon->targetSizeDecrement << "\n default target size: " << weapon->defaultTargetSize
         << "\n projectile count: " << weapon->projectileCount << std::endl << "\n display paths: " << weapon->displayPaths;
}

std::string WeaponLoader::loadPath(int index)
{
    std::string result;
    std::string path;
    std::fstream file;
    file.open("fixtures/weapons.txt", std::ios::in);
    for(int i = 0; i < index; i++)std::getline(file, path);
    for(int i = 0; i < 13; i++)file >> path;
    file >> result;
    return result;
}

void WeaponLoader::loadNone(Weapon* weapon)
{
    weapon->ammoMax = 1;
    weapon->ammoCurrent = 0;
    weapon->reloadSpeed = 0;
    weapon->damage = 0;
    weapon->cooldown = 0;
    weapon->timeToShoot = 0;
    weapon->reloading = false;
    weapon->damageType = normal;
    weapon->defaultTargetSize = 1;
    weapon->currentTargetSize = 1;
    weapon->targetSizeIncrement = 1;
    weapon->targetSizeDecrement = 1;
    weapon->targetSizeIncrementSlowDownPoint = 10;
    weapon->range = 0;
    weapon->displayPaths = "images/noWeapon.png";
    weapon->projectileCount = 0;
    weapon->name = "noWeapon";
    weapon->criticalChance = 10;
    weapon->criticalDamage = 2;
    weapon->reloadable = false;
    weapon->ammoType = -1;
}