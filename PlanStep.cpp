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
    this->arrowImage = Variables::images->getPlanStepArrow();
    this->spaceMarkerImage = Variables::images->getPlanStepSpaceMarker();
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
        displayCoords->X = coords->X;
        displayCoords->Y = coords->Y;
        displayCoords->width = coords->width;
        displayCoords->height = coords->height;
        if(coords->X - Variables::offsetX < Variables::RES_WIDTH && coords->X + coords->width - Variables::offsetX > 0 &&
           coords->Y - Variables::offsetY < Variables::RES_HEIGHT - 170 && coords->Y + coords->height - Variables::offsetY > 0)
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
        delete displayCoords;
    }
    else if(Variables::substate == plan)
    {
        spaceMarkerImage->display(coords);
    }
}

void PlanStep::displayPathToNext(Coordinates* nextCoords)
{
    al_draw_line((coords->X + coords->width/2 - Variables::offsetX) * Variables::ScaleX, (coords->Y + coords->height/2- Variables::offsetY) * Variables::ScaleX,
                (nextCoords->X + nextCoords->width/2 - Variables::offsetX) * Variables::ScaleX, (nextCoords->Y + nextCoords->height/2- Variables::offsetY) * Variables::ScaleX,
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