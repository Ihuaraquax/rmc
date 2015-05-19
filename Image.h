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

class Image {
public:
    Image(std::string path, bool isMask);
    ~Image();
    void display(Coordinates *coords);
    std::string getImagePath() const;
    DisplayState state;
private:
    ALLEGRO_BITMAP *image;
    int imageCenterX, imageCenterY;
    std::string imagePath;
    void displayMultiples(Coordinates *coords);
    void displayCut(Coordinates *coords);
    void displayNormal(Coordinates *coords);
    void displayBasic(Coordinates *coords);
    void displayUI(Coordinates *coords);
};

#endif	/* IMAGE_H */

