/* 
 * File:   LightSource.cpp
 * Author: Qb
 * 
 * Created on 23 maj 2015, 14:45
 */

#include "LightSource.h"

LightSource::LightSource(std::string path) {
    image = new Image(path, false);
    image->state = NORMAL;
    coords= new Coordinates();
    coords->X = 200;
    coords->Y = 200;
    time = -1;
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
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);
    image->display(coords);
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
}

void LightSource::update()
{
    if(time > 0)time--;
}