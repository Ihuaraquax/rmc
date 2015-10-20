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
#include "TileFactory.h"
#include "TextDisplayer.h"
#include "ModuleModificatorNames.h"

Module::Module() {
    allDecals = new AllDecals;
    modificatorsTable = new double[100];
    for(int i = 0; i < 100; i++)modificatorsTable[i] = 0;
    floorImage = Variables::images->getByName("stoneFloor3");
    floorImage->state = REPEATING;
    coords = new Coordinates();
    coords->X = 0;
    coords->Y = 0;
    coords->width = Variables::tileSize * Variables::tilesPerRoom;
    coords->height = Variables::tileSize * Variables::tilesPerRoom;
    coords->angle = 0;
    this->allLightSources = new AllLightSources();
    this->activateModificators();
}

Module::~Module()
{
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
    floorImage->display(coords);
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
    this->displayTransferBlocks();
    if(Variables::substate == game)
    {
        this->highlightTiles();
    }
}

void Module::displayMods()
{
    int modNo = 0;
    for(int i = 0; i < 100; i++)
    {
        if(this->modificatorsTable[i] != 0)
        {
            double X = 0;
            double Y = 12 * modNo;
            TextDisplayer::displayTextToLeft(X,Y,getCode(i));
            modNo++;
        }
    }
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


void Module::displayTransferBlocks()
{
    for(int i = 0; i < Variables::tilesPerRoom; i++)
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            if(moduleTiles[getModuleIndex(i,j)]->getTransferDirection() != -1)
            {
                int X = (i * Variables::tileSize + Variables::tileSize/2 - Variables::offsetX) * Variables::ScaleX * Variables::scale;
                int Y = (j * Variables::tileSize + Variables::tileSize/2 - Variables::offsetY) * Variables::ScaleY * Variables::scale;
                al_draw_circle(X, Y, (Variables::tileSize/5) * Variables::scale, al_map_rgb(0, 255, 0),25 * Variables::scale);
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
    for(int i = 0; i < Variables::tilesPerRoom; i++)
        for(int j = 0; j < Variables::tilesPerRoom; j++)
            moduleTiles[getModuleIndex(i,j)]->getAiTile()->resetAIValue();
    int index = getModuleIndex(X / Variables::tileSize, Y / Variables::tileSize);
    moduleTiles[index]->getAiTile()->getTarget()->X = X - Variables::offsetX;
    moduleTiles[index]->getAiTile()->getTarget()->Y = Y - Variables::offsetY;
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
    if(coorY < 0 || coorY > Variables::tilesPerRoom * Variables::tileSize)result = NULL;
    else if (coorX < 0 || coorX > Variables::tilesPerRoom * Variables::tileSize)result = NULL;
    else
    {
        int tileIndex = getModuleIndex(coorX / Variables::tileSize, coorY / Variables::tileSize);
        if(tileIndex >= 0 && tileIndex < Variables::tilesPerRoom * Variables::tilesPerRoom)
            result = this->moduleTiles[tileIndex];
        else result = NULL;
    }
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
    file << "MD" << std::endl;
    for(int i = 0; i < 100; i++)if(this->modificatorsTable[i] != 0)file << i << ' ';
    file << -1;
    file << std::endl;
}

void Module::load(std::fstream& file)
{ 
    std::string temp;
    file >> temp;
    int mods = 0;
    while(mods != -1)
    {
        file >> mods;
        if(mods != -1)modificatorsTable[mods] = 1;
    }
    this->moduleTiles = new ModuleTile*[Variables::tilesPerRoom * Variables::tilesPerRoom];
    for(int i = 0; i < Variables::tilesPerRoom; i++)
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            moduleTiles[i*Variables::tilesPerRoom + j] = new ModuleTile(false,0,0);
            moduleTiles[i*Variables::tilesPerRoom + j]->setCenter(i * Variables::tileSize + 25, j * Variables::tileSize + 25);
        }
    for(int i = 0; i < Variables::tilesPerRoom * Variables::tilesPerRoom; i++)
    {
        TileFactory::addNeighboursToTile(i, moduleTiles);
    }
    Floor *floor = new Floor();
    Coordinates *coords = new Coordinates();
    coords->X = 0;
    coords->Y = 0;
    coords->height = Variables::tileSize * Variables::tilesPerRoom;
    coords->width = Variables::tileSize * Variables::tilesPerRoom;
    floor->setCoords(coords);
    std::string path = "images/stoneFloor3.jpg";
    Image *image = new Image(path, false);
    image->state = REPEATING;
    floor->setImage(image);
    WallFactory *wallFactory = new WallFactory();
    wallFactory->setModuleBasicWalls(this);
    delete wallFactory;
    TileFactory::defineTilesSides(this);
}

void Module::setPlanCoords(int X, int Y)
{
    floorPlanCoords = new Coordinates();
    floorPlanCoords->X = (coords->X + X * (Variables::tileSize * Variables::tilesPerRoom + 100));
    floorPlanCoords->Y = (coords->Y + Y * (Variables::tileSize * Variables::tilesPerRoom + 100));
    floorPlanCoords->width = coords->width;
    floorPlanCoords->height = coords->height;
}

void Module::displayPlan()
{
    floorImage->display(floorPlanCoords);
}

void Module::activateModificators()
{
    if(this->modificatorsTable[21] != 0)
    {
        LightSource *shadow = new LightSource("images/moduleShadow.png");
        shadow->setTime(-1);
        shadow->getCoords()->X = 0;
        shadow->getCoords()->Y = 0;
        shadow->setAsGlobal();
        shadow->setAsNegative();
        this->allLightSources->addSource(shadow);
    }
}

AllLightSources* Module::getAllLightSources() const {
    return allLightSources;
}

void Module::setModificator(int modId)
{
    this->modificatorsTable[modId] = 1;
}

void Module::highlightTiles()
{
    for(int i = 0; i < Variables::tilesPerRoom; i++)
        for(int j = 0; j < Variables::tilesPerRoom; j++)
            getModuleTileAt(i * Variables::tileSize,j * Variables::tileSize)->highlightTile();
}