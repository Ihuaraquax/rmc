/* 
 * File:   ObstacleDoor.cpp
 * Author: Qb
 * 
 * Created on 19 marzec 2015, 20:57
 */

#include "ObstacleDoor.h"
#include "globalVariables.h"


ObstacleDoor::ObstacleDoor()
{
    coords = new Coordinates();
    this->coords->width = Variables::tileSize;
    this->coords->height = Variables::tileSize;
    this->coords->speedX = 0;
    this->coords->speedY = 0;
    this->coords->angle = 0;
    image = NULL;
    std::string paths[] = {"images/blastDoorClosed.jpg"};
    std::string paths2[] = {"images/blastDoorOpen.jpg"};
    this->closedImage = new Image(1, paths, true);
    this->openImage = new Image(1, paths2, true);
    this->closedImage->state = NORMAL;
    this->openImage->state = NORMAL;
    this->health = 1000;
    this->maximumHealth = health;
    closed = true;
    this->armor = 1;
    for(int i = 0; i < Variables::damageTypeCount; i++)elementalResists[i] = 0.5;
}

void ObstacleDoor::setCoords(double X, double Y) {
    coords->X = X;
    coords->Y = Y;
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
    if(closed) file << 1 << ' ';
    else  file << 0 << ' ';
    if(vertical) file << 1 << ' ';
    else file << 0 << ' ';    
    file << std::endl;
}

void ObstacleDoor::load(std::fstream& file)
{
    loadGeneric(file);
    int temp;
    file >> temp;
    if(temp == 1)closed = true;
    else closed = false;
    file >> temp;
    if(temp == 1)vertical = true;
    else vertical = false;
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->setObstacle(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->addToEntityList(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->setRemoteAccessObject(this);
    this->setAngle(vertical);
    if(vertical)this->coords->X -= Variables::tileSize/2;
    else this->coords->Y -= Variables::tileSize/2;
}

Entity *ObstacleDoor::CreateObstacleDoor(double X, double Y)
{
    Entity *obstacleDoor = new ObstacleDoor();
    if(X != -1 && Y != -1)
    {
        obstacleDoor->setCoords(X,Y);
        Variables::session->getMap()->getCurrentModule()->getModuleTileAt(obstacleDoor->getCoords()->X, obstacleDoor->getCoords()->Y)->setRemoteAccessObject(obstacleDoor);
    }
    return obstacleDoor;
}

void ObstacleDoor::executeAgony()
{
    for(int i = 0; i < Variables::tilesPerRoom * Variables::tilesPerRoom; i++)
    {
        Variables::session->getMap()->getCurrentModule()->getModuleTiles()[i]->deleteUsableObject(this);
        Variables::session->getMap()->getCurrentModule()->getModuleTiles()[i]->deleteFromEntityList(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->setRemoteAccessObject(NULL);
    }
}

void ObstacleDoor::displayPlan()
{
    if(closed)closedImage->display(planCoords);
    else openImage->display(planCoords);
}

void ObstacleDoor::RCUse()
{
    use();
}