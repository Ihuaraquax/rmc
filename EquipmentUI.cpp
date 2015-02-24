/* 
 * File:   EquipmentUI.cpp
 * Author: Qb
 * 
 * Created on 16 luty 2015, 21:07
 */

#include "EquipmentUI.h"
#include "globalVariables.h"
#include "Equipment.h"
#include "UsableItem.h"

EquipmentUI::EquipmentUI() {
    selectedHelmet = NULL;
    selectedChestplate = NULL;
    selectedGreaves = NULL;
    selectedItem = NULL;
    
    helmetImage = NULL;
    chestplateImage = NULL;
    greavesImage = NULL;
    itemImage = NULL;
    
    helmetCoords = new Coordinates();
    helmetCoords->X = 150;
    helmetCoords->Y = Variables::RES_HEIGHT - 110;
    chestplateCoords = new Coordinates();
    chestplateCoords->X = 260;
    chestplateCoords->Y = Variables::RES_HEIGHT - 110;
    greavesCoords = new Coordinates();
    greavesCoords->X = 370;
    greavesCoords->Y = Variables::RES_HEIGHT - 110;
    itemCoords = new Coordinates();
    itemCoords->X = 480;
    itemCoords->Y = Variables::RES_HEIGHT - 110;
}

EquipmentUI::~EquipmentUI() {
    delete selectedHelmet;
    delete selectedChestplate;
    delete selectedGreaves;
    delete selectedItem;
    
    delete helmetImage;
    delete chestplateImage;
    delete greavesImage;
    delete itemImage;
    
    delete helmetCoords;
    delete chestplateCoords;
    delete greavesCoords;
    delete itemCoords;
}

void EquipmentUI::reloadImages(Equipment *helmet, Equipment *chestplate, Equipment *greaves, UsableItem *item)
{
    selectedHelmet = helmet;
    selectedChestplate = chestplate;
    selectedGreaves = greaves;
    selectedItem = item;
    
    if(helmetImage != NULL)delete helmetImage;
    if(chestplateImage != NULL)delete chestplateImage;
    if(greavesImage != NULL)delete greavesImage;
    if(itemImage != NULL)delete itemImage;
    
    std::string helmetPaths[] = {helmet->getImagePath()};
    std::string chestplatePaths[] = {chestplate->getImagePath()};
    std::string greavesPaths[] = {greaves->getImagePath()};
    std::string itemPaths[] = {item->getImagePath()};
    
    helmetImage = new Image(1, helmetPaths, false);
    chestplateImage = new Image(1, chestplatePaths, false);
    greavesImage = new Image(1, greavesPaths, false);
    itemImage = new Image(1, itemPaths, false);
}

void EquipmentUI::display()
{
    int energy =100 * selectedHelmet->getCurrentEnergy() / selectedHelmet->getMaxEnergy();
    if(selectedHelmet->isActive())al_draw_filled_rectangle(
            helmetCoords->X-5 - Variables::offsetX, 
            helmetCoords->Y-5 - Variables::offsetY, 
            helmetCoords->X + 105 - Variables::offsetX, 
            helmetCoords->Y + 105 - Variables::offsetY, 
            al_map_rgb(255,0,0));
    helmetImage->display(helmetCoords);
    al_draw_line(
            helmetCoords->X - 5 - Variables::offsetX,
            helmetCoords->Y + 105 - Variables::offsetY,
            helmetCoords->X + 5 + energy - Variables::offsetX,
            helmetCoords->Y + 105 - Variables::offsetY,
            al_map_rgb(70,70,255), 4);
    
    energy =100 * selectedChestplate->getCurrentEnergy() / selectedChestplate->getMaxEnergy();
    if(selectedChestplate->isActive())al_draw_filled_rectangle(
            chestplateCoords->X-5 - Variables::offsetX, 
            chestplateCoords->Y-5 - Variables::offsetY, 
            chestplateCoords->X + 105 - Variables::offsetX, 
            chestplateCoords->Y + 105 - Variables::offsetY, 
            al_map_rgb(255,0,0));
    chestplateImage->display(chestplateCoords);
    al_draw_line(
            chestplateCoords->X - 5 - Variables::offsetX,
            chestplateCoords->Y + 105 - Variables::offsetY,
            chestplateCoords->X + 5 + energy - Variables::offsetX,
            chestplateCoords->Y + 105 - Variables::offsetY,
            al_map_rgb(70,70,255), 4);
    
    energy =100 * selectedGreaves->getCurrentEnergy() / selectedGreaves->getMaxEnergy();
    if(selectedGreaves->isActive())al_draw_filled_rectangle(
            greavesCoords->X-5 - Variables::offsetX, 
            greavesCoords->Y-5 - Variables::offsetY, 
            greavesCoords->X + 105 - Variables::offsetX, 
            greavesCoords->Y + 105 - Variables::offsetY, 
            al_map_rgb(255,0,0));
    greavesImage->display(greavesCoords);
    al_draw_line(
            greavesCoords->X - 5 - Variables::offsetX,
            greavesCoords->Y + 105 - Variables::offsetY,
            greavesCoords->X + 5 + energy - Variables::offsetX,
            greavesCoords->Y + 105 - Variables::offsetY,
            al_map_rgb(70,70,255), 4);
    
    itemImage->display(itemCoords);    
    char chargesLeft[2];
    itoa(selectedItem->getCharges(), chargesLeft, 10);
    double X = itemCoords->X + 80 - Variables::offsetX;
    double Y = itemCoords->Y + 80 - Variables::offsetY;
    al_draw_text(Variables::basicFont, al_map_rgb(0,0,0), X, Y, ALLEGRO_ALIGN_CENTER, chargesLeft);
    
}

void EquipmentUI::update()
{
    helmetCoords->X = 150 + Variables::offsetX;
    helmetCoords->Y = Variables::RES_HEIGHT - 115 + Variables::offsetY;
    chestplateCoords->X = 260 + Variables::offsetX;
    chestplateCoords->Y = Variables::RES_HEIGHT - 115 + Variables::offsetY;
    greavesCoords->X = 370 + Variables::offsetX;
    greavesCoords->Y = Variables::RES_HEIGHT - 115 + Variables::offsetY;
    itemCoords->X = 480 + Variables::offsetX;
    itemCoords->Y = Variables::RES_HEIGHT - 110 + Variables::offsetY;
}