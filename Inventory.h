/* 
 * File:   Inventory.h
 * Author: Qb
 *
 * Created on 24 luty 2015, 20:27
 */

#ifndef INVENTORY_H
#define	INVENTORY_H
#include "Image.h"
#include "Coordinates.h"
#include "Button.h"

class Inventory {
public:
    Inventory();
    virtual ~Inventory();
    void display();
    void swapWeapons(bool inventory, int index);
    void storeEquipmentInChest(int chestFieldIndex, int inventoryFieldIndex);
    void storeInChest(int chestFieldIndex, int inventoryFieldIndex);
    void init();
    
    int getWeaponIndex();
    int getEquipmentIndex();
    void onMousePressed();
private:
    void clearImages();
    bool isCorrectEquipmentType(int chestIndex, int inventoryIndex);
    
    void displayWeapons();
    void displayEquipment();
    void displayAttributes();
    void displayStats();
    void displayAmmo();
    void displayTooltips();
    
    
    Image *backgroundImage;
    Coordinates *backgroundCoords;
    
    Image **weaponImages;
    Coordinates **weaponCoords;
    
    Image **equipmentImages;
    Coordinates **equipmentCoords;
    
    std::string *ammoNames;
    Button **buttons;
};

#endif	/* INVENTORY_H */

