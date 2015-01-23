/* 
 * File:   Door.h
 * Author: Qb
 *
 * Created on 23 listopad 2014, 18:54
 */

#ifndef DOOR_H
#define	DOOR_H
#include "Coordinates.h"

class Door {
public:
    Door(Coordinates *coords);
    Door(const Door& orig);
    ~Door();
    void display();
    void update();
    Coordinates* getCoords() const;
    void setOpen(bool open);
    bool isOpen() const;
private:
    Coordinates *coords;
    bool open;
};

#endif	/* DOOR_H */

