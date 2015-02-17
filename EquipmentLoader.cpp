/* 
 * File:   EquipmentLoader.cpp
 * Author: Qb
 * 
 * Created on 17 luty 2015, 21:53
 */

#include "EquipmentLoader.h"
#include "globalVariables.h"
#include <iostream>
#include <fstream>

EquipmentLoader::EquipmentLoader() {
}

EquipmentLoader::~EquipmentLoader() {
}

void EquipmentLoader::loadNewEquipment(Equipment* equipment, int index, std::string path)
{
    std::fstream file;
    file.open(path.c_str(), std::ios::in);
    std::string temp;
    for(int i = 1; i < index; i++)std::getline(file, temp);
    file >> equipment->action >> equipment->name >> equipment->armor >> equipment->energyConsumption;
    for(int i = 0; i < Variables::damageTypeCount; i++)file >> equipment->resistance[i];
    file >> equipment->imagePath;
    
    std::cout << equipment->action << ' ';
    std::cout << equipment->name << ' ';
    std::cout << equipment->armor << ' ';
    std::cout << equipment->energyConsumption << ' ';
    std::cout << equipment->resistance[0] << ' ';
    std::cout << equipment->resistance[1] << ' ';
    std::cout << equipment->resistance[2] << ' ';
    std::cout << equipment->resistance[3] << ' ';
    std::cout << equipment->resistance[4] << ' ';
    std::cout << equipment->imagePath << std::endl;
}