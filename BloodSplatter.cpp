/* 
 * File:   BloodSplatter.cpp
 * Author: Qb
 * 
 * Created on 19 marzec 2015, 20:28
 */

#include "BloodSplatter.h"
#include <iostream>

BloodSplatter::BloodSplatter(double X, double Y) {
    coords = new Coordinates();
    coords->X = X;
    coords->Y = Y;
    coords->angle = rand()%360;
    int type = rand()%5;
    std::string paths[] = {""};
    switch(type)
    {
        case 0: paths[0] = "images/BloodSplater01.png";
            break;
        case 1: paths[0] = "images/BloodSplater02.png";
            break;
        case 2: paths[0] = "images/BloodSplater03.png";
            break;
        case 3: paths[0] = "images/BloodSplater04.png";
            break;
        case 4: paths[0] = "images/BloodSplater05.png";
            break;
    }
    image = new Image(1, paths, true);
    image->state = NORMAL;
}
