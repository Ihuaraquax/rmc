/* 
 * File:   PlanStep.h
 * Author: Qb
 *
 * Created on 24 kwiecień 2015, 20:22
 */

#ifndef PLANSTEP_H
#define	PLANSTEP_H
#include "Coordinates.h"
#include "Image.h"
#include <fstream>

class PlanStep {
public:
    PlanStep();
    PlanStep(const PlanStep& orig);
    virtual ~PlanStep();
    void display();
    void displayPathToNext(Coordinates *nextCoords);
    Coordinates* getCoords() const;
    void setCoords(double X, double Y, int moduleX, int moduleY);
    int getModuleY() const;
    int getModuleX() const;
    void save(std::fstream &savefile);
    void load(std::fstream &savefile);
private:
    Coordinates *coords;
    int moduleX, moduleY;
    Image *spaceMarkerImage;
    Image *arrowImage;
};

#endif	/* PLANSTEP_H */

