/* 
 * File:   Session.cpp
 * Author: Qb
 * 
 * Created on 4 listopad 2014, 22:27
 */

#include "Session.h"
#include "KeyboardControl.h"
#include "MouseControl.h"
#include "globalVariables.h"
#include "configurator.h"

Session::Session() {
    configurator::config();
}

Map* Session::getMap() const {
    return map;
}

void Session::create()
{
    mainMenu = new Menu();
    keyboard = new KeyboardControl();
    mouse = new MouseControl();
    hud = new HUD();
    map = new Map();
    map->createLevels();
    allEntities = new AllEntities();
}

AllEntities* Session::getAllEntities() const {
    return allEntities;
}

Menu* Session::getMainMenu() const {
    return mainMenu;
}

HUD* Session::getHud() const {
    return hud;
}

Session::Session(const Session& orig) {
}

Session::~Session() {
    delete mainMenu;
    delete allEntities;
    delete keyboard;
    delete mouse;
    delete map;
}

void Session::display()
{
    if(Variables::status == GAME)
        {
        al_clear_to_color(al_map_rgb(0,0,0));
        map->display();
        allEntities->display();
        hud->display();
        if(Variables::substate == inventory)hud->getPlayerInventory()->display();
        if(Variables::substate == chest)
        {
            hud->getPlayerInventory()->display();
            hud->getOpenChest()->displayContent();
        }
        al_flip_display();
        }
}

void Session::update()
{
    keyboard->keyboardActions();
    mouse->mouseActions();
    if(Variables::status == GAME)
        {
        updateOffset();
        map->update();
        allEntities->update();
        hud->update();
        if(Variables::substate == chest)hud->getOpenChest()->update();
    }
}

void Session::loadSave()
{
    
}

void Session::loadNew()
{
    
}

void Session::loop()
{
    while(Variables::status != END)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(Variables::event_queue, &ev);
        Variables::currentFrame++;
        if(Variables::currentFrame >= 20)Variables::currentFrame = 0;
        update();
        display();
    }
}


void Session::updateOffset()
{
    if(allEntities->getPlayer()->getCoords()->X - Variables::offsetX < 400)Variables::offsetX -= allEntities->getPlayer()->getCoords()->speedX;
    if(allEntities->getPlayer()->getCoords()->X - Variables::offsetX > Variables::RES_WIDTH-400)Variables::offsetX += allEntities->getPlayer()->getCoords()->speedX;
    if(allEntities->getPlayer()->getCoords()->Y - Variables::offsetY < 400)Variables::offsetY -= allEntities->getPlayer()->getCoords()->speedY;
    if(allEntities->getPlayer()->getCoords()->Y - Variables::offsetY > Variables::RES_HEIGHT-500)Variables::offsetY += allEntities->getPlayer()->getCoords()->speedY;
}