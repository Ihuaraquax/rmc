/* 
 * File:   Obstacle.h
 * Author: Qb
 *
 * Created on 1 luty 2015, 12:48
 */

#ifndef OBSTACLE_H
#define	OBSTACLE_H
#include "Entity.h"

class Obstacle : public Entity {
public:
    Obstacle();
    Obstacle(double X, double Y);
    void setAsWall();
    void setAsCornerWall(int corner);
    bool isBarricade();
    void display();
    void setStartingTile();
protected:
    Image *damagedImage;
    Image *damagedImage2;
};

#endif	/* OBSTACLE_H */

