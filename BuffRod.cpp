/* 
 * File:   BuffRod.cpp
 * Author: Qb
 * 
 * Created on 12 marzec 2015, 13:20
 */

#include "BuffRod.h"
#include "globalVariables.h"
#include "DistanceBuffer.h"

BuffRod::BuffRod()
{
    coords = new Coordinates();
    coords->width = Variables::tileSize;
    coords->height = Variables::tileSize;
    image = Variables::images->getBuffRod();
    this->health = 10;
}

BuffRod::~BuffRod()
{
    image = NULL;
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
    file << this->buffer->GetBuffType()  << ' ' <<  this->buffer->GetBuffValue()  << ' '
         << static_cast<DistanceBuffer*>(buffer)->GetDistance() << ' ';
    file << std::endl;
}

void BuffRod::load(std::fstream& file)
{
    loadGeneric(file);
    double type, value, distance;
    file >> type >> value >> distance;
    GenericBuffer *buff = new DistanceBuffer(type, value, distance);
    buffer = buff;
}

void BuffRod::setBuffer(GenericBuffer* buffer) {
    this->buffer = buffer;
}

Entity *BuffRod::CreateBuffRod(double X, double Y)
{
    Entity *buffRod = new BuffRod();
    if(X != -1 && Y != -1)buffRod->setCoords(X,Y);
    return buffRod;
}

Entity *BuffRod::CreateBuffRod(double X, double Y, GenericBuffer* buff)
{
    Entity *buffRod = new BuffRod();
    if(X != -1 && Y != -1)buffRod->setCoords(X,Y);
    dynamic_cast<BuffRod*>(buffRod)->setBuffer(buff);
    return buffRod;
}