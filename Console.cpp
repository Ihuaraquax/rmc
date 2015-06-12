/* 
 * File:   Console.cpp
 * Author: Qb
 * 
 * Created on 3 maj 2015, 13:42
 */

#include "Console.h"
#include "globalVariables.h"

Console::Console() {
    coords = new Coordinates();
    coords->height = Variables::tileSize;
    coords->width = Variables::tileSize;
    image = Variables::images->getByName("console");
}

Console::Console(const Console& orig) {
}

Console::~Console() {
}

void Console::use()
{
    Variables::substate = console;
    double height = Variables::RES_HEIGHT - 120;
    Variables::scale =  height/(Variables::tileSize * Variables::tilesPerRoom);
    Console::offsetX = Variables::offsetX;
    Console::offsetY = Variables::offsetY;
    Variables::offsetX = -512;
    Variables::offsetY = 0;
}

Entity *Console::CreateConsole(double X, double Y)
{
    Entity *console = new Console();
    
    if(X == 0 && Y == 0)dynamic_cast<Console*>(console)->setRandomCoords();
    else
    {
        console->getCoords()->X = X;
        console->getCoords()->Y = Y;
    }
    return console;
}

void Console::setRandomCoords()
{
    int X, Y;
    bool isViableTile = false;
    do
    {        
        X = Variables::tileSize + rand()%(Variables::tileSize * (Variables::tilesPerRoom - 2));
        Y = Variables::tileSize + rand()%(Variables::tileSize * (Variables::tilesPerRoom - 2));
        X -= X%Variables::tileSize;
        Y -= Y%Variables::tileSize;
        ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X, Y);
        if(tile->getObstacle() == NULL && tile->getEntityList() == NULL)isViableTile = true;
        else isViableTile = false;
    } while(!isViableTile);
    coords->X = X;
    coords->Y = Y;
}

void Console::save(std::fstream& file)
{
    file << "CO" << std::endl;
    this->saveGeneric(file);
    file << std::endl;
}

void Console::load(std::fstream& file)
{
    loadGeneric(file);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->setObstacle(this);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->addToThreatLevel(threatLevel);
}

void Console::setStartingTile()
{
    ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y);
    tile->setObstacle(this);
    tile->addToEntityList(this);
    for(int i = 0; i < 4; i++)
    {
        if(tile->getAiTile()->getRoomId() == tile->getAdjacentTiles()[i*2 +1]->getAiTile()->getRoomId())
            tile->getAdjacentTiles()[i*2 +1]->setUsableObject(this);
    }
}

void Console::end()
{
    Variables::substate = game;
    Variables::offsetX = Console::offsetX;
    Variables::offsetY = Console::offsetY;
    Variables::scale = 1;
}

void Console::mouseControl()
{
    Coordinates *mosueCoords = new Coordinates();
    mosueCoords->X = Variables::mouse_x;
    mosueCoords->Y = Variables::mouse_y;
    mosueCoords->width = 50;
    mosueCoords->height = 50;
    ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt
            (Variables::mouse_x * (1/(Variables::ScaleX * Variables::scale)) + Variables::offsetX, Variables::mouse_y * (1/(Variables::ScaleY * Variables::scale)));
    if(tile != NULL)if(tile->getRemoteAccessObject() != NULL)
    {
        tile->getRemoteAccessObject()->RCUse();
    }
}

void Console::executeAgony()
{
    for(int i = 0; i < Variables::tilesPerRoom * Variables::tilesPerRoom; i++)
    {
        Variables::session->getMap()->getCurrentModule()->getModuleTiles()[i]->deleteUsableObject(this);
        Variables::session->getMap()->getCurrentModule()->getModuleTiles()[i]->deleteFromEntityList(this);
    }
}