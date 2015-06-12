/* 
 * File:   PlanStep.cpp
 * Author: Qb
 * 
 * Created on 24 kwiecień 2015, 20:22
 */

#include "PlanStep.h"
#include "GlobalImages.h"
#include "globalVariables.h"

PlanStep::PlanStep() {
    this->arrowImage = Variables::images->getByName("arrow");
    this->spaceMarkerImage = Variables::images->getByName("spaceMarker");
    coords = new Coordinates();
    coords->width = 100;
    coords->height = 100;
}

PlanStep::PlanStep(const PlanStep& orig) {
}

PlanStep::~PlanStep() {
    arrowImage= NULL;
    spaceMarkerImage = NULL;
}

void PlanStep::display()
{
    if(Variables::substate == game)
    {
        Coordinates *displayCoords = new Coordinates();
        if(moduleX == Variables::session->getMap()->getModuleX() && moduleY == Variables::session->getMap()->getModuleY())
        {
            displayCoords->X = coords->X - (moduleX * Variables::tileSize * Variables::tilesPerRoom);
            displayCoords->Y = coords->Y - (moduleY * Variables::tileSize * Variables::tilesPerRoom);
            displayCoords->width = coords->width;
            displayCoords->height = coords->height;
            if(displayCoords->X - Variables::offsetX < Variables::RES_WIDTH && displayCoords->X + displayCoords->width - Variables::offsetX > 0 &&
               displayCoords->Y - Variables::offsetY < Variables::RES_HEIGHT - 170 && displayCoords->Y + displayCoords->height - Variables::offsetY > 0)
                spaceMarkerImage->display(displayCoords);
            else
            {
                if(displayCoords->X - Variables::offsetX > Variables::RES_WIDTH)displayCoords->X = Variables::RES_WIDTH + Variables::offsetX - 50;
                if(displayCoords->X - Variables::offsetX < 0)displayCoords->X = Variables::offsetX;
                if(displayCoords->Y - Variables::offsetY > Variables::RES_HEIGHT - 170)displayCoords->Y = Variables::RES_HEIGHT + Variables::offsetY - 170;
                if(displayCoords->Y - Variables::offsetY < 0)displayCoords->Y = Variables::offsetY;
                displayCoords->angle = Variables::getAngle(displayCoords->X, displayCoords->Y, coords->X, coords->Y);
                arrowImage->display(displayCoords);
            }
        }
        else
        {
            displayCoords->X = (Variables::tileSize * Variables::tilesPerRoom * 0.5) * (moduleX+1);
            displayCoords->Y = (Variables::tileSize * Variables::tilesPerRoom * 0.5) * (moduleY+1);
            if(displayCoords->X - Variables::offsetX > Variables::RES_WIDTH)displayCoords->X = Variables::RES_WIDTH + Variables::offsetX - 50;
            if(displayCoords->X - Variables::offsetX < 0)displayCoords->X = Variables::offsetX;
            if(displayCoords->Y - Variables::offsetY > Variables::RES_HEIGHT - 170)displayCoords->Y = Variables::RES_HEIGHT + Variables::offsetY - 170;
            if(displayCoords->Y - Variables::offsetY < 0)displayCoords->Y = Variables::offsetY;
            displayCoords->angle = Variables::getAngle(displayCoords->X, displayCoords->Y,  Variables::tileSize * Variables::tilesPerRoom * 0.5 * Variables::session->getMap()->getModuleX(),  
                    Variables::tileSize * Variables::tilesPerRoom * 0.5 * Variables::session->getMap()->getModuleY());
            arrowImage->display(displayCoords);
        }
        delete displayCoords;
    }
    else if(Variables::substate == plan)
    {
        spaceMarkerImage->display(coords);
    }
}

void PlanStep::displayPathToNext(Coordinates* nextCoords)
{
    al_draw_line((coords->X + coords->width/2 - Variables::offsetX)* Variables::scale, (coords->Y + coords->height/2- Variables::offsetY)* Variables::scale,
                (nextCoords->X + nextCoords->width/2 - Variables::offsetX)* Variables::scale, (nextCoords->Y + nextCoords->height/2- Variables::offsetY)* Variables::scale,
                al_map_rgb(0,255,0), 3);
}

Coordinates* PlanStep::getCoords() const {
    return coords;
}


void PlanStep::setCoords(double X, double Y, int moduleX, int moduleY)
{
    coords->X = X;
    coords->Y = Y;
    this->moduleX = moduleX;
    this->moduleY = moduleY;
}

int PlanStep::getModuleY() const {
    return moduleY;
}

int PlanStep::getModuleX() const {
    return moduleX;
}

void PlanStep::save(std::fstream& savefile)
{
    savefile << "PS" << ' ';
    savefile << coords->X << ' ' << coords->Y << ' ' << moduleX << ' ' << moduleY << ' ';
    savefile << std::endl;
}

void PlanStep::load(std::fstream& savefile)
{
    std::string temp;
    savefile >> temp >> coords->X >> coords->Y >> moduleX >> moduleY;
}