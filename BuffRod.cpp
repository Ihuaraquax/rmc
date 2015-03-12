/* 
 * File:   BuffRod.cpp
 * Author: Qb
 * 
 * Created on 12 marzec 2015, 13:20
 */

#include "BuffRod.h"
#include "globalVariables.h"
#include "DistanceBuffer.h"

BuffRod::BuffRod(GenericBuffer * buff) {
    buffer = buff;
    coords = new Coordinates();
    coords->width = 50;
    coords->height = 50;
    std::string paths[] = {"images/bufferRod.png"};
    image = new Image(1, paths, true);
    this->health = 10;
}
void BuffRod::update()
{
    
}
void BuffRod::display()
{
    image->display(coords);
    al_draw_circle(coords->X - Variables::offsetX, coords->Y - Variables::offsetY, static_cast<DistanceBuffer*>(buffer)->GetDistance(), al_map_rgb(0,255,0), 5);
}
void BuffRod::setCoords(double X, double Y)
{
    coords->X = X - ((int)X % Variables::tileSize);
    coords->Y = Y - ((int)Y % Variables::tileSize);
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X,Y)->propagateBuffs(buffer, static_cast<DistanceBuffer*>(buffer)->GetModuleTileDistance());
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X,Y)->setObstacle(this);
}

void BuffRod::executeAgony()
{
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->depropagateBuffs(buffer);
}