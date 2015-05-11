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
    ObstacleDoor();
    void setCoords(double X, double Y);
    virtual ~ObstacleDoor();
    void setAngle(bool vertical);
    void use();
    void update();
    void display();
    void displayPlan();
    bool isBarricade();
    void save(std::fstream &file);
    void load(std::fstream &file);
    void executeAgony();
    
    static Entity *CreateObstacleDoor(double X, double Y);
    void RCUse();
private:
    Image *closedImage;
    Image *openImage;
    bool closed;
    bool vertical;
};

#endif	/* OBSTACLEDOOR_H */

