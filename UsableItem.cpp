/* 
 * File:   UsableItem.cpp
 * Author: Qb
 * 
 * Created on 22 luty 2015, 13:51
 */

#include "UsableItem.h"
#include "globalVariables.h"
#include "Turret.h"

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
        case 2:
            int X = Variables::mouse_x + Variables::offsetX, Y =Variables::mouse_y + Variables::offsetY;
            X -= X%Variables::tileSize;
            Y -= Y%Variables::tileSize;
            ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X, Y);
            if(isTileNearToPlayer(X,Y) && tile->getObstacle() == NULL && tile->getEntityList() == NULL)
            {
                Entity *turret = new Turret(X, Y);
                Variables::session->getAllEntities()->addEntity(turret);
            } else charges++;
            break;
    }
}

int UsableItem::getCharges() const {
    return charges;
}

std::string UsableItem::getImagePath() const {
    return imagePath;
}

int UsableItem::getAction() const {
    return action;
}

bool UsableItem::isTileNearToPlayer(double X, double Y)
{
    return Variables::proximity(X,Y, Variables::session->getAllEntities()->getPlayer()->getCoords()->X, Variables::session->getAllEntities()->getPlayer()->getCoords()->Y) < 200;
}