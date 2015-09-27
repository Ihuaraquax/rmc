/* 
 * File:   LightSource.cpp
 * Author: Qb
 * 
 * Created on 23 maj 2015, 14:45
 */

#include "LightSource.h"
#include "globalVariables.h"

LightSource::LightSource(std::string path) {
    image = new Image(path, false);
    image->state = NORMAL;
    coords= new Coordinates();
    coords->X = 200;
    coords->Y = 200;
    time = -1;
    negative = false;
    radius = 50;
}

void LightSource::setRadius(int radius) {
    this->radius = radius;
}

void LightSource::setTime(int time) {
    this->time = time;
}

int LightSource::getTime() const {
    return time;
}

Coordinates* LightSource::getCoords() const {
    return coords;
}

LightSource::LightSource(const LightSource& orig) {
}

LightSource::~LightSource() {
    delete image;
    delete coords;
}

void LightSource::display()
{
    if(negative)al_set_blender(ALLEGRO_DEST_MINUS_SRC, ALLEGRO_ONE, ALLEGRO_ONE);
    else al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);
    image->display(coords);
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
}

void LightSource::update()
{
    if(time > 0)time--;
}

void LightSource::setAsGlobal()
{
    this->image->state = UI;
}

void LightSource::setAsNegative()
{
    negative = true;
}

void LightSource::decreaseTileLightValue()
{
    ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y);
    if(tile != NULL)
    {
        tile->addToLightValue(-radius);
    }
}

void LightSource::increaseTileLightValue()
{
    ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y);
    if(tile != NULL)
    {
        tile->addToLightValue(radius);
    }
}