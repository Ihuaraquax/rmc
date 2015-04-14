/* 
 * File:   Floor.h
 * Author: Qb
 *
 * Created on 24 listopad 2014, 18:52
 */

#ifndef FLOOR_H
#define	FLOOR_H
#include "Image.h"
#include "Coordinates.h"

class Floor {
public:
    Floor();
    ~Floor();
    void setCoords(Coordinates * coords);
    void setImage(Image *image);
    void display();
    void displayPlan();
    void update();
    void setPlanCoords(int X, int Y);
    
private:
    Image *floorPattern;
    Coordinates *coords;
    Coordinates *planCoords;
};

#endif	/* FLOOR_H */

