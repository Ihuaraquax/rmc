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
    Turret(double X, double Y);
    Turret(bool isLoad);
    void update();
    void display();
    void setRange(int range);
    int getRange() const;
    void setTargetAngle(double targetAngle, double X, double Y);
    double getTargetAngle() const;
    void moveUpperPart();
    void setCurrentThreatLevel(int currentThreatLevel);
    int getCurrentThreatLevel() const;
    void executeAgony();
    void attack(int weapon);
    
    void save(std::fstream& file);
    void load(std::fstream& file);
private:
    Image *upperPart;
    Image *lowerPart;
    int range;
    double targetAngle;
    int currentThreatLevel;
    bool turnRight();
};

#endif	/* TURRET_H */

