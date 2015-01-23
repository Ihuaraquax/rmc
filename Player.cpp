/* 
 * File:   Player.cpp
 * Author: Qb
 * 
 * Created on 16 grudzień 2014, 20:50
 */

#include "Player.h"
#include "globalVariables.h"
#include "ModuleTile.h"

Player::Player() {
    setTestValues();
}


Player::~Player() {
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
    health = 20;
    weapons = new Weapon*[2];
    weapons[0] = new Weapon();
    weapons[1] = new Weapon();
    teamId = 1;
    possessedWeapons = 2;
}

void Player::playerMove(double X, double Y)
{
    move(X,Y);
    Variables::session->getMap()->getCurrentModule()->updateTileAiValue
        (coords->X + coords->width/2, coords->Y + coords->height/2, 100);
}

void Player::update()
{
    double dX, dY;
    dX = (Variables::mouse_x - 8) - (coords->X - Variables::offsetX);
    dY = (coords->Y - Variables::offsetY) - (Variables::mouse_y - 8);
    shootingAngle = 180 + (atan(dX/dY) * 180 / M_PI);
    if(Variables::mouse_y <= (coords->Y - Variables::offsetY))shootingAngle += 180;
    for(int i = 0; i < possessedWeapons; i++)weapons[i]->update();
}