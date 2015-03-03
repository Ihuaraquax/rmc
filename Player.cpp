/* 
 * File:   Player.cpp
 * Author: Qb
 * 
 * Created on 16 grudzień 2014, 20:50
 */

#include "Player.h"
#include "globalVariables.h"
#include "ModuleTile.h"
#include "WeaponLoader.h"
#include "EquipmentUI.h"
#include "Helmet.h"
#include "Chestplate.h"
#include "Greaves.h"
#include "EquipmentLoader.h"
#include "UsableItemLoader.h"

Player::Player() {
    targetCoords = new Coordinates();
    this->threatLevel = 0;
    this->coords = new Coordinates();
    attributes = new Attributes();  
    helmet = new Helmet();
    chestplate = new Chestplate();
    item = new UsableItem();
    greaves = new Greaves();
    weapons = new Weapon*[6];
    ammo = new int[10];
    for(int i = 0; i < 10; i++)ammo[i] = 1000;
    for(int i = 0; i < 6; i++)
    {
        weapons[i] = new Weapon();
        weapons[i]->setPlayerIsWielder(true);
    }
    setTestValues();
}


Player::~Player() {
    delete helmet;
    delete chestplate;
    delete greaves;
    delete []ammo;
}

void Player::setTestValues()
{
    this->coords->X = 115;
    this->coords->Y = 115;
    this->coords->angle = 0;
    this->coords->height = 25;
    this->coords->width = 25;
    this->coords->speedX = 1;
    this->coords->speedY = 1;
    Variables::offsetX = coords->X -Variables::RES_WIDTH/2;
    Variables::offsetY = coords->Y -Variables::RES_HEIGHT/2;
    Variables::session->getMap()->getCurrentModule()->updateTileAiTarget
        (coords->X + coords->width/2, coords->Y + coords->height/2);
    std::string paths[] = {"images/player.png"};
    this->image = new Image(1, paths, true);
    this->image->state = NORMAL;
    health = 100;
    maximumHealth = health + 100;
    WeaponLoader::loadWeapon(weapons[0], 2);
    WeaponLoader::loadWeapon(weapons[1], 4);
    WeaponLoader::loadWeapon(weapons[2], 6);
    WeaponLoader::loadWeapon(weapons[3], 1);
    WeaponLoader::loadWeapon(weapons[4], 8);
    WeaponLoader::loadWeapon(weapons[5], 10);
    this->changeHelmet(7);
    this->changeChestplate(4);
    this->changeGreaves(5);
    this->changeItem(1);
    teamId = 1;
    possessedWeapons = 6;
    aiValue = 100;
    expirience = 0;
    Variables::session->getHud()->getMainWeaponUI()->selectWeapon(weapons[0]);
    Variables::session->getHud()->getSecondaryWeaponUI()->selectWeapon(weapons[1]);
    Variables::session->getHud()->getEquipmentUI()->reloadImages(helmet, chestplate, greaves, item);
    selecetedWeaponSet = 0;
    shoulderGun = new Weapon();
    WeaponLoader::loadWeapon(shoulderGun, 3);
}

void Player::playerMove(double X, double Y)
{
    move(X,Y);
    Variables::session->getMap()->getCurrentModule()->updateTileAiTarget
        (coords->X + coords->width/2, coords->Y + coords->height/2);
}

void Player::update()
{
    targetCoords->X = Variables::mouse_x;
    targetCoords->Y = Variables::mouse_y;
    coords->angle = Variables::getAngle(coords->X - Variables::offsetX, coords->Y - Variables::offsetY, targetCoords->X, targetCoords->Y);
    for(int i = 0; i < possessedWeapons; i++)weapons[i]->update();
    helmet->update();
    chestplate->update();
    greaves->update();
}

void Player::display()
{
    image->display(coords);
    al_draw_circle(Variables::mouse_x, Variables::mouse_y, weapons[selecetedWeaponSet*2 + 0]->getCurrentTargetSize(), al_map_rgb(255,0,0), 5);
    al_draw_circle(Variables::mouse_x, Variables::mouse_y, weapons[selecetedWeaponSet*2 + 1]->getCurrentTargetSize(), al_map_rgb(0,0,255), 3);
}

void Player::interact()
{
        Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->useObject();
}

void Player::selectWeaponSet(int set)
{
    this->selecetedWeaponSet = set;
    Variables::session->getHud()->getMainWeaponUI()->selectWeapon(weapons[set *2]);
    Variables::session->getHud()->getSecondaryWeaponUI()->selectWeapon(weapons[set * 2 + 1]);
}

int Player::getSelecetedWeaponSet() const {
    return selecetedWeaponSet;
}

Equipment* Player::getGreaves() const {
    return greaves;
}

Equipment* Player::getHelmet() const {
    return helmet;
}

Equipment* Player::getChestplate() const {
    return chestplate;
}

void Player::recalculateEquipmentBenefits()
{
    this->armor = helmet->getArmor() + chestplate->getArmor() + greaves->getArmor();
    for(int i = 0; i < Variables::damageTypeCount; i++)
        this->elementalResists[i] = helmet->getResistance(i) + chestplate->getResistance(i) + greaves->getResistance(i);
}

void Player::changeHelmet(int newHelmetIndex)
{
    EquipmentLoader::loadNewEquipment(helmet, newHelmetIndex, "fixtures/helmets.txt");
    recalculateEquipmentBenefits();
    Variables::session->getHud()->getEquipmentUI()->reloadImages(helmet, chestplate, greaves, item);
}

void Player::changeChestplate(int newChestplateIndex)
{
    EquipmentLoader::loadNewEquipment(chestplate, newChestplateIndex, "fixtures/chestplates.txt");
    recalculateEquipmentBenefits();
    Variables::session->getHud()->getEquipmentUI()->reloadImages(helmet, chestplate, greaves, item);
}

void Player::changeGreaves(int newGreavesIndex)
{
    EquipmentLoader::loadNewEquipment(greaves, newGreavesIndex, "fixtures/greaves.txt");
    recalculateEquipmentBenefits();
    Variables::session->getHud()->getEquipmentUI()->reloadImages(helmet, chestplate, greaves, item);
}

void Player::useEquipment(int equipmentIndex)
{
    if(equipmentIndex == 0)helmet->setActive(!helmet->isActive());
    if(equipmentIndex == 1)chestplate->setActive(!chestplate->isActive());
    if(equipmentIndex == 2)greaves->setActive(!greaves->isActive());
}

void Player::addExpirience(int exp)
{
    expirience += exp;
}

int Player::getExpirience() const {
    return expirience;
}

void Player::increaseAttribute(int attribute, int amount)
{
    switch(attribute)
    {
        case 0: this->attributes->addStrength(amount);
            break;
        case 1: this->attributes->addInteligence(amount);
            break;
        case 2: this->attributes->addAccuracy(amount);
            break;
        case 3: this->attributes->addSpeed(amount);
            break;
    }
}

void Player::recalculateCritical()
{
    this->criticalChance = this->attributes->getInteligence()/5;
    this->criticalDamage = this->attributes->getInteligence()/100;
}

void Player::recalculateAccuracy()
{ 
    this->accuracy = this->attributes->getAccuracy();
    this->accuracy /= 30;
    if(helmet->getAction() == 2)
    {
        this->accuracy += 2;
        if(helmet->isActive())this->accuracy += 3;
    }
}


void Player::useItem()
{
    item->activate();
    if(item->getCharges() <= 0)changeItem(0);
}

void Player::changeItem(int index)
{
    UsableItemLoader::loadItem(item, index);
    Variables::session->getHud()->getEquipmentUI()->reloadImages(helmet, chestplate, greaves, item);
}

void Player::addAmmo(int ammo, int index)
{
    this->ammo[index] += ammo;
    if(this->ammo[index] > 0)
    {
        for(int i = 0; i < 6; i++)if(weapons[i]->getAmmoType() == index)
            weapons[i]->setReloadable(true);
    }
}

int Player::getAmmo(int index)
{
    if(index == -1)return 0;
    else return ammo[index];
}

bool Player::isWeapon(int index)
{
    return weapons[index]->getWeaponId() != -1;
}