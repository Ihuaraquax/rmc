/* 
 * File:   Button.cpp
 * Author: Qb
 * 
 * Created on 4 listopad 2014, 22:28
 */

#include "Button.h"
#include "globalVariables.h"
#include "CollisionDetector.h"
#include "Player.h"


Button::Button(int action) {
    this->action = action;
    if(this->action %2 == 1)image = new Image("images/buttons/buttonAttributeMinus.jpg", false);
    else image = new Image("images/buttons/buttonAttributePlus.jpg", false);
    image->state = UI;
    coords = new Coordinates();
    coords->width = 50;
    coords->height = 50;
    coords->Y = 45;
    coords->X = 30 + ((action / 2) * 160);
    if(this->action % 2 == 0)coords->X += 90;
}

Button::Button(const Button& orig) {
    delete coords;
    delete image;
}

Button::~Button() {
}

void Button::display()
{
    image->display(coords);
}

void Button::update()
{
}

void Button::execute()
{
    Coordinates *mouseCoords = Variables::mouseCoords;
    if(CollisionDetector::isBasicCollision(coords, mouseCoords))
    {
        makeAction();
    }
    delete mouseCoords;
}

void Button::makeAction()
{
    switch(this->action)
    {
        case 0: dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->getAttributes()->addStrength(1);
        break;
        case 1: dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->getAttributes()->addStrength(-1);
        break;
        case 2: dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->getAttributes()->addInteligence(1);
        break;
        case 3: dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->getAttributes()->addInteligence(-1);
        break;
        case 4: dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->getAttributes()->addAccuracy(1);
        break;
        case 5: dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->getAttributes()->addAccuracy(-1);
        break;
        case 6: dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->getAttributes()->addSpeed(1);
        break;
        case 7: dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->getAttributes()->addSpeed(-1);
        break;
    }
}