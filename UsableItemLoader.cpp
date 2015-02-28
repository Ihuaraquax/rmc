/* 
 * File:   UsableItemLoader.cpp
 * Author: Qb
 * 
 * Created on 23 luty 2015, 19:00
 */

#include "UsableItemLoader.h"
#include <fstream>
#include <iostream>

void UsableItemLoader::loadItem(UsableItem* item, int type)
{
    std::fstream file;
    file.open("fixtures/usableItems.txt", std::ios::in);
    std::string temp;
    for(int i = 0; i < type; i++)std::getline(file, temp);
    file >> item->action >> item->imagePath >> item->charges;
    
    std::cout << item->action << ' ' << item->imagePath << ' ' << item->charges << std::endl;
}