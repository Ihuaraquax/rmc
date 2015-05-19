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
#include "TextDisplayer.h"

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
    
    std::string helmetPaths = helmet->getImagePath();
    std::string chestplatePaths = chestplate->getImagePath();
    std::string greavesPaths = greaves->getImagePath();
    std::string itemPaths = item->getImagePath();
    
    helmetImage = new Image(helmetPaths, false);
    chestplateImage = new Image(chestplatePaths, false);
    greavesImage = new Image(greavesPaths, false);
    itemImage = new Image(itemPaths, false);
    
    helmetImage->state = UI;
    chestplateImage->state = UI;
    greavesImage->state = UI;
    itemImage->state = UI;
}

void EquipmentUI::display()
{
    int energy =100 * selectedHelmet->getCurrentEnergy() / selectedHelmet->getMaxEnergy();
    if(selectedHelmet->isActive())al_draw_filled_rectangle(
            helmetCoords->X-5, 
            helmetCoords->Y-5, 
            helmetCoords->X + 105, 
            helmetCoords->Y + 105, 
            al_map_rgb(255,0,0));
    helmetImage->display(helmetCoords);
    al_draw_line(
            helmetCoords->X - 5,
            helmetCoords->Y + 105,
            helmetCoords->X + 5 + energy,
            helmetCoords->Y + 105,
            al_map_rgb(70,70,255), 4);
    
    energy =100 * selectedChestplate->getCurrentEnergy() / selectedChestplate->getMaxEnergy();
    if(selectedChestplate->isActive())al_draw_filled_rectangle(
            chestplateCoords->X-5, 
            chestplateCoords->Y-5, 
            chestplateCoords->X + 105, 
            chestplateCoords->Y + 105, 
            al_map_rgb(255,0,0));
    chestplateImage->display(chestplateCoords);
    al_draw_line(
            chestplateCoords->X - 5,
            chestplateCoords->Y + 105,
            chestplateCoords->X + 5 + energy,
            chestplateCoords->Y + 105,
            al_map_rgb(70,70,255), 4);
    
    energy =100 * selectedGreaves->getCurrentEnergy() / selectedGreaves->getMaxEnergy();
    if(selectedGreaves->isActive())al_draw_filled_rectangle(
            greavesCoords->X-5, 
            greavesCoords->Y-5, 
            greavesCoords->X + 105, 
            greavesCoords->Y + 105, 
            al_map_rgb(255,0,0));
    greavesImage->display(greavesCoords);
    al_draw_line(
            greavesCoords->X - 5,
            greavesCoords->Y + 105,
            greavesCoords->X + 5 + energy,
            greavesCoords->Y + 105,
            al_map_rgb(70,70,255), 4);
    
    itemImage->display(itemCoords);    
    TextDisplayer::displayInt(itemCoords->X + 80, itemCoords->Y + 80, selectedItem->getCharges());    
}

void EquipmentUI::update()
{
}