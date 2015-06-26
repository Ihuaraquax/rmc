/* 
 * File:   Tooltip.h
 * Author: Qb
 *
 * Created on 22 czerwiec 2015, 22:24
 */

#ifndef TOOLTIP_H
#define	TOOLTIP_H
#include <iostream>
#include "Coordinates.h"
#include "Image.h"

class Tooltip {
public:
    Tooltip();
    Tooltip(const Tooltip& orig);
    virtual ~Tooltip();
    void display();
    void displayWeaponTooltips();
    void displayEquipmentTooltips();
    void displaySkillTooltip();
    void displayAttributeTooltip();
    bool isDisplaing();
    void setImage(Image *image);
    void setBaseValues(int *values);
    void setCurrentValues(int *values);
    void calculateCoords();
    void setDisplay(bool Display);
    /**
     * 0 - Weapon
     * 1 - Equipment
     * 2 - Skill
     * 3 - Attribute
     * @param type
     */
    void setType(int type);
    void setName(std::string name);
private:
    Coordinates *coords;
    Image *image;
    std::string name;
    std::string **statName;
    int *baseValue;
    int *currentValue;
    std::string specialText;
    bool isDisplay;
    int type;
};

#endif	/* TOOLTIP_H */

