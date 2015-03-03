/* 
 * File:   Chest.cpp
 * Author: Qb
 * 
 * Created on 28 luty 2015, 15:03
 */

#include <fstream>

#include "Chest.h"
#include "globalVariables.h"
#include "ModuleTile.h"
#include "CollisionDetector.h"
#include "WeaponLoader.h"

Chest::Chest() {
    open = false;
    std::string paths[] = {"images/chest.png"};
    this->image = new Image(1, paths, true);    
    
    this->coords = new Coordinates();
    this->coords->X = 300;
    this->coords->Y = 200;
    this->coords->width = Variables::tileSize;
    this->coords->height = Variables::tileSize;
    
    std::string backgroundPaths[] = {"images/chestBackground.png"};
    this->backgroundImage = new Image(1, backgroundPaths, false);
    this->backgroundImage->state = UI;    
    this->backgroundCoords = new Coordinates();
    this->backgroundCoords->X = 800;
    this->backgroundCoords->Y = 0;
    
    this->chestSize = 4;
    this->contentType = new int[chestSize];
    this->contentValue = new int[chestSize];
    this->contentImages = new Image*[chestSize];
    this->contentCoords = new Coordinates*[chestSize];
    for(int i = 0; i < chestSize; i++)
    {
        contentCoords[i] = new Coordinates();
        contentImages[i] = NULL;
        this->contentType[i] = rand()%2;
        switch(contentType[i])
        {
            case 0:
                this->loadContent(i, 0, -1);
                break;
            case 1: 
                this->contentValue[i] = rand()%32;
                this->loadContent(i, contentType[i], contentValue[i]);
                break;
        }
        contentCoords[i]->Y = 100 + 150*i;
    }
    health = 10000;
    
    ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y);
    tile->setObstacle(this);
    tile->addToEntityList(this);
    for(int i = 0; i < 4; i++)
    {
        tile->getAdjacentTiles()[i*2 +1]->setUsableObject(this);
    }
}

Chest::~Chest() {
    for(int i = 0; i < chestSize; i++)
    {
        delete contentCoords[i];
        delete contentImages[i];
    }
        delete []contentCoords;
        delete []contentImages;
        delete []contentValue;
        delete []contentType;
        delete backgroundImage;
        delete backgroundCoords;
}

void Chest::display()
{
    image->display(coords);
}

void Chest::displayContent()
{
    this->backgroundImage->display(backgroundCoords);
    for(int i = 0 ; i < chestSize; i++)contentImages[i]->display(contentCoords[i]);
}

int Chest::getContentType(int index)
{
    return contentType[index];
}

int Chest::getContentValue(int index)
{
    return contentValue[index];
}

bool Chest::isOpen() const {
    return open;
}

int Chest::getSelectedContent() const {
    return selectedContent;
}

int Chest::getSelectedField()
{
    int result = -1;
    Coordinates *mouseCoords = new Coordinates();
    mouseCoords->X = Variables::mouse_x;
    mouseCoords->Y = Variables::mouse_y;
    for(int i = 0; i < chestSize; i++)
    {
        if(CollisionDetector::isCollision(mouseCoords, contentCoords[i]))
        {
            result = i;
            break;
        }
    }
    return result;
}

void Chest::loadContent(int index, int type, int value)
{
    if(contentImages[index] != NULL)delete contentImages[index];
    if(type == 0 || value == -1)
    {
        std::string paths[] = {"images/noEquipmentInSlot.png"};
        contentImages[index] = new Image(1, paths, false);
        contentCoords[index]->X = 860;
        contentCoords[index]->width = 100;
        contentCoords[index]->height = 100;
    }
    else if(type == 1)
    {
        std::string paths[] = {WeaponLoader::loadPath(value)};
        contentImages[index] = new Image(1, paths, true);
        contentCoords[index]->X = 810;
        contentCoords[index]->width = 200;
        contentCoords[index]->height = 90;
    }
    contentImages[index]->state = UI;
    contentType[index] = type;
    contentValue[index] = value;
}

void Chest::use()
{
    if(open)
    {
        Variables::substate = game;
        open = false;
        Variables::session->setOpenChest(NULL);
    }
    else
    {
        Variables::substate = chest;
        open = true;
        Variables::session->setOpenChest(this);
        Variables::session->getPlayerInventory()->init();
    }
}
void Chest::update()
{
    
}

bool Chest::isFieldNotEmpty(int index)
{
    return contentType[index] != 0;
}

void Chest::swapContent(int firstContentIndex, int secondContentIndex)
{
    int secondType = contentType[secondContentIndex];
    int secondValue = contentValue[secondContentIndex];
    this->loadContent(secondContentIndex, contentType[firstContentIndex], contentValue[firstContentIndex]);
    this->loadContent(firstContentIndex, secondType, secondValue);
}