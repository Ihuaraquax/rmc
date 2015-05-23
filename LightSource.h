/* 
 * File:   LightSource.h
 * Author: Qb
 *
 * Created on 23 maj 2015, 14:45
 */

#ifndef LIGHTSOURCE_H
#define	LIGHTSOURCE_H
#include "Image.h"

class LightSource {
public:
    LightSource(std::string path);
    LightSource(const LightSource& orig);
    virtual ~LightSource();
    void display();
    void update();
    void setRadius(int radius);
    void setTime(int time);
    int getTime() const;
    Coordinates* getCoords() const;
private:
    Image *image;
    Coordinates *coords;
    int time;
    int radius;
};

#endif	/* LIGHTSOURCE_H */

