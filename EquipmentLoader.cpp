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
    for(int i = 0; i < index; i++)std::getline(file, temp);
    file >> equipment->action >> equipment->name >> equipment->armor >> equipment->energyConsumption;
    for(int i = 0; i < Variables::damageTypeCount; i++)file >> equipment->resistance[i];
    file >> equipment->imagePath;
}

void EquipmentLoader::displayLogsToConsole(Equipment* equipment)
{    
    std::cout << " action: "  << equipment->action << std::endl;
    std::cout << " name: "  << equipment->name << std::endl;
    std::cout << " armor: "  << equipment->armor << std::endl;
    std::cout << " energy consumption: " << equipment->energyConsumption << std::endl;
    std::cout << " resistance 0: "  << equipment->resistance[0] << std::endl;
    std::cout << " resistance 1: "  << equipment->resistance[1] << std::endl;
    std::cout << " resistance 2: "  << equipment->resistance[2] << std::endl;
    std::cout << " resistance 3: "  << equipment->resistance[3] << std::endl;
    std::cout << " resistance 4: "  << equipment->resistance[4] << std::endl;
    std::cout << " imagePath: "  << equipment->imagePath << std::endl << std::endl;
}