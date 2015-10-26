/* 
 * File:   ModuleDoor.h
 * Author: Adiutant
 *
 * Created on 24 październik 2015, 18:30
 */

#ifndef MODULEDOOR_H
#define	MODULEDOOR_H
#include "Obstacle.h"
#include "UsableObject.h"
#include "AllowanceObject.h"
#include <list>

class ModuleDoor : public Obstacle, public UsableObject{
public:
    ModuleDoor(bool horizontal);
    void setCoords(double X, double Y);
    virtual ~ModuleDoor();
    void setUseTiles(bool horizontal);
    void use();
    void update();
    void display();
    void displayPlan();
    void displayConnections();
    bool isBarricade();
    void save(std::fstream &file);
    void load(std::fstream &file);
    void executeAgony();
    bool canBeUsed();
    void setRandomAllowanceObjects();
    void setStartingTile();
    
    static Entity *CreateModuleDoor(double X, double Y, bool horizontal);
    void RCUse();
    void highlight();
    void setRequirements();
    void useOtherSideDoor();
private:
    void changeDoorStatus(int moduleX, int moduleY);
    Image *closedImage;
    Image *openImage;
    bool closed;
    bool horizontal;
    AllowanceObject **allowanceObjects;
    bool *requiredAllowanceObjectTypes;    
};

#endif	/* MODULEDOOR_H */

