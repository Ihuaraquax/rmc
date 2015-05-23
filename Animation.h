/* 
 * File:   Animation.h
 * Author: Qb
 *
 * Created on 21 maj 2015, 19:35
 */

#ifndef ANIMATION_H
#define	ANIMATION_H
#include "Image.h"
#include "Coordinates.h"
#include <iostream>

enum DISPLAY_ORDER
{
    random, sequential, stillImage
};

class Animation {
public:
    Animation();
    virtual ~Animation();
    void setAnimation(std::string file, int frameWidth, int frameHeight);
    void display(Coordinates* coords);
    void setDelay(int delay);
    void setDuration(int seconds);
private:
    Image **images;
    int currentImage;
    int imageCount;
    int timer;
    int delay;     
};

#endif	/* ANIMATION_H */

