/* 
 * File:   Door.h
 * Author: Qb
 *
 * Created on 23 listopad 2014, 18:54
 */

#ifndef DOOR_H
#define	DOOR_H
#include "Coordinates.h"
#include "UsableObject.h"

class Door : public UsableObject {
public:
    Door(Coordinates *coords);
    ~Door();
    void display();
    void update();
    Coordinates* getCoords() const;
    void setOpen(bool open);
    bool isOpen() const;
    void getHit(int damage, int damageType);
    int getHealth() const;
    void use();
private:
    Coordinates *coords;
    bool open;
    int health;
    int armor;
    double *elementalResists;
};

#endif	/* DOOR_H */

