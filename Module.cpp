/* 
 * File:   Module.cpp
 * Author: Qb
 * 
 * Created on 23 listopad 2014, 18:54
 */

#include <list>

#include "Module.h"
#include "WallFactory.h"
#include "globalVariables.h"

Module::Module() {
    allDecals = new AllDecals;
    modificatorsTable = new double[100];
    for(int i = 0; i < 100; i++)modificatorsTable[i] = 0;
}

Module::~Module()
{
    for(std::list<Floor*>::iterator i = floorTiles.begin(); i != floorTiles.end(); ++i)
    {
        Floor *temp = *i;
        delete temp;
    }
    for(std::list<Wall*>::iterator i = walls.begin(); i != walls.end(); ++i)
    {
        Wall *temp = *i;
        delete temp;
    }
    for(std::list<Door*>::iterator i = doors.begin(); i != doors.end(); ++i)
    {
        Door *temp = *i;
//        delete temp;  Dziwny błąd - delete powoduje wyrzucenie błędu podczas wychodzenia z debug w netbeans
    }
    for(std::list<Chest*>::iterator i = chests.begin(); i != chests.end(); ++i)
    {
        Chest *temp = *i;
        delete temp;
    }
    delete allDecals;
    delete []modificatorsTable;
}

void Module::display()
{
    for(std::list<Floor*>::iterator i = floorTiles.begin(); i != floorTiles.end(); ++i)
    {
        Floor *temp = *i;
        temp->display();
    }
    for(std::list<Wall*>::iterator i = walls.begin(); i != walls.end(); ++i)
    {
        Wall *temp = *i;
        temp->display();
    }
    for(std::list<Door*>::iterator i = doors.begin(); i != doors.end(); ++i)
    {
        Door *temp = *i;
        temp->display();
    }
    allDecals->display();
//    this->displayModuleTileAI();
//    this->displayModuleThreatLevel();
//    this->displayObstacles();
//    this->displayBuffs();
}

void Module::displayBuffs()
{
    for(int i = 0; i < Variables::tilesPerRoom; i++)
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            if(moduleTiles[getModuleIndex(i,j)]->getBufferList() != NULL)
            {
                int X = i * Variables::tileSize + Variables::tileSize/2 - Variables::offsetX;
                int Y = j * Variables::tileSize + Variables::tileSize/2 - Variables::offsetY;
                al_draw_circle(X, Y, Variables::tileSize/5, al_map_rgb(0, 150, 0),25);
            }
        }
}
void Module::displayModuleTileAI()
{
    for(int i = 0; i < Variables::tilesPerRoom; i++)
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            int col = moduleTiles[getModuleIndex(i,j)]->getAiTile()->getCurrentAIValue() * 1.5;
            int X = i * Variables::tileSize + Variables::tileSize/2 - Variables::offsetX;
            int Y = j * Variables::tileSize + Variables::tileSize/2 - Variables::offsetY;
            al_draw_circle(X, Y, Variables::tileSize/5, al_map_rgb(col, col, col),25);
        }
}

void Module::displayModuleThreatLevel()
{
    for(int i = 0; i < Variables::tilesPerRoom; i++)
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            int col = moduleTiles[getModuleIndex(i,j)]->getThreatLevel() * 10;
            int X = i * Variables::tileSize + 25 - Variables::offsetX;
            int Y = j * Variables::tileSize + 25 - Variables::offsetY;
            al_draw_circle(X, Y, 10, al_map_rgb(col, col, col),25);
        }
}
void Module::displayObstacles()
{
    for(int i = 0; i < Variables::tilesPerRoom; i++)
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            if(moduleTiles[getModuleIndex(i,j)]->getObstacle() != NULL)
            {
                int X = i * Variables::tileSize + 25 - Variables::offsetX;
                int Y = j * Variables::tileSize + 25 - Variables::offsetY;
                al_draw_circle(X, Y, 10, al_map_rgb(0, 0, 0),25);
            }
        }
}
void Module::update()
{
    if(Variables::log == full)std::cout << " Module Update Floor ";
    for(std::list<Floor*>::iterator i = floorTiles.begin(); i != floorTiles.end(); ++i)
    {
        Floor *temp = *i;
        temp->update();
    }
    if(Variables::log == full)std::cout << " Module Update wall ";
    for(std::list<Wall*>::iterator i = walls.begin(); i != walls.end(); ++i)
    {
        Wall *temp = *i;
        temp->update();
    }
    if(Variables::log == full)std::cout << " Module Update door ";
    for(std::list<Door*>::iterator i = doors.begin(); i != doors.end(); ++i)
    {
        Door *temp = *i;
        temp->update();
    }
    if(Variables::log == full)std::cout << " Module Update tiles ";
    for(int i = 0; i < Variables::tilesPerRoom * Variables::tilesPerRoom; i++)
    {
        moduleTiles[i]->update();
    }
    if(Variables::log == full)std::cout << " Module Update AITles ";
    for(int i = 0; i < Variables::tilesPerRoom * Variables::tilesPerRoom; i++)
    {
        moduleTiles[i]->getAiTile()->updateCurrentAIValue();
//        for(int j = 0; j < 16; j++) moduleTiles[i]->getAiTiles()[j]->updateCurrentAIValue();
    }
    allDecals->update();
    if(Variables::log == full)std::cout << " Ai Tile ai update end";
}

void Module::updateTileAiTarget(int X, int Y)
{
    int index = getModuleIndex(X / Variables::tileSize, Y / Variables::tileSize);
    moduleTiles[index]->getAiTile()->getTarget()->X = X;
    moduleTiles[index]->getAiTile()->getTarget()->Y = Y;
}

bool Module::isObstructed(int X, int Y)
{
    bool value = false;
    for(std::list<Wall*>::iterator i = walls.begin(); i != walls.end(); ++i)
    {
        Wall *temp = *i;
        if(temp->isOnCoords(X,Y))
        {
            value = true;
            break;
        }
    }
    return value;
}

ModuleTile *Module::getModuleTileAt(int coorX, int coorY)
{
    ModuleTile *result;
    int tileIndex = getModuleIndex(coorX / Variables::tileSize, coorY / Variables::tileSize);
    if(tileIndex >= 0 && tileIndex < Variables::tilesPerRoom * Variables::tilesPerRoom)
        result = this->moduleTiles[tileIndex];
    else result = NULL;
    return result;
}

void Module::addWallsToTiles()
{
    for(std::list<Wall*>::iterator i = walls.begin(); i != walls.end(); ++i)
    {
        Wall *temp = *i;
        int X = temp->getCoords()->X-1;
        int Y = temp->getCoords()->Y+1;
        ModuleTile *tile = getModuleTileAt(X,Y);
        if(tile != NULL)tile->addToWallList(temp, 1);
        X = temp->getCoords()->X+1;
        Y = temp->getCoords()->Y-1;
        tile = getModuleTileAt(X,Y);
        if(tile != NULL)tile->addToWallList(temp, 2);
        X = temp->getCoords()->X+1;
        Y = temp->getCoords()->Y+1;
        tile = getModuleTileAt(X,Y);
        if(tile != NULL)
        {
            if(temp->getCoords()->width > temp->getCoords()->height)
                tile->addToWallList(temp, 0);
            else tile->addToWallList(temp, 3);
        }
    }
}

void Module::addDoorsToTiles()
{
    for(std::list<Door*>::iterator i = doors.begin(); i != doors.end(); ++i)
    {
        Door *temp = *i;
        int X = temp->getCoords()->X-1;
        int Y = temp->getCoords()->Y+1;
        ModuleTile *tile = getModuleTileAt(X,Y);
        if(tile != NULL)tile->addToDoorList(temp, 1);
        X = temp->getCoords()->X+1;
        Y = temp->getCoords()->Y-1;
        tile = getModuleTileAt(X,Y);
        if(tile != NULL)tile->addToDoorList(temp, 2);
        X = temp->getCoords()->X+1;
        Y = temp->getCoords()->Y+1;
        tile = getModuleTileAt(X,Y);
        if(tile != NULL)
        {
            if(temp->getCoords()->width > temp->getCoords()->height)
                tile->addToDoorList(temp, 0);
            else tile->addToDoorList(temp, 3);
        }
    }
}

int Module::getModuleIndex(int X, int Y)
{
    return X*Variables::tilesPerRoom + Y;
}

void Module::deleteWall(Wall* toDelete)
{
    walls.remove(toDelete);
}

int Module::getIndexOfModule(ModuleTile* tile)
{
    for(int i = 0; i < Variables::tilesPerRoom * Variables::tilesPerRoom; i++)
    {
        if(moduleTiles[i] == tile)return i;
    }
    return -1;
}

ModuleTile** Module::getModuleTiles() const {
    return moduleTiles;
}

void Module::deleteDoor(Door* toDelete)
{
    doors.remove(toDelete);
}

void Module::useChest()
{
    Variables::session->getHud()->getPlayerInventory()->init();    
    for(std::list<Chest*>::iterator i = chests.begin(); i != chests.end(); ++i)
    {
        Chest *temp = *i;
        temp->use();
    }
}

AllDecals* Module::getAllDecals() const {
    return allDecals;
}

double* Module::getModificatorsTable() const {
    return modificatorsTable;
}

void Module::save(std::fstream& file)
{
    file << "MO" << std::endl;
    file << "MD" << std::endl;
    for(int i = 0; i < 100; i++)if(this->modificatorsTable[i] != 0)file << i << ' ';
    file << std::endl;
}