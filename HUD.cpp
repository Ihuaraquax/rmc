/* 
 * File:   HUD.cpp
 * Author: Qb
 * 
 * Created on 8 luty 2015, 00:10
 */

#include "HUD.h"
#include "globalVariables.h"
#include "WeaponUI.h"
#include "Player.h"
#include "EquipmentUI.h"
#include "Button.h"

HUD::HUD() {
    this->coords = new Coordinates();
    coords->X = 0;
    coords->Y = Variables::RES_HEIGHT - 120;
    std::string path = "images/HUDBackground.png";
    background = new Image( path, false);
    mainWeaponUI = new WeaponUI(true);
    secondaryWeaponUI = new WeaponUI(false);
    equipmentUI = new EquipmentUI();
    playerInventory = new Inventory();
    
    contentIndex = -1;
    isLeftButtonPressed = false;
    fromChest = false;
}


HUD::~HUD() {
    delete coords;
    delete background;
    delete equipmentUI;
    delete mainWeaponUI;
    delete secondaryWeaponUI;
}

void HUD::display()
{
    background->display(coords);
    mainWeaponUI->display();
    secondaryWeaponUI->display();
    displaySelectedSet();
    equipmentUI->display();
    displayHealth();
    displayExpirience();
    displayArmor();
}

WeaponUI* HUD::getMainWeaponUI() const {
   return mainWeaponUI;
}

WeaponUI* HUD::getSecondaryWeaponUI() const {
    return secondaryWeaponUI;
}

EquipmentUI* HUD::getEquipmentUI() const {
    return equipmentUI;
}

void HUD::setOpenChest(Chest* openChest) {
    this->openChest = openChest;
}

Chest* HUD::getOpenChest() const {
    return openChest;
}

void HUD::setPlayerInventory(Inventory* playerInventory) {
    this->playerInventory = playerInventory;
}

Inventory* HUD::getPlayerInventory() const {
    return playerInventory;
}

void HUD::update()
{
    coords->X = 0 + Variables::offsetX;
    coords->Y = Variables::RES_HEIGHT - 120 + Variables::offsetY;
    mainWeaponUI->update();
    secondaryWeaponUI->update();
    equipmentUI->update();
}


void HUD::displaySelectedSet()
{
    int X = 1024-403, Y = Variables::RES_HEIGHT - 115;
    int set = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->getSelecetedWeaponSet();
    if(set == 0)
    {
        al_draw_filled_rectangle(X, Y, X + 133, Y + 20, al_map_rgb(0,0,255));
    }
    else if(set == 1)
    {
        al_draw_filled_rectangle(X + 133, Y, X + 267, Y + 20, al_map_rgb(0,255,0));
    }
    else
    {
        al_draw_filled_rectangle(X + 267, Y, X + 400, Y + 20, al_map_rgb(255,0,0));
    }
}

void HUD::displayHealth()
{
    int playerHealth = Variables::session->getAllEntities()->getPlayer()->getHealth();
    char health[5], healthLabel[] = "health";
    itoa(playerHealth, health, 10);
    double X = 70;
    double Y = Variables::RES_HEIGHT - 90;
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y, ALLEGRO_ALIGN_CENTER, health);
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y - 15, ALLEGRO_ALIGN_CENTER, healthLabel);
}

void HUD::displayExpirience()
{
    int playerHealth = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->getExpirience();
    char expirience[4], expirienceLabel[] = "expirience";
    itoa(playerHealth, expirience, 10);
    double X = 70;
    double Y = Variables::RES_HEIGHT - 55;
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y, ALLEGRO_ALIGN_CENTER, expirience);
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y - 15, ALLEGRO_ALIGN_CENTER, expirienceLabel);
}

void HUD::displayArmor()
{
    int playerHealth = Variables::session->getAllEntities()->getPlayer()->getArmor();
    char armor[4], armorLabel[] = "armor";
    itoa(playerHealth, armor, 10);
    double X = 70;
    double Y = Variables::RES_HEIGHT - 20;
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y, ALLEGRO_ALIGN_CENTER, armor);
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y - 15, ALLEGRO_ALIGN_CENTER, armorLabel);
}

void HUD::mouseChestControls()
{
     int inventoryIndex = Variables::session->getHud()->getPlayerInventory()->getWeaponIndex();
     int chestIndex = Variables::session->getHud()->getOpenChest()->getSelectedField();
     if(Variables::mouse_state.buttons & 1)
     {
         if(!isLeftButtonPressed)if(contentIndex == -1)
         {
             if(inventoryIndex != -1)
             {
                 contentIndex = inventoryIndex;
                 if(inventoryIndex < 9)if(!dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->isWeapon(contentIndex))contentIndex = -1;
                 fromChest = false;
             }
             else
             {
                 contentIndex = chestIndex;
                 if(!Variables::session->getHud()->getOpenChest()->isFieldNotEmpty(contentIndex))contentIndex = -1;
                 fromChest = true;
             }
         }
         isLeftButtonPressed = true;
     } else
     {
         if(isLeftButtonPressed)if(contentIndex != -1) 
         {
             if(fromChest && inventoryIndex != -1)
             {
                 Variables::session->getHud()->getPlayerInventory()->swapWeapons(false, contentIndex);
                 contentIndex = -1;
             }
             if(fromChest && chestIndex != -1 && chestIndex != contentIndex)
             {
                 Variables::session->getHud()->getOpenChest()->swapContent(chestIndex, contentIndex);
                 contentIndex = -1;
             }
             if(!fromChest && inventoryIndex != -1 && inventoryIndex != contentIndex)
             {
                Variables::session->getHud()->getPlayerInventory()->swapWeapons(true, contentIndex);
                contentIndex = -1;
             }
             if(!fromChest && chestIndex != -1)
             {
                 Variables::session->getHud()->getPlayerInventory()->storeInChest(chestIndex, contentIndex);
                 contentIndex = -1;
             }
         }             
         isLeftButtonPressed = false;
     } 
}

void HUD::mouseInventoryControls()
{
     int inventoryIndex = Variables::session->getHud()->getPlayerInventory()->getWeaponIndex();
     if(Variables::mouse_state.buttons & 1)
     {
         if(!isLeftButtonPressed)if(contentIndex == -1)
         {
             contentIndex = inventoryIndex;
             if(!dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->isWeapon(contentIndex))contentIndex = -1;
         }
         isLeftButtonPressed = true;
     } else
     {
         if(isLeftButtonPressed)if(contentIndex != -1) 
         {
             if(inventoryIndex != -1 && inventoryIndex != contentIndex)
             {
                 Variables::session->getHud()->getPlayerInventory()->swapWeapons(true, contentIndex);
                 contentIndex = -1;
             }
         }
         isLeftButtonPressed = false;    
     }
}
