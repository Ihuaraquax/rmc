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

class Inventory {
public:
    Inventory();
    virtual ~Inventory();
    void display();
    void swapWeapons(bool inventory, int index);
    void swapEquipment(bool inventory, int index);
    void storeInChest(int chestFieldIndex, int inventoryFieldIndex);
    void init();
    
    int getWeaponIndex();
    int getEquipmentIndex();
private:
    void clearImages();
    
    void displayWeapons();
    void displayEquipment();
    void displayAttributes();
    void displayStats();
    void displayAmmo();
    
    
    Image *backgroundImage;
    Coordinates *backgroundCoords;
    
    Image **weaponImages;
    Coordinates **weaponCoords;
    
    Image **equipmentImages;
    Coordinates **equipmentCoords;
    
    std::string *ammoNames;
};

#endif	/* INVENTORY_H */

