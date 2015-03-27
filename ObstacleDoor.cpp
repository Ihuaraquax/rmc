/* 
 * File:   ObstacleDoor.cpp
 * Author: Qb
 * 
 * Created on 19 marzec 2015, 20:57
 */

#include "ObstacleDoor.h"
#include "globalVariables.h"

ObstacleDoor::ObstacleDoor(double X, double Y) {
    coords = new Coordinates();
    coords->X = X;
    coords->Y = Y;
    this->health = 1000;
    this->maximumHealth = health;
    this->armor = 1;
    this->coords->height = Variables::tileSize;
    this->coords->width = Variables::tileSize;
    for(int i = 0; i < Variables::damageTypeCount; i++)elementalResists[i] = 0.5;
    std::string paths[] = {"images/blastDoorClosed.jpg"};
    std::string paths2[] = {"images/blastDoorOpen.jpg"};
    this->closedImage = new Image(1, paths, true);
    this->openImage = new Image(1, paths2, true);
    this->closedImage->state = NORMAL;
    this->openImage->state = NORMAL;
    maximumHealth = health;
    closed = true;
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X,Y)->setObstacle(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X,Y)->addToEntityList(this);
    image = NULL;
}

ObstacleDoor::~ObstacleDoor() {
    delete closedImage;
    delete openImage;
}

void ObstacleDoor::display()
{
    if(closed)closedImage->display(coords);
    else openImage->display(coords);
}

void ObstacleDoor::update()
{
    
}

void ObstacleDoor::use()
{
    if(closed)
    {
        if(vertical)
        {
            Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->deleteFromEntityList(this);
            Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X + Variables::tileSize,coords->Y)->deleteFromEntityList(this);
        } else 
        {
            Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->deleteFromEntityList(this);
            Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y+ Variables::tileSize)->deleteFromEntityList(this);
        }
        closed = false;
    } else {
        if(vertical)
        {
            Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X + Variables::tileSize,coords->Y)->setObstacle(this);
            Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X + Variables::tileSize,coords->Y)->addToEntityList(this);
        } else 
        {
            Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y + Variables::tileSize)->setObstacle(this);
            Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y + Variables::tileSize)->addToEntityList(this);
        }
        closed = true;
    }
}

void ObstacleDoor::setAngle(bool vertical)
{
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X ,coords->Y)->setUsableObject(this);
    this->vertical = vertical;
    if(vertical)
    {
        Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X - Variables::tileSize,coords->Y)->setUsableObject(this);
        Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X + Variables::tileSize,coords->Y)->setUsableObject(this);
        Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X + Variables::tileSize,coords->Y)->setObstacle(this);
        Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X + Variables::tileSize,coords->Y)->addToEntityList(this);
        coords->X += Variables::tileSize/2;
    } else 
    {
        Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y - Variables::tileSize)->setUsableObject(this);
        Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y + Variables::tileSize)->setUsableObject(this);
        Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y + Variables::tileSize)->setObstacle(this);
        Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y + Variables::tileSize)->addToEntityList(this);
        coords->Y += Variables::tileSize/2;
    }
}

bool ObstacleDoor::isBarricade()
{
    return true;
}

void ObstacleDoor::save(std::fstream& file)
{
    file << "OD" << std::endl;
    saveGeneric(file);
    if(open) file << 1 << ' ';
    else  file << 0 << ' ';
    if(vertical) file << 1 << ' ';
    else file << 0 << ' ';    
    file << std::endl;
}