/* 
 * File:   Turret.h
 * Author: Qb
 *
 * Created on 31 styczeń 2015, 21:30
 */

#ifndef TURRET_H
#define	TURRET_H
#include "Entity.h"

class Turret : public Entity{
public:
    Turret();
    void update();
    void display();
private:
    Image *upperPart;
    Image *lowerPart;
};

#endif	/* TURRET_H */

