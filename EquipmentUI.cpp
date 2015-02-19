/* 
 * File:   EquipmentUI.cpp
 * Author: Qb
 * 
 * Created on 16 luty 2015, 21:07
 */

#include "EquipmentUI.h"
#include "globalVariables.h"
#include "Equipment.h"

EquipmentUI::EquipmentUI() {
    selectedHelmet = NULL;
    selectedChestplate = NULL;
    selectedGreaves = NULL;
    
    helmetImage = NULL;
    chestplateImage = NULL;
    greavesImage = NULL;
    
    helmetCoords = new Coordinates();
    helmetCoords->X = 150;
    helmetCoords->Y = Variables::RES_HEIGHT - 110;
    chestplateCoords = new Coordinates();
    chestplateCoords->X = 275;
    chestplateCoords->Y = Variables::RES_HEIGHT - 110;
    greavesCoords = new Coordinates();
    greavesCoords->X = 400;
    greavesCoords->Y = Variables::RES_HEIGHT - 110;
}

EquipmentUI::~EquipmentUI() {
    delete selectedHelmet;
    delete selectedChestplate;
    delete selectedGreaves;
    
    delete helmetImage;
    delete chestplateImage;
    delete greavesImage;
    
    delete helmetCoords;
    delete chestplateCoords;
    delete greavesCoords;
}

void EquipmentUI::reloadImages(Equipment *helmet, Equipment *chestplate, Equipment *greaves)
{
    selectedHelmet = helmet;
    selectedChestplate = chestplate;
    selectedGreaves = greaves;
    
    if(helmetImage != NULL)delete helmetImage;
    if(chestplateImage != NULL)delete chestplateImage;
    if(greavesImage != NULL)delete greavesImage;
    
    std::string helmetPaths[] = {helmet->getImagePath()};
    std::string chestplatePaths[] = {chestplate->getImagePath()};
    std::string greavesPaths[] = {greaves->getImagePath()};
    
    helmetImage = new Image(1, helmetPaths, false);
    chestplateImage = new Image(1, chestplatePaths, false);
    greavesImage = new Image(1, greavesPaths, false);
}

void EquipmentUI::display()
{
    if(selectedHelmet->isActive())al_draw_filled_rectangle(helmetCoords->X-5, helmetCoords->Y-5, helmetCoords->X + 105, helmetCoords->Y + 105, al_map_rgb(255,0,0));
    helmetImage->display(helmetCoords);
    if(selectedChestplate->isActive())al_draw_filled_rectangle(chestplateCoords->X-5, chestplateCoords->Y-5, chestplateCoords->X + 105, chestplateCoords->Y + 105, al_map_rgb(255,0,0));
    chestplateImage->display(chestplateCoords);
    if(selectedGreaves->isActive())al_draw_filled_rectangle(greavesCoords->X-5, greavesCoords->Y-5, greavesCoords->X + 105, greavesCoords->Y + 105, al_map_rgb(255,0,0));
    greavesImage->display(greavesCoords);
}

void EquipmentUI::update()
{
    helmetCoords->X = 150 + Variables::offsetX;
    helmetCoords->Y = Variables::RES_HEIGHT - 110 + Variables::offsetY;
    chestplateCoords->X = 275 + Variables::offsetX;
    chestplateCoords->Y = Variables::RES_HEIGHT - 110 + Variables::offsetY;
    greavesCoords->X = 400 + Variables::offsetX;
    greavesCoords->Y = Variables::RES_HEIGHT - 110 + Variables::offsetY;
}