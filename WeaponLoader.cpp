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
    std::fstream file;
    file.open("fixtures/weapons.txt", std::ios::in);
    int id;
    file >> id;
    while(id != newWeaponId)
    {
        std::string temp = " ";
        std::getline(file, temp);
        file >> id;
    }
    file >> weapon->name >> weapon->damage >> weapon->ammoMax >> weapon->ammoType
         >> weapon->reloadSpeed >> weapon->cooldown >> id
         >> weapon->weight >> weapon->targetSizeIncrement
         >> weapon->targetSizeDecrement >> weapon->defaultTargetSize
         >> weapon->projectileCount;
    weapon->ammoCurrent = weapon->ammoMax;
    std::cout << "name: " <<  weapon->name << "\n damage: " << weapon->damage << "\n ammoMax: " << weapon->ammoMax << "\n ammoType: " << weapon->ammoType
         << "\n reload speed: " << weapon->reloadSpeed << "\n cooldown: " << weapon->cooldown << "\n damageType: " << id
         << "\n weight: " << weapon->weight << "\n target size increment: " << weapon->targetSizeIncrement
         << "\n target size decrement: " << weapon->targetSizeDecrement << "\n default target size: " << weapon->defaultTargetSize
         << "\n projectile count: " << weapon->projectileCount << std::endl;
}
