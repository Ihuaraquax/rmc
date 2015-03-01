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

Chest::Chest() {
    open = false;
    std::string paths[] = {"images/chest.jpg"};
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
        contentImages[i] = NULL;
        this->contentType[i] = rand()%2;
        switch(contentType[i])
        {
            case 0: 
                this->contentValue[i] = rand()%32;
                this->loadContent(i, contentType[i], contentValue[i]);
                break;
            case 1:
                this->loadContent(i, 0, -1);
                break;
        }
        contentCoords[i] = new Coordinates();
        contentCoords[i]->X = 860;
        contentCoords[i]->Y = 100 + 150*i;
    }
    health = 100;
    
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

int Chest::getSelectedField()
{
    int result = -1;
    for(int i = 0; i < chestSize; i++)
    {
        if(contentCoords[i]->X < Variables::mouse_x && contentCoords[i]->X + contentCoords[i]->width > Variables::mouse_x)
        if(contentCoords[i]->Y < Variables::mouse_y && contentCoords[i]->Y + contentCoords[i]->height > Variables::mouse_y)
            result = i;
    }    
    return result;
}

void Chest::loadContent(int index, int type, int value)
{
    if(contentImages[index] != NULL)delete contentImages[index];
    if(type == 0)
    {
        std::string paths[] = {"images/noEquipmentInSlot.png"};
        contentImages[index] = new Image(1, paths, false);
    }
    if(type == 1)
    {
        std::string path;
        char *temp;
        std::fstream file;
        file.open("fixtures/weapons.txt", std::ios::in);
        for(int i = 0; i <= value; i++)std::getline(file, path);
        path.copy(temp, 100, path.find_last_of(" "));
        std::string paths[] = {temp};
        contentImages[index] = new Image(1, paths, false);
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