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
    this->closedImage = Variables::images->getByName("blastDoorClosed");
    this->openImage = Variables::images->getByName("blastDoorOpen");
    this->closedImage->state = NORMAL;
    this->openImage->state = NORMAL;
    this->health = 1000;
    this->maximumHealth = health;
    closed = true;
    this->armor = 1;
    for(int i = 0; i < Variables::damageTypeCount; i++)elementalResists[i] = 0.5;
    setRandomAllowanceObjects();
}

void ObstacleDoor::setCoords(double X, double Y) {
    coords->X = X;
    coords->Y = Y;
}

ObstacleDoor::~ObstacleDoor() {
}

void ObstacleDoor::display()
{
    if(closed)closedImage->display(coords);
    else openImage->display(coords);
    if(Variables::substate == console)displayConnections();
}

void ObstacleDoor::update()
{
    
}

void ObstacleDoor::use()
{
    if(canBeUsed())
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
//    displayConnections();
}

void ObstacleDoor::RCUse()
{
    use();
}

bool ObstacleDoor::canBeUsed()
{
    bool result = true;
    
    for(std::list<AllowanceObject*>::iterator i = allowanceObjects.begin(); i != allowanceObjects.end(); ++i)
    {
        AllowanceObject *temp = *i;
        if(temp->isAllow() == false)result = false;
    }
    return result;
}

void ObstacleDoor::displayConnections()
{
    double maxDistanceX = Variables::tileSize * Variables::tilesPerRoom * Variables::ScaleX * Variables::scale;
    double maxDistanceY = Variables::tileSize * Variables::tilesPerRoom * Variables::ScaleY * Variables::scale;
    for(std::list<AllowanceObject*>::iterator i = allowanceObjects.begin(); i != allowanceObjects.end(); ++i)
    {
        AllowanceObject *temp = *i;
        double X = ((coords->X + coords->width/2) * Variables::ScaleX - Variables::offsetX) * Variables::scale;
        double Y = ((coords->Y + coords->height/2) * Variables::ScaleX - Variables::offsetY) * Variables::scale;
        double objectX = ((temp->getCoords()->X + temp->getCoords()->width/2) * Variables::ScaleX - Variables::offsetX) * Variables::scale;
        double objectY = ((temp->getCoords()->Y + temp->getCoords()->height/2) * Variables::ScaleY - Variables::offsetY) * Variables::scale;
        int deltaX = Variables::session->getMap()->getModuleX() - temp->getModuleX();
        int deltaY = Variables::session->getMap()->getModuleY() - temp->getModuleY();
        objectX -= deltaX*maxDistanceX;
        objectY -= deltaY*maxDistanceY;
        if(objectX > maxDistanceX && objectY > maxDistanceY)
        {
            objectX = maxDistanceX;
            objectY = maxDistanceY;
        }
        else if (objectX > maxDistanceX && objectY < 0)
        {
            objectX = maxDistanceX;
            objectY = 0;
        }
        else if (objectX < 0 && objectY > maxDistanceY)
        {
            objectX = 0;
            objectY = maxDistanceY;
        }
        else if(objectX < 0 && objectY < 0)
        {
            objectX = 0;
            objectY = 0;
        }
        else if(objectX > maxDistanceX)
        {
            objectX = maxDistanceX;
            objectY = Y;
        }
        else if(objectY > maxDistanceY)
        {
            objectX = X;
            objectY = maxDistanceY;
        }
        else if(objectX < 0)
        {
            objectX = 0;
            objectY = Y;
        }
        else if(objectY < 0)
        {
            objectX = X;
            objectY = 0;
        }
        al_draw_line(X, Y, objectX, objectY, al_map_rgb(0,0,255), 5);
    }
}

void ObstacleDoor::setRandomAllowanceObjects()
{
    AllowanceObject *object = Variables::session->getAllAllowanceObjects()->getRandomObject();
    if(object != NULL)
    {
        this->allowanceObjects.push_back(object);
    }
}
void ObstacleDoor::highlight()
{
    al_draw_filled_rectangle(
            coords->X - Variables::offsetX, 
            coords->Y - Variables::offsetY, 
            coords->X + coords->width - Variables::offsetX, 
            coords->Y + coords->height - Variables::offsetY,
            al_map_rgb(0,255,0));
}