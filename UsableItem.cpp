/* 
 * File:   UsableItem.cpp
 * Author: Qb
 * 
 * Created on 22 luty 2015, 13:51
 */

#include "UsableItem.h"
#include "globalVariables.h"

UsableItem::UsableItem() {
    charges = 0;
    action = 0;
    imagePath = "images/noEquipmentInSlot.png";
}
UsableItem::~UsableItem() {
}

void UsableItem::activate()
{
    charges--;
    switch(action)
    {
        case 0: charges++;
            break;
        case 1: Variables::session->getAllEntities()->getPlayer()->heal(50);
            break;
    }
}

int UsableItem::getCharges() const {
    return charges;
}

std::string UsableItem::getImagePath() const {
    return imagePath;
}