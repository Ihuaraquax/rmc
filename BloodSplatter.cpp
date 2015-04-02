/* 
 * File:   BloodSplatter.cpp
 * Author: Qb
 * 
 * Created on 19 marzec 2015, 20:28
 */

#include "BloodSplatter.h"
#include "globalVariables.h"
#include <iostream>

BloodSplatter::BloodSplatter(double X, double Y) {
    coords = new Coordinates();
    coords->X = X;
    coords->Y = Y;
    coords->angle = rand()%360;
    int type = rand()%5;
    switch(type)
    {
        case 0: image = Variables::images->getBloodSplatter1();
            break;
        case 1: image = Variables::images->getBloodSplatter2();
            break;
        case 2: image = Variables::images->getBloodSplatter3();
            break;
        case 3: image = Variables::images->getBloodSplatter4();
            break;
        case 4: image = Variables::images->getBloodSplatter5();
            break;
    }
}
