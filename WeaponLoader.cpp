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
    
    std::cout << "name: " <<  weapon->name << "\n damage: " << weapon->damage << "\n ammoMax: " << weapon->ammoMax << "\n ammoType: " << weapon->ammoType
         << "\n reload speed: " << weapon->reloadSpeed << "\n cooldown: " << weapon->cooldown << "\n damageType: " << temp
         << "\n weight: " << weapon->weight << "\n target size increment: " << weapon->targetSizeIncrement
         << "\n target size decrement: " << weapon->targetSizeDecrement << "\n default target size: " << weapon->defaultTargetSize
         << "\n projectile count: " << weapon->projectileCount << std::endl << "\n display paths: " << weapon->displayPaths;
}