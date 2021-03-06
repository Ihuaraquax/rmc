/* 
 * File:   AllowanceObject.cpp
 * Author: Adiutant
 * 
 * Created on 30 wrzesień 2015, 22:30
 */

#include "AllowanceObject.h"
#include "globalVariables.h"

AllowanceObject::AllowanceObject() {
    allow = false;
    timer = 0;
    startUpTime = 2 * Variables::fps;
    worktime = 120 * Variables::fps;
    intelligenceNeeded = 10;
}

AllowanceObject::~AllowanceObject() {
}

void AllowanceObject::use()
{
    if(allow == false)
    {
        timer = startUpTime;
    }
    else
    {
        allow = false;
        timer = 0;
    }
}

void AllowanceObject::update()
{
}

void AllowanceObject::specificUpdate()
{
    if(timer > 0)
    {
        timer--;
        if(timer == 0)
        {
            if(allow)allow = false;
            else 
            {
                timer = worktime;
                allow = true;
            }
        }
    }
}

void AllowanceObject::display()
{
    if(timer > 0)
    {
        if(allow)workingImage->display(coords);
        else startingUpImage->display(coords);
    }
    else
    {
        idleImage->display(coords);
    }
}

void AllowanceObject::setAllow(bool allow) {
    this->allow = allow;
}

bool AllowanceObject::isAllow() const {
    return allow;
}

int AllowanceObject::getIntelligenceNeeded() const {
    return intelligenceNeeded;
}

void AllowanceObject::executeAgony()
{
    Variables::session->getAllAllowanceObjects()->deleteObject(this);
}

Entity *AllowanceObject::createObject(double X, double Y, int type)
{
    Entity *object = new AllowanceObject();
    AllowanceObject *temp = dynamic_cast<AllowanceObject*>(object);
    temp->type = type;
    temp->health = 1000;
    temp->maximumHealth = temp->health;
    temp->coords = new Coordinates();
    temp->coords->X = X;
    temp->coords->Y = Y;
    temp->coords->width = Variables::tileSize;
    temp->coords->height = Variables::tileSize;
    temp->coords->angle = 0;
    temp->coords->speedX = 0;
    temp->coords->speedY = 0;
    temp->idleImage = Variables::images->getByName("powerIdle");
    temp->startingUpImage = Variables::images->getByName("powerStartup");
    temp->workingImage = Variables::images->getByName("powerWorking");
    temp->isWall = false;
    temp->bleeds = false;
    temp->armor = 1;
    for(int i = 0; i < Variables::damageTypeCount; i++)temp->elementalResists[i] = 0.5;
    temp->elementalResists[explosive] = 0;
    Variables::session->getAllAllowanceObjects()->addObject(temp);
    return object;
}

bool AllowanceObject::isProjectile()
{
    return false;
}

int AllowanceObject::getType() const {
    return type;
}

int AllowanceObject::getModuleY() const {
    return moduleY;
}

int AllowanceObject::getModuleX() const {
    return moduleX;
}

void AllowanceObject::setUsableTiles()
{
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X - Variables::tileSize,coords->Y)->setUsableObject(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X + Variables::tileSize,coords->Y)->setUsableObject(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y - Variables::tileSize)->setUsableObject(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y + Variables::tileSize)->setUsableObject(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->setObstacle(this);
}

void AllowanceObject::setModuleCoords(int X, int Y)
{
    this->moduleX = X;
    this->moduleY = Y;
}

void AllowanceObject::highlight()
{
    al_draw_filled_rectangle(
            coords->X - Variables::offsetX, 
            coords->Y - Variables::offsetY, 
            coords->X + coords->width - Variables::offsetX, 
            coords->Y + coords->height - Variables::offsetY,
            al_map_rgb(0,255,0));
}


bool AllowanceObject::isBarricade()
{
    return true;
}