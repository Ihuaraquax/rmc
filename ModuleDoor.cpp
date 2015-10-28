/* 
 * File:   ModuleDoor.cpp
 * Author: Adiutant
 * 
 * Created on 24 październik 2015, 18:30
 */

#include "ModuleDoor.h"
#include "globalVariables.h"

ModuleDoor::ModuleDoor(bool horizontal)
{
    coords = new Coordinates();
    if(horizontal)
    {
        this->coords->width = Variables::tileSize * 4;
        this->coords->height = Variables::tileSize;
        this->coords->angle = 90;
    } 
    else 
    {
        this->coords->width = Variables::tileSize;
        this->coords->height = Variables::tileSize * 4;
        this->coords->angle = 0;
    }
    this->coords->speedX = 0;
    this->coords->speedY = 0;
    image = NULL;
    this->closedImage = Variables::images->getByName("moduleDoor");
    this->openImage = Variables::images->getByName("moduleDoorOpen");
    this->closedImage->state = NORMAL;
    this->openImage->state = NORMAL;
    this->health = 1000;
    this->maximumHealth = health;
    closed = true;
    this->armor = 1;
    for(int i = 0; i < Variables::damageTypeCount; i++)elementalResists[i] = 0.5;
    this->setRequirements();
}

void ModuleDoor::setCoords(double X, double Y) {
    coords->X = X;
    coords->Y = Y;
}

ModuleDoor::~ModuleDoor() {
}

void ModuleDoor::display()
{
    if(closed)closedImage->display(coords);
    else openImage->display(coords);
    if(Variables::substate == console)displayConnections();
}

void ModuleDoor::update()
{
    
}

void ModuleDoor::use()
{
    if(canBeUsed())
    {
        int moduleX = Variables::session->getMap()->getModuleX();
        int moduleY = Variables::session->getMap()->getModuleY();
        changeDoorStatus(moduleY, moduleX);
        useOtherSideDoor();
    }
}

void ModuleDoor::changeDoorStatus(int moduleX, int moduleY)
{
    if(closed)
    {
        for(int i = 0; i < Variables::tilesPerRoom * Variables::tilesPerRoom; i++)
        {
            Variables::session->getMap()->getModules()[moduleX][moduleY]->getModuleTiles()[i]->deleteFromEntityList(this);
        }
        closed = false;
    }
    else 
    {
        for(int i = 0; i < 4; i++)
        {
        ModuleTile *tile;
            if(horizontal)
            {
                tile = Variables::session->getMap()->getModules()[moduleX][moduleY]->getModuleTileAt(coords->X + (Variables::tileSize*i),coords->Y + Variables::tileSize);
                if(tile != NULL)tile->setObstacle(this);
                tile = Variables::session->getMap()->getModules()[moduleX][moduleY]->getModuleTileAt(coords->X + (Variables::tileSize*i),coords->Y - Variables::tileSize);
                if(tile != NULL)tile->setObstacle(this);
            } else 
            {                    
                tile = Variables::session->getMap()->getModules()[moduleX][moduleY]->getModuleTileAt(coords->X - Variables::tileSize,coords->Y + (Variables::tileSize*i));
                if(tile != NULL)tile->setObstacle(this);
                tile = Variables::session->getMap()->getModules()[moduleX][moduleY]->getModuleTileAt(coords->X + Variables::tileSize,coords->Y + (Variables::tileSize*i));
                if(tile != NULL)tile->setObstacle(this);
            }
        }
        closed = true;
    }
}

void ModuleDoor::setUseTiles(bool horizontal)
{
    for(int i = 0; i < 4; i++)
    {
        ModuleTile *tile;
        this->horizontal = horizontal;
        if(horizontal)
        {
            tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X + (Variables::tileSize*i),coords->Y + Variables::tileSize);
            if(tile != NULL)tile->setUsableObject(this);
            tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X + (Variables::tileSize*i),coords->Y - Variables::tileSize);
            if(tile != NULL)tile->setUsableObject(this);
        } 
        else 
        {
            tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X - Variables::tileSize,coords->Y + (Variables::tileSize*i));
            if(tile != NULL)tile->setUsableObject(this);
            tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X + Variables::tileSize,coords->Y + (Variables::tileSize*i));
            if(tile != NULL)tile->setUsableObject(this);
        }
    }
}

bool ModuleDoor::isBarricade()
{
    return true;
}

void ModuleDoor::save(std::fstream& file)
{
    file << "OD" << std::endl;
    saveGeneric(file);
    if(closed) file << 1 << ' ';
    else  file << 0 << ' ';
    if(horizontal) file << 1 << ' ';
    else file << 0 << ' ';    
    file << std::endl;
}

void ModuleDoor::load(std::fstream& file)
{
    loadGeneric(file);
    int temp;
    file >> temp;
    if(temp == 1)closed = true;
    else closed = false;
    file >> temp;
    if(temp == 1)horizontal = true;
    else horizontal = false;
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->setObstacle(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->addToEntityList(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->setRemoteAccessObject(this);
    this->setUseTiles(horizontal);
    if(horizontal)this->coords->X -= Variables::tileSize/2;
    else this->coords->Y -= Variables::tileSize/2;
}

Entity *ModuleDoor::CreateModuleDoor(double X, double Y, bool horizontal)
{
    Entity *moduleDoor = new ModuleDoor(horizontal);
    if(X != -1 && Y != -1)
    {
        moduleDoor->setCoords(X,Y);
        dynamic_cast<ModuleDoor*>(moduleDoor)->setUseTiles(horizontal);
    }
    return moduleDoor;
}

void ModuleDoor::executeAgony()
{
    for(int i = 0; i < Variables::tilesPerRoom * Variables::tilesPerRoom; i++)
    {
        Variables::session->getMap()->getCurrentModule()->getModuleTiles()[i]->deleteUsableObject(this);
        Variables::session->getMap()->getCurrentModule()->getModuleTiles()[i]->deleteFromEntityList(this);
    }
}

void ModuleDoor::displayPlan()
{
    if(closed)closedImage->display(planCoords);
    else openImage->display(planCoords);
    displayConnections();
}

void ModuleDoor::RCUse()
{
    use();
}

bool ModuleDoor::canBeUsed()
{
    bool result = true;
    for(int i = 0; i < Variables::allowancObjectMaxCount; i++)
    {
        if(this->allowanceObjects[i] != NULL)
        {
            if(this->allowanceObjects[i]->isAllow() == false) result = false;
        }
    }
    
    return result;
}

void ModuleDoor::displayConnections()
{
    for(int i = 0; i < Variables::allowancObjectMaxCount; i++)
    {
        if(this->requiredAllowanceObjectTypes[i] && allowanceObjects[i] != NULL)
        {
            AllowanceObject *temp = allowanceObjects[i];
            double X = (this->planCoords->X - Variables::offsetX) * Variables::scale;
            double Y = (this->planCoords->Y - Variables::offsetY) * Variables::scale;
            double deltaX = (temp->getPlanCoords()->X - Variables::offsetX) * Variables::scale;
            double deltaY = (temp->getPlanCoords()->Y - Variables::offsetY) * Variables::scale;
            if(temp->isAllow())al_draw_line(X, Y, deltaX, deltaY, al_map_rgb(0,255,0), 5);
            else al_draw_line(X, Y, deltaX, deltaY, al_map_rgb(0,0,255), 5);
        }
    }
}

void ModuleDoor::setRandomAllowanceObjects()
{
    int a = 0;
    for(int i = 0; i < Variables::allowancObjectMaxCount; i++)
    {
        if(this->requiredAllowanceObjectTypes[i])
        {
            AllowanceObject *object = Variables::session->getAllAllowanceObjects()->getRandomObject(i);
            if(object != NULL)
            {
                this->allowanceObjects[i] = object;
                a++;
            }
            else
            {
                requiredAllowanceObjectTypes[i] = false;
            }
        }
    }
}
void ModuleDoor::highlight()
{
    al_draw_filled_rectangle(
            coords->X - Variables::offsetX, 
            coords->Y - Variables::offsetY, 
            coords->X + coords->width - Variables::offsetX, 
            coords->Y + coords->height - Variables::offsetY,
            al_map_rgb(0,255,0));
}

void ModuleDoor::setRequirements()
{
    requiredAllowanceObjectTypes = new bool[Variables::allowancObjectMaxCount];
    allowanceObjects = new AllowanceObject*[Variables::allowancObjectMaxCount];
    for(int i = 0; i < Variables::allowancObjectMaxCount; i++)
    {
        allowanceObjects[i] = NULL;
        if(rand()%2 == 0)requiredAllowanceObjectTypes[i] = false;
        else requiredAllowanceObjectTypes[i] = false;
    }
    setRandomAllowanceObjects();
}

void ModuleDoor::setStartingTile()
{
    if(coords->angle == 90)
    {
        for(int i = 0; i < 4; i++)
        {
            double X = coords->X + (Variables::tileSize*i);
            if(closed)Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X,coords->Y)->addToEntityList(this);
            Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X,coords->Y)->setUsableObject(this);
        }
    }
    else 
    {
        for(int i = 0; i < 4; i++)
        {
            double Y = coords->Y + (Variables::tileSize*i);
            if(closed)Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,Y)->addToEntityList(this);
            Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,Y)->setUsableObject(this);
        }
    }
}

void ModuleDoor::useOtherSideDoor()
{
    int moduleX, moduleY;
    ModuleTile *tile;
    if(horizontal)
    {
        if(coords->Y == 0)
        {
            moduleY = Variables::session->getMap()->getModuleX();
            moduleX = Variables::session->getMap()->getModuleY()-1;
            tile = Variables::session->getMap()->getModules()[moduleX][moduleY]->getModuleTileAt(coords->X, Variables::tileSize * (Variables::tilesPerRoom-1));
        }
        else
        {
            moduleY = Variables::session->getMap()->getModuleX();
            moduleX = Variables::session->getMap()->getModuleY()+1;
            tile = Variables::session->getMap()->getModules()[moduleX][moduleY]->getModuleTileAt(coords->X, 1);
        }
    }
    else
    {
        if(coords->X == 0)
        {
            moduleY = Variables::session->getMap()->getModuleX()-1;
            moduleX = Variables::session->getMap()->getModuleY();
            tile = Variables::session->getMap()->getModules()[moduleX][moduleY]->getModuleTileAt(Variables::tileSize * (Variables::tilesPerRoom-1), coords->Y );
        }
        else
        {
            moduleY = Variables::session->getMap()->getModuleX()+1;
            moduleX = Variables::session->getMap()->getModuleY();
            tile = Variables::session->getMap()->getModules()[moduleX][moduleY]->getModuleTileAt(1, coords->Y);
        }
    }
    
    ModuleDoor *otherDoor = dynamic_cast<ModuleDoor*>(tile->getUsableObject());
    otherDoor->changeDoorStatus(moduleX, moduleY);
}

bool ModuleDoor::isClosed() const {
    return closed;
}