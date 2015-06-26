/* 
 * File:   Skills.cpp
 * Author: Qb
 * 
 * Created on 12 czerwiec 2015, 21:12
 */

#include "Skills.h"
#include "globalVariables.h"
#include "TextDisplayer.h"
#include "CollisionDetector.h"

Skills::Skills() {
    skillNames = new std::string*[4];
    skillActive = new bool*[4];
    for(int i = 0; i < 4; i++)
    {
        skillNames[i] = new std::string[8];
        skillActive[i] = new bool[8];
        for(int j = 0; j < 8; j++)skillActive[i][j] = false;
    }
    this->inactiveSkillImage = Variables::images->getByName("inactiveSkillButton");
    this->inactiveSkillImage->state = UI;
    this->activeSkillImage = Variables::images->getByName("activeSkillButton");
    this->activeSkillImage->state = UI;
    std::fstream file;
    file.open("fixtures/skills.txt");
    for(int attributeCount = 0; attributeCount < 4; attributeCount++)
    {
        for(int skillCount = 0; skillCount < 8; skillCount++)
        {
            file >> this->skillNames[attributeCount][skillCount];
        }
    }
    for(int i = 0; i < 4; i++)skilPointsAvaiilable[i] = 0;
}

Skills::Skills(const Skills& orig) {
}

Skills::~Skills() {
}

void Skills::display()
{
    Coordinates *coords = new Coordinates();
    coords->X = 25;
    coords->Y = 110;
    
    for(int attributeCount = 0; attributeCount < 4; attributeCount++)
    {
        for(int skillCount = 0; skillCount < 8; skillCount++)
        {
            if(this->isSkillActive(attributeCount, skillCount))activeSkillImage->display(coords);
            else inactiveSkillImage->display(coords);
            TextDisplayer::displayTextToLeft(coords->X, coords->Y+8, skillNames[attributeCount][skillCount]);
            coords->Y += 40;
        }
        coords->Y = 110;
        coords->X += 160;
    }
    delete coords;
}

void Skills::handleMouseAction()
{
    Coordinates *mouseCoords = new Coordinates();
    mouseCoords->X = Variables::mouseCoords->X;
    mouseCoords->Y = Variables::mouseCoords->Y;
    mouseCoords->width = 5;
    mouseCoords->height = 5;
    Coordinates *coords = new Coordinates();
    coords->X = 25;
    coords->Y = 110;
    coords->width = 120;
    coords->height = 30;
    
    for(int attributeCount = 0; attributeCount < 4; attributeCount++)
    {
        for(int skillCount = 0; skillCount < 8; skillCount++)
        {
            if(CollisionDetector::isBasicCollision(coords, mouseCoords))
            {
                if(skillActive[attributeCount][skillCount] == false)
                {
                    if(skilPointsAvaiilable[attributeCount] > 0)
                    {
                        this->skillActive[attributeCount][skillCount] = true;
                        skilPointsAvaiilable[attributeCount]--;
                    }
                }
                else if(Variables::skillRedistributionAviable)
                {
                    this->skillActive[attributeCount][skillCount] = !false;
                    skilPointsAvaiilable[attributeCount]++;
                }
            }
            coords->Y += 40;
        }
        coords->Y = 110;
        coords->X += 155;
    }
    delete coords;
}

void Skills::load(std::fstream& savefile)
{
    
}

void Skills::save(std::fstream& savefile)
{
    
}

bool Skills::isSkillActive(int attribute, int number)
{
    return this->skillActive[attribute][number];
}

void Skills::addSkillPoints(int attribute, int value)
{
    this->skilPointsAvaiilable[attribute] += value;
}