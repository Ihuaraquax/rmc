/* 
 * File:   Decal.cpp
 * Author: Qb
 * 
 * Created on 19 marzec 2015, 20:28
 */

#include "Decal.h"

Decal::Decal() {
    image = NULL;
    coords = NULL;
}

Decal::~Decal() {
    if(image != NULL)delete image;
    if(coords != NULL)delete coords;    
}

void Decal::display()
{
    image->display(coords);
}

void Decal::update()
{
    
}

