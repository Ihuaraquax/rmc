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
    targetCoords = new Coordinates();
    this->threatLevel = 0;
    Variables::session->getMap()->getCurrentModule()->updateTileAiValue
        (coords->X + coords->width/2, coords->Y + coords->height/2, 100);
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
    this->image->state = NORMAL;
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
    targetCoords->X = Variables::mouse_x;
    targetCoords->Y = Variables::mouse_y;
    for(int i = 0; i < possessedWeapons; i++)weapons[i]->update();
}

void Player::display()
{
    image->display(coords);
    al_draw_circle(Variables::mouse_x, Variables::mouse_y, weapons[0]->getCurrentTargetSize(), al_map_rgb(255,0,0), 5);
}