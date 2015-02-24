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
#include "UsableItem.h"

class EquipmentUI {
public:
    EquipmentUI();
    virtual ~EquipmentUI();
    void update();
    void display();
    void reloadImages(Equipment *helmet, Equipment *chestplate, Equipment *greaves, UsableItem *item);
private:
    Equipment *selectedHelmet;
    Equipment *selectedChestplate;
    Equipment *selectedGreaves;
    UsableItem *selectedItem;
    
    Image *helmetImage;
    Image *chestplateImage;
    Image *greavesImage;
    Image *itemImage;
    
    Coordinates *helmetCoords;
    Coordinates *chestplateCoords;
    Coordinates *greavesCoords;
    Coordinates *itemCoords;
};

#endif	/* EQUIPMENTUI_H */

