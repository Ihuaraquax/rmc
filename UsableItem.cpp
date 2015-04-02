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
    ModuleTile *tile;
    double X,Y;
    bool acceptableCoords = this->getPointedCoords(X,Y);
    switch(action)
    {
        case 0: charges++;
            break;
        case 1: Variables::session->getAllEntities()->getPlayer()->heal(50);
            break;
        case 2:
            tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X, Y);
            if(isTileNearToPlayer(X,Y) && acceptableCoords && tile->getEntityList() == NULL)
            {
                Entity *turret = Turret::CreateTurret(X,Y);
                Variables::session->getAllEntities()->addEntity(turret);
            } else charges++;
            break;
        case 3:
            tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X, Y);
            if(isTileNearToPlayer(X,Y) && acceptableCoords && tile->getEntityList() == NULL)
            {
                GenericBuffer *buff = new DistanceBuffer(0, 1, 200);
                Entity *rod = BuffRod::CreateBuffRod(X, Y, buff);
                Variables::session->getAllEntities()->addEntity(rod);
            } else charges++;
            break;
        case 4:
            tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X, Y);
            if(isTileNearToPlayer(X,Y) && acceptableCoords && tile->getEntityList() == NULL)
            {
                Entity *explosive = Explosives::CreateExplosives(X, Y);
                Variables::session->getAllEntities()->addEntity(explosive);
            } else charges++;
            break;
        case 5:
            tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X, Y);
            if(isTileNearToPlayer(X,Y) && acceptableCoords && tile->getEntityList() == NULL)
            {
                Entity *explosive = RemoteCharges::CreateCharges(X, Y);
                Variables::session->getAllEntities()->addRemoteCharge(explosive);
                dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->changeItem(100);
                this->additionalData = dynamic_cast<RemoteCharges*>(explosive)->getSignalId();
            } else charges++;
            break;
        case 6:
            tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X, Y);
            if(isTileNearToPlayer(X,Y) && acceptableCoords && tile->getEntityList() == NULL)
            {
                Variables::session->getAllEntities()->getPlayer()->setCoords(X,Y);
            } else charges++;
            break;
        case 100:
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

bool UsableItem::getPointedCoords(double& X, double& Y)
{
    int size = Variables::tileSize * Variables::ScaleX;
    int x,y;
    x = (Variables::mouse_x ) * (1/Variables::ScaleX)+ Variables::offsetX;
    y = (Variables::mouse_y ) * (1/Variables::ScaleY)+ Variables::offsetY;
    x -= x%size;
    y -= y%size;
    X = x;
    Y = y;
    if(X < 0 || Y < 0 || X > Variables::tileSize * Variables::tilesPerRoom || Y > Variables::tileSize * Variables::tilesPerRoom
            || Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X, Y)->getObstacle() != NULL)return false;
    return true;
}

void UsableItem::save(std::fstream& file)
{
    file << action  << ' ' << charges << ' ' << additionalData << ' ';
}

void UsableItem::load(std::fstream& file)
{
    file >>action >> charges >> additionalData;
    this->imagePath = UsableItemLoader::loadItemPath(action);
}