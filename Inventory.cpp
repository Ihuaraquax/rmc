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
#include "TextDisplayer.h"
#include "EquipmentLoader.h"
#include "Skills.h"

Inventory::Inventory() {
    backgroundImage = Variables::images->getByName("inventroyBackground");
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
        equipmentCoords[i]->width = 100;
        equipmentCoords[i]->height = 100;
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
    
    buttons = new Button*[8];
    for(int i = 0; i < 8; i++)buttons[i] = new Button(i);
}

Inventory::~Inventory() {
    for(int i = 0; i < 8; i++)delete buttons[i];
    delete []buttons;
}

void Inventory::display()
{
    backgroundImage->display(backgroundCoords);
    displayWeapons();
    displayEquipment();
    displayAttributes();
    displayStats();
    displayAmmo();
    for(int i = 0; i < 8; i++)buttons[i]->display();
    dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->getSkills()->display();
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
    
    double X = 81;
    double Y = 50;
    
    TextDisplayer::displayInt(X, Y, player->attributes->getStrength());
    TextDisplayer::displayInt(X + 157 + 9, Y, player->attributes->getInteligence());
    TextDisplayer::displayInt(X + 320 + 9, Y, player->attributes->getAccuracy());
    TextDisplayer::displayInt(X + 480 + 9, Y, player->attributes->getSpeed());
    
    Y = 20;
    
    TextDisplayer::displayText(X, Y, "STRENGTH");
    TextDisplayer::displayText(X + 157 + 9, Y, "INTELLIGENCE");
    TextDisplayer::displayText(X + 320 + 9, Y, "ACCURACY");
    TextDisplayer::displayText(X + 480 + 9, Y, "SPEED");
}

void Inventory::displayStats()
{
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    double X = 717;
    double Y = 20;
    
    std::string resistsLabel[] = {"NORMAL", "FIRE", "ELECTRIC", "POISON", "COLD", "EXPLOSIVE"};
    TextDisplayer::displayText(X, Y, "HEALTH");
    Y += 20;
    TextDisplayer::displayInt(X, Y, player->getHealth());
    Y += 20;
    TextDisplayer::displayText(X, Y, "ARMOR");
    Y += 20;
    TextDisplayer::displayInt(X, Y, player->getArmor());
    Y += 20;
    TextDisplayer::displayText(X, Y, "EXPIRIENCE");
    Y += 20;
    TextDisplayer::displayInt(X, Y, player->getExpirience());
    Y += 40;
    TextDisplayer::displayText(X, Y, "RESISTS");
    Y += 20;
    for(int i = 0; i < Variables::damageTypeCount; i++)
    {
    
        Y += 20;
        TextDisplayer::displayText(X, Y, resistsLabel[i]);
        Y += 20;
        TextDisplayer::displayInt(X, Y, player->elementalResists[i] * 100);
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
        std::string path = player->weapons[i]->getDisplayPaths();
        weaponImages[i] = new Image(path, true);
        weaponImages[i]->state = UI;
    }
    std::string equipmentPaths = player->helmet->getImagePath();
    equipmentImages[0] = new Image(equipmentPaths, false);
    equipmentImages[0]->state = UI;
    
    equipmentPaths = player->chestplate->getImagePath();
    equipmentImages[1] = new Image(equipmentPaths, false);
    equipmentImages[1]->state = UI;
    
    equipmentPaths = player->greaves->getImagePath();
    equipmentImages[2] = new Image( equipmentPaths, false);
    equipmentImages[2]->state = UI;
    
    equipmentPaths = player->item->getImagePath();
    equipmentImages[3] = new Image(equipmentPaths, false);
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
    else if(firstWeaponIndex > 9)this->storeEquipmentInChest(secondWeaponIndex, firstWeaponIndex);
    else if(inventory)
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
        int secondWeaponId = Variables::session->getHud()->getOpenChest()->getContentValue(index);
        int weaponId = player->weapons[firstWeaponIndex]->getWeaponId();
        if(weaponId == -1)Variables::session->getHud()->getOpenChest()->loadContent(index, 0, -1);
        else Variables::session->getHud()->getOpenChest()->loadContent(index, 1, weaponId);
            
            
        WeaponLoader::loadWeapon(player->weapons[firstWeaponIndex], secondWeaponId);
    }
    this->init();
    Variables::session->getHud()->getMainWeaponUI()->reloadImage();
    Variables::session->getHud()->getSecondaryWeaponUI()->reloadImage();
}

int Inventory::getEquipmentIndex()
{
    int result = -1;
    Coordinates *mouseCoords = Variables::mouseCoords;
    for(int i = 0; i < 4; i++)
    {
        if(CollisionDetector::isBasicCollision(mouseCoords, equipmentCoords[i]))
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
    Coordinates *mouseCoords = Variables::mouseCoords;
    for(int i = 0; i < 6; i++)
    {
        if(CollisionDetector::isBasicCollision(mouseCoords, weaponCoords[i]))
        {
            result = i;
            break;
        }
    }
    if(result == -1)
    {
        for(int i = 0; i < 4; i++)
        {
            if(CollisionDetector::isBasicCollision(mouseCoords, equipmentCoords[i]))
            {
                result = i + 10;
                break;
            }
        }
    }
    return result;
}

void Inventory::storeInChest(int chestFieldIndex, int inventoryFieldIndex)
{
    if(inventoryFieldIndex > 9)storeEquipmentInChest(chestFieldIndex, inventoryFieldIndex);
    else
    {
        Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
        int chestWeaponType = Variables::session->getHud()->getOpenChest()->getContentValue(chestFieldIndex);
        int weaponId = player->weapons[inventoryFieldIndex]->getWeaponId();
        if(weaponId == -1)Variables::session->getHud()->getOpenChest()->loadContent(chestFieldIndex, 0, -1);
        else Variables::session->getHud()->getOpenChest()->loadContent(chestFieldIndex, 1, weaponId);
        WeaponLoader::loadWeapon(player->weapons[inventoryFieldIndex], chestWeaponType);
        init();
        Variables::session->getHud()->getMainWeaponUI()->reloadImage();
        Variables::session->getHud()->getSecondaryWeaponUI()->reloadImage();
    }
}

void Inventory::storeEquipmentInChest(int chestFieldIndex, int inventoryFieldIndex)
{
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    if(isCorrectEquipmentType(chestFieldIndex, inventoryFieldIndex))
    {
        inventoryFieldIndex -= 10;
        int chestEquipmentValue = Variables::session->getHud()->getOpenChest()->getContentValue(chestFieldIndex); 
        if(inventoryFieldIndex == 3)
        {
            int equipmentType = player->item->getAction();
            if(equipmentType == 0)Variables::session->getHud()->getOpenChest()->loadContent(chestFieldIndex, 0, -1);
            else Variables::session->getHud()->getOpenChest()->loadContent(chestFieldIndex, inventoryFieldIndex+2, equipmentType);
            player->changeItem(chestEquipmentValue);
        }
        else
        {
            Equipment *equipment = player->helmet;
            if(inventoryFieldIndex == 1)equipment = player->chestplate;
            if(inventoryFieldIndex == 2)equipment = player->greaves;
            int equipmentType = equipment->getAction();
            if(equipmentType == 0) Variables::session->getHud()->getOpenChest()->loadContent(chestFieldIndex, 0, -1);
            else Variables::session->getHud()->getOpenChest()->loadContent(chestFieldIndex, inventoryFieldIndex+2, equipmentType);
            EquipmentLoader::loadNewEquipment(equipment, chestEquipmentValue, equipment->getFilePath());
        }
        init();
        Variables::session->getHud()->getEquipmentUI()->reloadImages(player->helmet, player->chestplate, player->greaves, player->item);
    }
}

bool Inventory::isCorrectEquipmentType(int chestIndex, int inventoryIndex)
{
    bool result;
    if(inventoryIndex > 9)
    {
        result = (inventoryIndex-10) == Variables::session->getHud()->getOpenChest()->getContentType(chestIndex) - 2;
    } else {
        result = Variables::session->getHud()->getOpenChest()->getContentType(chestIndex) == 1;
    }
    result = result || Variables::session->getHud()->getOpenChest()->getContentType(chestIndex) == 0;
    return result;
}

void Inventory::onMousePressed()
{
    for(int i = 0; i < 8; i++)buttons[i]->execute();
    dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->getSkills()->handleMouseAction();
}