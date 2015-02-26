/* 
 * File:   Inventory.cpp
 * Author: Qb
 * 
 * Created on 24 luty 2015, 20:27
 */

#include "Inventory.h"
#include <iostream>
#include "Player.h"
#include "globalVariables.h"

Inventory::Inventory() {
    std::string paths[] = {"images/inventoryBackground.png"};
    backgroundImage = new Image(1, paths, false);
    backgroundImage->state = UI;
    backgroundCoords = new Coordinates();
    backgroundCoords->X = -17;
    backgroundCoords->Y = -17;
    
    weaponCoords = new Coordinates*[6];
    for(int i = 0; i <6; i++)
    {
        weaponCoords[i] = new Coordinates();
        weaponCoords[i]->X = 12 + 210*(i/2);
        weaponCoords[i]->Y = 575 + 90*(i%2);
    }
    weaponImages = new Image*[6];
    
    for(int i = 0; i < 6; i++)
    {
        weaponImages[i]  = NULL;
    }
    
    equipmentCoords = new Coordinates*[4];
    for(int i = 0; i <4; i++)
    {
        equipmentCoords[i] = new Coordinates();
        equipmentCoords[i]->X = 46 + 140*i;
        equipmentCoords[i]->Y = 455;
    }
    equipmentImages = new Image*[4];
    
    for(int i = 0; i < 4; i++)
    {
        equipmentImages[i]  = NULL;
    }
}

Inventory::~Inventory() {
}

void Inventory::display()
{
    backgroundImage->display(backgroundCoords);
    displayWeapons();
    displayEquipment();
    displayAttributes();
    displayStats();
}

void Inventory::displayWeapons()
{
    for(int i = 0; i < 6; i++)
    {
        weaponImages[i]->display(weaponCoords[i]);
    }
}

void Inventory::displayEquipment()
{
    for(int i = 0; i < 4; i++)
    {
        equipmentImages[i]->display(equipmentCoords[i]);
    }
}
void Inventory::displayAttributes()
{
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    char strength[3], intelligence[3], accuracy[3], speed[3];
    char strengthLabel[] = "STRENGTH", intelligenceLabel[] = "INTELLIGENCE", accuracyLabel[] = "ACCURACY", speedLabel[] = "SPEED";
    itoa(player->attributes->getStrength(), strength, 10);
    itoa(player->attributes->getInteligence(), intelligence, 10);
    itoa(player->attributes->getAccuracy(), accuracy, 10);
    itoa(player->attributes->getSpeed(), speed, 10);
    double X = 74;
    double Y = 50;
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y, ALLEGRO_ALIGN_CENTER, strength);
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X + 157, Y, ALLEGRO_ALIGN_CENTER, intelligence);
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X + 320, Y, ALLEGRO_ALIGN_CENTER, accuracy);
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X + 480, Y, ALLEGRO_ALIGN_CENTER, speed);
    
    Y = 20;
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y, ALLEGRO_ALIGN_CENTER, strengthLabel);
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X + 157, Y, ALLEGRO_ALIGN_CENTER, intelligenceLabel);
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X + 320, Y, ALLEGRO_ALIGN_CENTER, accuracyLabel);
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X + 480, Y, ALLEGRO_ALIGN_CENTER, speedLabel);
}

void Inventory::displayStats()
{
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    char health[4], armor[4], expirience[5], resistance[Variables::damageTypeCount][3];
    char healthLabel[] = "HEALTH", armorLabel[] = "ARMOR", expirienceLabel[] = "EXPIRIENCE";
    std::string resistsLabel[] = {"RESISTS", "NORMAL", "FIRE", "ELECTRIC", "POISON", "COLD", "EXPLOSIVE"};
    itoa(player->getHealth(), health, 10);
    itoa(player->getArmor(), armor, 10);
    itoa(player->getExpirience(), expirience, 10);
    for(int i = 0 ; i < Variables::damageTypeCount; i++)
    {
        int resistPercentage = ceil(player->elementalResists[i] * 100);
        itoa(resistPercentage, resistance[i], 10);
    }
    double X = 700;
    double Y = 20;
    
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y, ALLEGRO_ALIGN_CENTER, healthLabel);
    Y += 20;
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y, ALLEGRO_ALIGN_CENTER, health);
    Y += 20;
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y, ALLEGRO_ALIGN_CENTER, armorLabel);
    Y += 20;
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y, ALLEGRO_ALIGN_CENTER, armor);
    Y += 20;
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y, ALLEGRO_ALIGN_CENTER, expirienceLabel);
    Y += 20;
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y, ALLEGRO_ALIGN_CENTER, expirience);
    Y += 40;
    char label[20];
    strcpy(label, resistsLabel[0].c_str());
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y, ALLEGRO_ALIGN_CENTER, label);
    Y += 20;
    for(int i = 0; i < Variables::damageTypeCount; i++)
    {
        Y += 20;
        strcpy(label, resistsLabel[i+1].c_str());
        al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y, ALLEGRO_ALIGN_CENTER, label);
        Y += 20;
        al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y, ALLEGRO_ALIGN_CENTER, resistance[i]);
    }
}

void Inventory::displayAmmo()
{
    // NOT YET IMPLEMENTED
}

void Inventory::init()
{
    clearImages();
    
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());    
    for(int i = 0; i < 6; i++)
    {
        std::string paths[] = {player->weapons[i]->getDisplayPaths()};
        weaponImages[i] = new Image(1, paths, true);
        weaponImages[i]->state = UI;
    }
    std::string equipmentPaths[] = {player->helmet->getImagePath()};
    equipmentImages[0] = new Image(1, equipmentPaths, false);
    equipmentImages[0]->state = UI;
    
    equipmentPaths[0] = player->chestplate->getImagePath();
    equipmentImages[1] = new Image(1, equipmentPaths, false);
    equipmentImages[1]->state = UI;
    
    equipmentPaths[0] = player->greaves->getImagePath();
    equipmentImages[2] = new Image(1, equipmentPaths, false);
    equipmentImages[2]->state = UI;
    
    equipmentPaths[0] = player->item->getImagePath();
    equipmentImages[3] = new Image(1, equipmentPaths, false);
    equipmentImages[3]->state = UI;
}

void Inventory::clearImages()
{
    for(int i = 0; i < 6; i++)
    {
        if(weaponImages[i] != NULL)delete weaponImages[i];
    }
    for(int i = 0; i < 4; i++)
    {
        if(equipmentImages[i] != NULL)delete equipmentImages[i];
    }
}