/* 
 * File:   ObstacleDoor.h
 * Author: Qb
 *
 * Created on 19 marzec 2015, 20:57
 */

#ifndef OBSTACLEDOOR_H
#define	OBSTACLEDOOR_H
#include "Obstacle.h"
#include "UsableObject.h"

class ObstacleDoor : public Obstacle, public UsableObject{
public:
    ObstacleDoor(double X, double Y);
    virtual ~ObstacleDoor();
    void setAngle(bool vertical);
    void use();
    void update();
    void display();
    bool isBarricade();
private:
    Image *closedImage;
    Image *openImage;
    bool closed;
    bool vertical;
};

#endif	/* OBSTACLEDOOR_H */

