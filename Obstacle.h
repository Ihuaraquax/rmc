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
    void setCoords(double X, double Y);
    void setAsWall();
    void setAsCornerWall(int corner);
    bool isBarricade();
    void display();
    void displayPlan();
    void setStartingTile();
    void save(std::fstream &file);
    void load(std::fstream &file);
    
    static Entity *CreateObstacle(double X, double Y);
protected:
    Image *damagedImage;
    Image *damagedImage2;
    bool isWall;
};

#endif	/* OBSTACLE_H */

