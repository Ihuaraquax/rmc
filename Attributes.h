/* 
 * File:   Attributes.h
 * Author: Qb
 *
 * Created on 21 luty 2015, 18:02
 */

#ifndef ATTRIBUTES_H
#define	ATTRIBUTES_H
#include <fstream>

class Attributes {
public:
    Attributes();
    virtual ~Attributes();
    int getAccuracy() const;
    int getInteligence() const;
    int getSpeed() const;
    int getStrength() const;
    
    void addStrength(int toAdd);
    void addSpeed(int toAdd);
    void addInteligence(int toAdd);
    void addAccuracy(int toAdd);
    
    void save(std::fstream &file);
    void load(std::fstream &file);
private:
    int strength;
    int speed;
    int inteligence;
    int accuracy;
    int pointsLeft;
    int skillPointsLeft[4];
};

#endif	/* ATTRIBUTES_H */

