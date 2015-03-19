/* 
 * File:   Decal.h
 * Author: Qb
 *
 * Created on 19 marzec 2015, 20:28
 */

#ifndef DECAL_H
#define	DECAL_H
#include "Coordinates.h"
#include "Image.h"

class Decal {
public:
    Decal();
    ~Decal();
    void virtual update();
    void virtual display();
protected:
    Image *image;
    Coordinates *coords;
};

#endif	/* DECAL_H */

