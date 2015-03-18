/* 
 * File:   UsableItemLoader.cpp
 * Author: Qb
 * 
 * Created on 23 luty 2015, 19:00
 */

#include "UsableItemLoader.h"
#include <fstream>

void UsableItemLoader::loadItem(UsableItem* item, int type)
{
    std::fstream file;
    file.open("fixtures/usableItems.txt", std::ios::in);
    std::string temp;
    int id;
    file >> id;
    while(id != type)
    {
        std::getline(file, temp);
        file >> id;
    }
    file >> item->imagePath >> item->charges;
    item->action = id;
   
}

std::string UsableItemLoader::loadItemPath(int type)
{
    std::string result;
    std::fstream file;
    file.open("fixtures/usableItems.txt", std::ios::in);
    std::string temp;
    int id;
    file >> id;
    while(id != type)
    {
        std::getline(file, temp);
        file >> id;
    }
    file >> result;
    return result;
}