/* 
 * File:   EquipmentUI.h
 * Author: Qb
 *
 * Created on 16 luty 2015, 21:07
 */

#ifndef EQUIPMENTUI_H
#define	EQUIPMENTUI_H
#include "Image.h"
#include "Coordinates.h"
#include "Equipment.h"

class EquipmentUI {
public:
    EquipmentUI();
    virtual ~EquipmentUI();
    void update();
    void display();
    void reloadImages(Equipment *helmet, Equipment *chestplate, Equipment *greaves);
private:
    Equipment *selectedHelmet;
    Equipment *selectedChestplate;
    Equipment *selectedGreaves;
    
    Image *helmetImage;
    Image *chestplateImage;
    Image *greavesImage;
    
    Coordinates *helmetCoords;
    Coordinates *chestplateCoords;
    Coordinates *greavesCoords;
};

#endif	/* EQUIPMENTUI_H */

