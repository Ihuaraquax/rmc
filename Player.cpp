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
#include "TimedBuffer.h"
#include "CollisionDetector.h"

Player::Player() {
    keyValue = -1;
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
    bleeds = true;
    setTestValues();
    this->animation = new Animation();
    animation->setAnimation("images/walking2.png", 88, 98);
    this->animation->setDuration(1);
}

Player::Player(bool isLoad)
{
    std::string path = "images/player.png";
    this->image = new Image(path, true);
    this->image->state = NORMAL;
    targetCoords = new Coordinates();
    this->threatLevel = 0;
    this->coords = new Coordinates();
    this->coords->width = 25;
    this->coords->height = 25;
    this->coords->speedX = 1.5;
    this->coords->speedY = 1.5;
    attributes = new Attributes();  
    helmet = new Helmet();
    chestplate = new Chestplate();
    item = new UsableItem();
    greaves = new Greaves();
    ammo = new int[10];
    weapons = new Weapon*[6];
    for(int i = 0; i < 6; i++)
    {
        weapons[i] = new Weapon();
        weapons[i]->setPlayerIsWielder(true);
    }
    bleeds = true;
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
    this->coords->speedX = 1.5;
    this->coords->speedY = 1.5;
    Variables::offsetX = (coords->X * Variables::ScaleX * Variables::scale) -Variables::RES_WIDTH/2;
    Variables::offsetY = (coords->Y * Variables::ScaleY * Variables::scale) -Variables::RES_HEIGHT/2;
    Variables::session->getMap()->getCurrentModule()->updateTileAiTarget
        (coords->X + coords->width/2, coords->Y + coords->height/2);
    std::string path = "images/player.png";
    this->image = new Image(path, true);
    this->image->state = NORMAL;
    health = 10000;
    maximumHealth = health + 100;
    WeaponLoader::loadWeapon(weapons[0], 0);
    WeaponLoader::loadWeapon(weapons[1], 16);
    WeaponLoader::loadWeapon(weapons[2], 17);
    WeaponLoader::loadWeapon(weapons[3], 18);
    WeaponLoader::loadWeapon(weapons[4], 19);
    WeaponLoader::loadWeapon(weapons[5], 20);
    this->changeHelmet(6);
    this->changeChestplate(0);
    this->changeGreaves(0);
    this->changeItem(3);
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
    this->setStartingTile();
}

void Player::playerMove(double X, double Y)
{
    move(X,Y);
    Variables::session->getMap()->getCurrentModule()->updateTileAiTarget(coords->X + coords->width/2, coords->Y + coords->height/2);
    int side = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->getTransferDirection();
    if(side != -1)
    {
        this->setTransferCoords(side);
        Variables::session->getMap()->switchModule(side);
    }
}

void Player::update()
{    
    if(Variables::log == full)std::cout << " player Update Begin ";
    double X = (coords->X + coords->width/2 - Variables::offsetX) * Variables::ScaleX * Variables::scale;
    double Y = (coords->Y + coords->height/2 - Variables::offsetY) * Variables::ScaleY * Variables::scale;
    targetCoords->X = Variables::mouse_x * ((1/Variables::ScaleX * Variables::scale));
    targetCoords->Y = Variables::mouse_y * ((1/Variables::ScaleY * Variables::scale));
    coords->angle = Variables::getAngle(X, Y, targetCoords->X, targetCoords->Y);
    for(int i = 0; i < possessedWeapons; i++)weapons[i]->update();
    helmet->update();
    chestplate->update();
    greaves->update();
    this->updateBuffers();
    updatePlanStep();
    updatePickUps();
    if(Variables::log == full)std::cout << " player Update End ";
}

void Player::updatePlanStep()
{
    if(Variables::session->getAllPlans()->getCurrentPlan()->getCurrentStep() != NULL)
    {
        Coordinates *tempCoords = new Coordinates();
        PlanStep *step = Variables::session->getAllPlans()->getCurrentPlan()->getCurrentStep();
        tempCoords->X = step->getCoords()->X - (step->getModuleX() * Variables::tileSize * Variables::tilesPerRoom);
        tempCoords->Y = step->getCoords()->Y - (step->getModuleY() * Variables::tileSize * Variables::tilesPerRoom);
        tempCoords->width = step->getCoords()->width;
        tempCoords->height = step->getCoords()->height;
        if(CollisionDetector::isBasicCollision(coords, tempCoords))
            Variables::session->getAllPlans()->getCurrentPlan()->changeCurrentStep(true);
    }
}

void Player::display()
{
//    image->display(coords);
    animation->display(coords);
    al_draw_circle(Variables::mouse_x, Variables::mouse_y, weapons[selecetedWeaponSet*2 + 0]->getCurrentTargetSize() * Variables::scale, al_map_rgb(255,0,0), 5);
    al_draw_circle(Variables::mouse_x, Variables::mouse_y, weapons[selecetedWeaponSet*2 + 1]->getCurrentTargetSize() * Variables::scale, al_map_rgb(0,0,255), 3);
//    this->displayIsInBuffRange();
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
    if(index == -1)return false;
    return weapons[index]->getWeaponId() != -1;
}

void Player::displayIsInBuffRange()
{
    double X = (coords->X + coords->width/2 - Variables::offsetX) * Variables::ScaleX * Variables::scale;
    double Y = (coords->Y + coords->height/2 - Variables::offsetY) * Variables::ScaleY * Variables::scale;
    if(this->getValueOfBuffer(0) > 0)al_draw_circle(X, Y, 5, al_map_rgb(0,255,0), 3);
    else al_draw_circle(X, Y, 5, al_map_rgb(255,0,0), 3);
}

void Player::save(std::fstream& file)
{
    file << "PL" << std::endl;
    saveGeneric(file);
    file << ' ' << expirience << ' ' << selecetedWeaponSet << ' ' << keyValue << ' ';
    for(int i = 0; i < 10; i++)file << ammo[i] << ' ';
    attributes->save(file);
    this->helmet->save(file);
    this->chestplate->save(file);
    this->greaves->save(file);
    this->item->save(file);
    file << std::endl;
}


void Player::load(std::fstream& file)
{
    loadGeneric(file);
    file >> expirience >> selecetedWeaponSet >> keyValue;
    for(int i = 0; i < 10; i++)file >> ammo[i];
    attributes->load(file);
    this->helmet->load(file);
    this->chestplate->load(file);
    this->greaves->load(file);
    this->item->load(file);
    Variables::session->getHud()->getMainWeaponUI()->selectWeapon(weapons[0]);
    Variables::session->getHud()->getSecondaryWeaponUI()->selectWeapon(weapons[1]);
    Variables::session->getHud()->getEquipmentUI()->reloadImages(helmet, chestplate, greaves, item);
    Variables::session->getMap()->getCurrentModule()->updateTileAiTarget
        (coords->X + coords->width/2, coords->Y + coords->height/2);
}

void Player::loadGeneric(std::fstream& file)
{
    file >> health >> coords->X >> coords->Y >> coords->angle >> coords->speedX >> coords->speedY >> maximumHealth  >> aiValue >> criticalChance  >>  criticalDamage;
    file >> teamId >> threatLevel;
    for(int i = 0; i < Variables::damageTypeCount; i++)file >> elementalResists[i];
    int bleedsValue;
    file >> bleedsValue;
    if(bleedsValue = 1)bleeds = true;
    else bleeds = false;
    file >> possessedWeapons;
    int weaponIds[possessedWeapons];
    int weaponsAmmos[possessedWeapons];
    for(int i = 0; i < possessedWeapons; i++)
    {
        file >> weaponIds[i] >> weaponsAmmos[i];
        WeaponLoader::loadWeapon(weapons[i], weaponIds[i]);
        weapons[i]->setAmmoCurrent(weaponsAmmos[i]);
    }
}

void Player::setKeyValue(int keyValue) {
    this->keyValue = keyValue;
}

int Player::getKeyValue() const {
    return keyValue;
}

void Player::setTransferCoords(int side)
{
    double totalSize = Variables::tileSize * Variables::tilesPerRoom;
    switch(side)
    {
        case 0: coords->Y = totalSize - Variables::tileSize - coords->Y;
            break;
        case 1: coords->X = Variables::tileSize + (totalSize - coords->X);
            break;
        case 2: coords->Y = Variables::tileSize + (totalSize - coords->Y);
            break;
        case 3: coords->X = totalSize - Variables::tileSize - coords->X;
            break;
    }
}

void Player::updatePickUps()
{
    templateList<Entity> *pickUps = Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->getPickUpList();
    while(pickUps != NULL)
    {
        if(CollisionDetector::isBasicCollision(coords, pickUps->data->getCoords()))pickUps->data->getHit(200000, 1);
        pickUps = pickUps->next;
    }
}