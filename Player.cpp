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

Player::Player() {
    setTestValues();
    targetCoords = new Coordinates();
    this->threatLevel = 0;
    Variables::session->getMap()->getCurrentModule()->updateTileAiTarget
        (coords->X + coords->width/2, coords->Y + coords->height/2);
}


Player::~Player() {
    delete helmet;
    delete chestplate;
    delete greaves;
}

void Player::setTestValues()
{
    this->coords = new Coordinates();
    this->coords->X = 115;
    this->coords->Y = 115;
    this->coords->angle = 0;
    this->coords->height = 25;
    this->coords->width = 25;
    this->coords->speedX = 1;
    this->coords->speedY = 1;
    std::string paths[] = {"images/player.png"};
    this->image = new Image(1, paths, true);
    this->image->state = NORMAL;
    health = 20;
    weapons = new Weapon*[6];
    for(int i = 0; i < 6; i++)weapons[i] = new Weapon();
    WeaponLoader::loadWeapon(weapons[0], 6);
    WeaponLoader::loadWeapon(weapons[1], 31);
    WeaponLoader::loadWeapon(weapons[2], 12);
    WeaponLoader::loadWeapon(weapons[3], 1);
    WeaponLoader::loadWeapon(weapons[4], 27);
    WeaponLoader::loadWeapon(weapons[5], 23);    
    helmet = new Helmet();
    chestplate = new Chestplate();
    greaves = new Greaves();
    teamId = 1;
    possessedWeapons = 6;
    aiValue = 100;
    Variables::session->getHud()->getMainWeaponUI()->selectWeapon(weapons[0]);
    Variables::session->getHud()->getSecondaryWeaponUI()->selectWeapon(weapons[1]);
    Variables::session->getHud()->getEquipmentUI()->reloadImages(helmet, chestplate, greaves);
    selecetedWeaponSet = 0;
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
    coords->angle = Variables::getAngle(coords->X, coords->Y, targetCoords->X, targetCoords->Y);
    for(int i = 0; i < possessedWeapons; i++)weapons[i]->update();
}

void Player::display()
{
    image->display(coords);
    al_draw_circle(Variables::mouse_x, Variables::mouse_y, weapons[selecetedWeaponSet*2 + 0]->getCurrentTargetSize(), al_map_rgb(255,0,0), 5);
    al_draw_circle(Variables::mouse_x, Variables::mouse_y, weapons[selecetedWeaponSet*2 + 1]->getCurrentTargetSize(), al_map_rgb(0,0,255), 3);
}

void Player::interact()
{
    for(int i = 0; i < 4; i++)
    {
        Variables::session->getMap()->getCurrentModule()->getModuleTileAt(coords->X, coords->Y)->useDoor(i);
    }
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