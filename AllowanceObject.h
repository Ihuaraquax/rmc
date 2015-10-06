/* 
 * File:   AllowanceObject.h
 * Author: Adiutant
 *
 * Created on 30 wrzesień 2015, 22:30
 */

#ifndef ALLOWANCEOBJECT_H
#define	ALLOWANCEOBJECT_H
#include "Obstacle.h"
#include "UsableObject.h"

class AllowanceObject : public Obstacle, public UsableObject {
public:
    AllowanceObject();
    virtual ~AllowanceObject();
    void use();
    void update();
    void display();
    void executeAgony();
    void setAllow(bool allow);
    bool isAllow() const;
    int getIntelligenceNeeded() const;
    static Entity *createObject(double X, double Y, int type);
    bool isProjectile();
    int getType() const;
private:
    Image *idleImage;
    Image *startingUpImage;
    Image *workingImage;
    bool allow;
    int timer;
    int startUpTime;
    int worktime;
    int intelligenceNeeded;
    void setUsableTiles();
    /**
     * 0 - power
     * 1 - hydraulics
     * 2 - security
     * 3 - pneumatics
     */    
    int type;
};

#endif	/* ALLOWANCEOBJECT_H */

