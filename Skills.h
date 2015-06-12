/* 
 * File:   Skills.h
 * Author: Qb
 *
 * Created on 12 czerwiec 2015, 21:12
 */

#ifndef SKILLS_H
#define	SKILLS_H
#include <iostream>
#include <fstream>
#include "Image.h"

class Skills {
public:
    Skills();
    Skills(const Skills& orig);
    virtual ~Skills();
    void display();
    void handleMouseAction();
    void save(std::fstream &savefile);
    void load(std::fstream &savefile);
    bool isSkillActive(int attribute, int number);
    void addSkillPoints(int attribute, int value);
private:
    bool **skillActive;
    std::string **skillNames;
    Image *inactiveSkillImage;
    Image *activeSkillImage;
    int skilPointsAvaiilable[4];
};

#endif	/* SKILLS_H */

