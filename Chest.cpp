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
#include "EquipmentLoader.h"
#include "UsableItemLoader.h"

Chest::Chest() {
    open = false;
    std::string paths[] = {"images/chest.png"};
    this->image = new Image(1, paths, true);    
    
    this->coords = new Coordinates();
    do{
    this->coords->X = (5+ (rand()%(Variables::tilesPerRoom - 10))) * Variables::tileSize;
    this->coords->Y = (5+ (rand()%(Variables::tilesPerRoom - 10))) * Variables::tileSize;
    }while(Variables::session->getMap()->getCurrentModule()->getModuleTileAt(this->coords->X, this->coords->Y)->getObstacle() != NULL);
    this->coords->width = Variables::tileSize;
    this->coords->height = Variables::tileSize;
    this->coords->angle = 0;
    this->coords->speedX = 0;
    this->coords->speedY = 0;
    std::string backgroundPaths[] = {"images/chestBackground.png"};
    this->backgroundImage = new Image(1, backgroundPaths, false);
    this->backgroundImage->state = UI;    
    this->backgroundCoords = new Coordinates();
    this->backgroundCoords->X = 800;
    this->backgroundCoords->Y = 0;
    
    this->chestSize = rand()%5 + 1;
    this->contentType = new int[chestSize];
    this->contentValue = new int[chestSize];
    this->contentImages = new Image*[chestSize];
    this->contentCoords = new Coordinates*[chestSize];
    for(int i = 0; i < chestSize; i++)
    {
        contentCoords[i] = new Coordinates();
        contentImages[i] = NULL;
        this->contentType[i] = rand()%10;
        switch(contentType[i])
        {
            case 0:
                this->loadContent(i, 0, -1);
                break;
            case 1: 
                this->contentValue[i] = rand()%32;
                this->loadContent(i, contentType[i], contentValue[i]);
                break;
            case 2: 
                this->contentValue[i] = rand()%8 + 1;
                this->loadContent(i, contentType[i], contentValue[i]);
                break;
            case 3: 
                this->contentValue[i] = rand()%8 + 1;
                this->loadContent(i, contentType[i], contentValue[i]);
                break;
            case 4: 
                this->contentValue[i] = rand()%8 + 1;
                this->loadContent(i, contentType[i], contentValue[i]);
                break;
            case 5: 
                this->contentValue[i] = rand()%3 + 1;
                this->loadContent(i, contentType[i], contentValue[i]);
                break;
            default:
                this->contentType[i] = 0;
                this->loadContent(i, 0, -1);
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
        if(tile->getAiTile()->getRoomId() == tile->getAdjacentTiles()[i*2 +1]->getAiTile()->getRoomId())
            tile->getAdjacentTiles()[i*2 +1]->setUsableObject(this);
    }
}

Chest::Chest(bool isLoad)
{
    open = false;
    std::string paths[] = {"images/chest.png"};
    this->image = new Image(1, paths, true);   
    this->coords = new Coordinates();
    this->coords->width = Variables::tileSize;
    this->coords->height = Variables::tileSize;
    this->coords->speedX = 0;
    this->coords->speedY = 0;
    std::string backgroundPaths[] = {"images/chestBackground.png"};
    this->backgroundImage = new Image(1, backgroundPaths, false);
    this->backgroundImage->state = UI;    
    this->backgroundCoords = new Coordinates();
    this->backgroundCoords->X = 800;
    this->backgroundCoords->Y = 0;
    health = 10000;    
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
        if(CollisionDetector::isBasicCollision(mouseCoords, contentCoords[i]))
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
    else if(type == 2)
    {
        std::string paths[] = {EquipmentLoader::loadEquipmentImagePath(value, "fixtures/helmets.txt")};
        contentImages[index] = new Image(1, paths, true);
        contentCoords[index]->X = 860;
        contentCoords[index]->width = 100;
        contentCoords[index]->height = 100;
    }
    else if(type == 3)
    {
        std::string paths[] = {EquipmentLoader::loadEquipmentImagePath(value, "fixtures/chestplates.txt")};
        contentImages[index] = new Image(1, paths, true);
        contentCoords[index]->X = 860;
        contentCoords[index]->width = 100;
        contentCoords[index]->height = 100;
    }
    else if(type == 4)
    {
        std::string paths[] = {EquipmentLoader::loadEquipmentImagePath(value, "fixtures/greaves.txt")};
        contentImages[index] = new Image(1, paths, true);
        contentCoords[index]->X = 860;
        contentCoords[index]->width = 100;
        contentCoords[index]->height = 100;
    }
    else if(type == 5)
    {
        std::string paths[] = {UsableItemLoader::loadItemPath(value)};
        contentImages[index] = new Image(1, paths, true);
        contentCoords[index]->X = 860;
        contentCoords[index]->width = 100;
        contentCoords[index]->height = 100;
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
        Variables::session->getHud()->setOpenChest(NULL);
    }
    else
    {
        Variables::substate = chest;
        open = true;
        Variables::session->getHud()->setOpenChest(this);
        Variables::session->getHud()->getPlayerInventory()->init();
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

void Chest::save(std::fstream& file)
{
    file << "CH" << std::endl;
    saveGeneric(file);
    file << chestSize << ' ';
    for(int i = 0; i < chestSize; i++)file << this->contentType[i] << ' ' <<  this->contentValue[i]  << ' ';
    file << std::endl;
}

void Chest::load(std::fstream& file)
{
    loadGeneric(file);
    file >> chestSize;
    this->contentType = new int[chestSize];
    this->contentValue = new int[chestSize];
    this->contentImages = new Image*[chestSize];
    this->contentCoords = new Coordinates*[chestSize];
    for(int i = 0; i < chestSize; i++)file >> contentType[i] >> contentValue[i];
    for(int i = 0; i < chestSize; i++)
    {
        contentCoords[i] = new Coordinates();
        contentImages[i] = NULL;
        switch(contentType[i])
        {
            case 0:
                this->loadContent(i, 0, -1);
                break;
            case 1: 
                this->loadContent(i, contentType[i], contentValue[i]);
                break;
            case 2: 
                this->loadContent(i, contentType[i], contentValue[i]);
                break;
            case 3: 
                this->loadContent(i, contentType[i], contentValue[i]);
                break;
            case 4: 
                this->loadContent(i, contentType[i], contentValue[i]);
                break;
            case 5: 
                this->loadContent(i, contentType[i], contentValue[i]);
                break;
            default:
                this->loadContent(i, 0, -1);
                break;
        }
        contentCoords[i]->Y = 100 + 150*i;
    }
    
    ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y);
    tile->setObstacle(this);
    tile->addToEntityList(this);
    for(int i = 0; i < 4; i++)
    {
        if(tile->getAiTile()->getRoomId() == tile->getAdjacentTiles()[i*2 +1]->getAiTile()->getRoomId())
            tile->getAdjacentTiles()[i*2 +1]->setUsableObject(this);
    }
}