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
    this->displayModuleTileAI();
}

void Module::displayModuleTileAI()
{
    for(int i = 0; i < Variables::tilesPerRoom; i++)
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            int col = moduleTiles[i*Variables::tilesPerRoom + j]->getCurrentAIValue() * 2.5;
            int X = i * 50 + 25 - Variables::offsetX;
            int Y = j * 50 + 25 - Variables::offsetY;
            al_draw_circle(X, Y, 10, al_map_rgb(col, col, col),25);
        }
}

void Module::update()
{
    for(std::list<Floor*>::iterator i = floorTiles.begin(); i != floorTiles.end(); ++i)
    {
        Floor *temp = *i;
        temp->update();
    }
    for(std::list<Wall*>::iterator i = walls.begin(); i != walls.end(); ++i)
    {
        Wall *temp = *i;
        temp->update();
    }
    for(std::list<Door*>::iterator i = doors.begin(); i != doors.end(); ++i)
    {
        Door *temp = *i;
        temp->update();
    }
}

void Module::updateTileAiValue(int X, int Y)
{
    int coorX = X / 50;
    int coorY = Y / 50;
    moduleTiles[coorX*Variables::tilesPerRoom + coorY]->resetAIValue();
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

ModuleTile *Module::getModuleTileAt(int X, int Y)
{
    ModuleTile *result;
    int tileNo = (X/50)*Variables::tilesPerRoom + (Y/50)%Variables::tilesPerRoom;
    if(tileNo >= 0 && tileNo < Variables::tilesPerRoom * Variables::tilesPerRoom)
        result = this->moduleTiles[tileNo];
    else result = NULL;
    return result;
}

void Module::addWallsToTiles()
{
    for(std::list<Wall*>::iterator i = walls.begin(); i != walls.end(); ++i)
    {
        Wall *temp = *i;
        int X = temp->getCoords()->X-1;
        int Y = temp->getCoords()->Y-1;
        ModuleTile *tile = getModuleTileAt(X,Y);
        if(tile != NULL)tile->addToWallList(temp);
        X = temp->getCoords()->X-1;
        Y = temp->getCoords()->Y+1;
        tile = getModuleTileAt(X,Y);
        if(tile != NULL)tile->addToWallList(temp);
        X = temp->getCoords()->X+1;
        Y = temp->getCoords()->Y-1;
        tile = getModuleTileAt(X,Y);
        if(tile != NULL)tile->addToWallList(temp);
        X = temp->getCoords()->X+1;
        Y = temp->getCoords()->Y+1;
        tile = getModuleTileAt(X,Y);
        if(tile != NULL)tile->addToWallList(temp);
    }
}

void Module::addDoorsToTiles()
{
    for(std::list<Door*>::iterator i = doors.begin(); i != doors.end(); ++i)
    {
        Door *temp = *i;
        int X = temp->getCoords()->X-1;
        int Y = temp->getCoords()->Y-1;
        ModuleTile *tile = getModuleTileAt(X,Y);
        if(tile != NULL)tile->addToDoorList(temp);
        X = temp->getCoords()->X-1;
        Y = temp->getCoords()->Y+1;
        tile = getModuleTileAt(X,Y);
        if(tile != NULL)tile->addToDoorList(temp);
        X = temp->getCoords()->X+1;
        Y = temp->getCoords()->Y-1;
        tile = getModuleTileAt(X,Y);
        if(tile != NULL)tile->addToDoorList(temp);
        X = temp->getCoords()->X+1;
        Y = temp->getCoords()->Y+1;
        tile = getModuleTileAt(X,Y);
        if(tile != NULL)tile->addToDoorList(temp);
    }
}