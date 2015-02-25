/* 
 * File:   Image.h
 * Author: Qb
 *
 * Created on 4 listopad 2014, 22:27
 */

#ifndef IMAGE_H
#define	IMAGE_H
#include <iostream>
#include <string>
#include "Coordinates.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

enum DisplayState{
    BASIC, NORMAL, REPEATING, CUT, UI
};

enum ImageOrder{
    SINGLE, LOOP, RANDOM
};

class Image {
public:
    Image(int count, std::string paths[], bool isMask);
    ~Image();
    void display(Coordinates *coords);
    void nextImage();
    void specificImage(int imageNo);
    DisplayState state;
    ImageOrder order;
private:
    ALLEGRO_BITMAP **images;
    int imageCount;
    int currentImage;
    int *imageCenterX, *imageCenterY;
    void displayMultiples(Coordinates *coords);
    void displayCut(Coordinates *coords);
    void displayNormal(Coordinates *coords);
    void displayBasic(Coordinates *coords);
    void displayUI(Coordinates *coords);
};

#endif	/* IMAGE_H */

