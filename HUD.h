/* 
 * File:   HUD.h
 * Author: Qb
 *
 * Created on 8 luty 2015, 00:10
 */

#ifndef HUD_H
#define	HUD_H
#include "Image.h"
#include "Coordinates.h"
#include "WeaponUI.h"
#include "EquipmentUI.h"
#include "Inventory.h"
#include "Chest.h"

class HUD {
public:
    HUD();
    virtual ~HUD();
    void update();
    void display();
    WeaponUI* getMainWeaponUI() const;
    WeaponUI* getSecondaryWeaponUI() const;
    EquipmentUI* getEquipmentUI() const;
    
    void setOpenChest(Chest* openChest);
    Chest* getOpenChest() const;
    void setPlayerInventory(Inventory* playerInventory);
    Inventory* getPlayerInventory() const;
    
    void mouseChestControls();
    void mouseInventoryControls();
private:
    void displaySelectedSet();
    void displayHealth();
    void displayArmor();
    void displayExpirience();
    
    Image *background;
    Coordinates *coords;
    WeaponUI *mainWeaponUI;
    WeaponUI *secondaryWeaponUI;
    EquipmentUI *equipmentUI;
    Inventory *playerInventory;    
    Chest *openChest;
    
    int contentIndex;
    bool isLeftButtonPressed;
    bool fromChest;
};

#endif	/* HUD_H */

