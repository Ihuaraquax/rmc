/* 
 * File:   UsableItem.cpp
 * Author: Qb
 * 
 * Created on 22 luty 2015, 13:51
 */

#include "UsableItem.h"
#include "globalVariables.h"
#include "Turret.h"
#include "GenericBuffer.h"
#include "DistanceBuffer.h"
#include "BuffRod.h"
#include "Explosives.h"
#include "UsableItemLoader.h"
#include "RemoteCharges.h"
#include "Player.h"

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
    int X, Y;
    ModuleTile *tile;
    switch(action)
    {
        case 0: charges++;
            break;
        case 1: Variables::session->getAllEntities()->getPlayer()->heal(50);
            break;
        case 2:
            X = Variables::mouse_x + Variables::offsetX;
            Y =Variables::mouse_y + Variables::offsetY;
            X -= X%Variables::tileSize;
            Y -= Y%Variables::tileSize;
            tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X, Y);
            if(isTileNearToPlayer(X,Y) && tile->getObstacle() == NULL && tile->getEntityList() == NULL)
            {
                Entity *turret = new Turret(X, Y);
                Variables::session->getAllEntities()->addEntity(turret);
            } else charges++;
            break;
        case 3:
            X = Variables::mouse_x + Variables::offsetX;
            Y =Variables::mouse_y + Variables::offsetY;
            X -= X%Variables::tileSize;
            Y -= Y%Variables::tileSize;
            tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X, Y);
            if(isTileNearToPlayer(X,Y) && tile->getObstacle() == NULL && tile->getEntityList() == NULL)
            {
                GenericBuffer *buff = new DistanceBuffer(0, 1, 200);
                BuffRod *rod = new BuffRod(buff);
                rod->setCoords(X,Y);
                Variables::session->getAllEntities()->addEntity(rod);
            } else charges++;
            break;
        case 4:
            X = Variables::mouse_x + Variables::offsetX;
            Y =Variables::mouse_y + Variables::offsetY;
            X -= X%Variables::tileSize;
            Y -= Y%Variables::tileSize;
            tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X, Y);
            if(isTileNearToPlayer(X,Y) && tile->getObstacle() == NULL && tile->getEntityList() == NULL)
            {
                Entity *explosive = new Explosives(X, Y);
                Variables::session->getAllEntities()->addEntity(explosive);
            } else charges++;
            break;
        case 5:
            X = Variables::mouse_x + Variables::offsetX;
            Y =Variables::mouse_y + Variables::offsetY;
            X -= X%Variables::tileSize;
            Y -= Y%Variables::tileSize;
            tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X, Y);
            if(isTileNearToPlayer(X,Y) && tile->getObstacle() == NULL && tile->getEntityList() == NULL)
            {
                Entity *explosive = new RemoteCharges(X, Y);
                Variables::session->getAllEntities()->addRemoteCharge(explosive);
                dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->changeItem(6);
                this->additionalData = dynamic_cast<RemoteCharges*>(explosive)->getSignalId();
            } else charges++;
            break;
        case 6:
            if(Variables::session->getAllEntities()->deleteRemoteCharge(additionalData) == false)
            {
                charges++;
            }
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