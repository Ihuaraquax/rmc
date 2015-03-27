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
    al_draw_circle(coords->X - Variables::offsetX + coords->width/2, coords->Y - Variables::offsetY + coords->height/2, static_cast<DistanceBuffer*>(buffer)->GetDistance(), al_map_rgb(0,255,0), 5);
}
void BuffRod::setCoords(double X, double Y)
{
    coords->X = X - ((int)X % Variables::tileSize);
    coords->Y = Y - ((int)Y % Variables::tileSize);
    for(int i = 0; i < Variables::tilesPerRoom; i++)
        for(int j = 0; j < Variables::tilesPerRoom; j++)
        {
            if(Variables::proximity(X,Y, i * Variables::tileSize, j * Variables::tileSize) <= static_cast<DistanceBuffer*>(buffer)->GetDistance()+25)
                Variables::session->getMap()->getCurrentModule()->getModuleTileAt(i * Variables::tileSize, j * Variables::tileSize)->propagateBuffs(buffer);
        }
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(X,Y)->setObstacle(this);
    static_cast<DistanceBuffer*>(buffer)->setCoords(X + coords->width/2, Y + coords->height/2);
}

void BuffRod::executeAgony()
{
    Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X,coords->Y)->depropagateBuffs(buffer);
}

void BuffRod::save(std::fstream& file)
{
    file << "BR" << std::endl;
    saveGeneric(file);
    file << this->buffer->GetBuffType()  << ' ' <<  this->buffer->GetBuffValue()  << ' ';
    file << std::endl;
}