/* 
 * File:   Wall.h
 * Author: Qb
 *
 * Created on 23 listopad 2014, 18:54
 */

#ifndef WALL_H
#define	WALL_H
#include "Coordinates.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

class Wall {
public:
    Wall();
    ~Wall();
    void setCoords(Coordinates *coords);
    void display();
    void update();
    bool isOnCoords(int X, int Y);
    Coordinates* getCoords() const;
    int wallSize;
private:
    Coordinates *coords;
};

#endif	/* WALL_H */

