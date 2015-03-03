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
#include "WeaponLoader.h"
#include "CollisionDetector.h"

Inventory::Inventory() {
    std::string paths[] = {"images/inventoryBackground.png"};
    backgroundImage = new Image(1, paths, false);
    backgroundImage->state = UI;
    backgroundCoords = new Coordinates();
    backgroundCoords->X = 0;
    backgroundCoords->Y = -17;
    
    weaponCoords = new Coordinates*[6];
    for(int i = 0; i <6; i++)
    {
        weaponCoords[i] = new Coordinates();
        weaponCoords[i]->X = 29 + 210*(i/2);
        weaponCoords[i]->Y = 575 + 90*(i%2);
        weaponCoords[i]->width = 200;
        weaponCoords[i]->height = 90;
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
        equipmentCoords[i]->X = 63 + 140*i;
        equipmentCoords[i]->Y = 455;
    }
    equipmentImages = new Image*[4];
    
    for(int i = 0; i < 4; i++)
    {
        equipmentImages[i]  = NULL;
    }
    
    ammoNames = new std::string[10];
    ammoNames[0] = "PIST";
    ammoNames[1] = "SMG";
    ammoNames[2] = ".50";
    ammoNames[3] = "12G";
    ammoNames[4] = "RIFLE";
    ammoNames[5] = "GRND";
    ammoNames[6] = "RKET";
    ammoNames[7] = "ENRG";
    ammoNames[8] = "HEAVY";
    ammoNames[9] = "HCG";
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
    displayAmmo();
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
    double X = 81;
    double Y = 50;
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y, ALLEGRO_ALIGN_CENTER, strength);
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X + 157 + 9, Y, ALLEGRO_ALIGN_CENTER, intelligence);
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X + 320 + 9, Y, ALLEGRO_ALIGN_CENTER, accuracy);
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X + 480 + 9, Y, ALLEGRO_ALIGN_CENTER, speed);
    
    Y = 20;
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X, Y, ALLEGRO_ALIGN_CENTER, strengthLabel);
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X + 157 + 9, Y, ALLEGRO_ALIGN_CENTER, intelligenceLabel);
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X + 320 + 9, Y, ALLEGRO_ALIGN_CENTER, accuracyLabel);
    al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X + 480 + 9, Y, ALLEGRO_ALIGN_CENTER, speedLabel);
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
    double X = 717;
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
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    double X = 717;
    double Y = 450;
    char label[20];
    for(int i = 0; i < 10 ; i++)
    {
        char ammo[5];
        strcpy(label, ammoNames[i].c_str());
        itoa(player->getAmmo(i), ammo, 10);
        al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X-55, Y, ALLEGRO_ALIGN_LEFT, label);
        al_draw_text(Variables::basicFont, al_map_rgb(255,255,255), X+60, Y, ALLEGRO_ALIGN_RIGHT, ammo);
        Y += 32;
    }
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

void Inventory::swapWeapons(bool inventory, int index)
{
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    int firstWeaponIndex = this->getWeaponIndex();
    int secondWeaponIndex = index;
    if(firstWeaponIndex == -1)return;
    if(inventory)
    {
        int firstWeaponAmmo = player->weapons[firstWeaponIndex]->getAmmoCurrent();
        int secondWeaponAmmo = player->weapons[secondWeaponIndex]->getAmmoCurrent();
        int secondWeaponId = player->weapons[secondWeaponIndex]->getWeaponId();
        WeaponLoader::loadWeapon(player->weapons[secondWeaponIndex], player->weapons[firstWeaponIndex]->getWeaponId());
        WeaponLoader::loadWeapon(player->weapons[firstWeaponIndex], secondWeaponId);
        player->weapons[firstWeaponIndex]->setAmmoCurrent(secondWeaponAmmo);
        player->weapons[secondWeaponIndex]->setAmmoCurrent(firstWeaponAmmo);
    } else {
        int firstWeaponAmmo = player->weapons[firstWeaponIndex]->getAmmoCurrent();
        player->addAmmo(firstWeaponAmmo, player->weapons[firstWeaponIndex]->getAmmoType());
        int secondWeaponId = Variables::session->getOpenChest()->getContentValue(index);
        Variables::session->getOpenChest()->loadContent(index, 1, player->weapons[firstWeaponIndex]->getWeaponId());
        WeaponLoader::loadWeapon(player->weapons[firstWeaponIndex], secondWeaponId);
    }
    this->init();
    Variables::session->getHud()->getMainWeaponUI()->reloadImage();
    Variables::session->getHud()->getSecondaryWeaponUI()->reloadImage();
}

void Inventory::swapEquipment(bool inventory, int index)
{
    
}

int Inventory::getEquipmentIndex()
{
    int result = -1;
    Coordinates *mouseCoords = new Coordinates();
    mouseCoords->X = Variables::mouse_x;
    mouseCoords->Y = Variables::mouse_y;
    for(int i = 0; i < 4; i++)
    {
        if(CollisionDetector::isCollision(mouseCoords, equipmentCoords[i]))
        {
            result = i;
            break;
        }
    }
    return result;
}

int Inventory::getWeaponIndex()
{
    int result = -1;
    Coordinates *mouseCoords = new Coordinates();
    mouseCoords->X = Variables::mouse_x;
    mouseCoords->Y = Variables::mouse_y;
    mouseCoords->width = 1;
    mouseCoords->height = 1;
    for(int i = 0; i < 6; i++)
    {
        if(CollisionDetector::isCollision(mouseCoords, weaponCoords[i]))
        {
            result = i;
            break;
        }
    }
    return result;
}

void Inventory::storeInChest(int chestFieldIndex, int inventoryFieldIndex)
{
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    int chestWeaponType = Variables::session->getOpenChest()->getContentValue(chestFieldIndex);
    Variables::session->getOpenChest()->loadContent(chestFieldIndex, 1, player->weapons[inventoryFieldIndex]->getWeaponId());
    WeaponLoader::loadWeapon(player->weapons[inventoryFieldIndex], chestWeaponType);
    init();
    Variables::session->getHud()->getMainWeaponUI()->reloadImage();
    Variables::session->getHud()->getSecondaryWeaponUI()->reloadImage();
}