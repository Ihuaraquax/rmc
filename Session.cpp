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
#include <fstream>

Session::Session() {
    configurator::config();
    Variables::images = new GlobalImages();
    std::string paths[] = {"images/GameWin.png"};
    winImage = new Image(1,paths,false);
    winImage->state = UI;
    coords = new Coordinates();
    allPlans = new AllPlans();
    coords->X = 0;
    coords->Y = 0;
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
//    this->loadSave();
    al_register_event_source(Variables::event_queue, al_get_timer_event_source(Variables::timer));
    map->setOffest();
}

AllEntities* Session::getAllEntities() const {
    map->getCurrentAllEntities();
}

Menu* Session::getMainMenu() const {
    return mainMenu;
}

HUD* Session::getHud() const {
    return hud;
}

AllPlans* Session::getAllPlans() const {
    return allPlans;
}

Session::~Session() {
    delete mainMenu;
    delete keyboard;
    delete mouse;
    delete map;
    delete winImage;
    delete coords;
}

void Session::display()
{
    if(Variables::log == full)std::cout << " display ";
    if(Variables::status == GAME)
        {
        al_clear_to_color(al_map_rgb(0,0,0));
        map->display();
        hud->display();
        if(Variables::substate == inventory)hud->getPlayerInventory()->display();
        if(Variables::substate == chest)
        {
            hud->getPlayerInventory()->display();
            hud->getOpenChest()->displayContent();
        }
        if(Variables::substate == game)
        {
            allPlans->getCurrentPlan()->displayCurrent();
            map->getCurrentModule()->displayMods();
        }
        if(Variables::substate == plan)allPlans->getCurrentPlan()->displayAll();
        al_flip_display();
        }
    if(Variables::status == WIN)
    {
        winImage->display(coords);
        al_flip_display();
    }
}

void Session::update()
{
    if(Variables::log == full)std::cout << " update ";
    keyboard->keyboardActions();
    mouse->mouseActions();
    if(Variables::status == GAME)
        {
        if(Variables::substate == game)updateOffset();
        map->update();
        hud->update();
        if(Variables::substate == chest)hud->getOpenChest()->update();
    }
}

void Session::loadSave()
{
    std::fstream file;
    file.open("saves/save01.txt", std::ios::in);
    map->load(file);
    allPlans->load(file);
    file.close();
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
        if(Variables::currentFrame >= Variables::fps)Variables::currentFrame = 0;
        update();
        display();
        if(Variables::log == full)std::cout << std::endl;
    }
}


void Session::updateOffset()
{
    double X = (getAllEntities()->getPlayer()->getCoords()->X - Variables::offsetX) * Variables::ScaleX * Variables::scale;
    double Y = (getAllEntities()->getPlayer()->getCoords()->Y - Variables::offsetY) * Variables::ScaleY * Variables::scale;
    
    if(X < 400)Variables::offsetX -= getAllEntities()->getPlayer()->getCoords()->speedX;
    if(X > Variables::RES_WIDTH-400)Variables::offsetX += getAllEntities()->getPlayer()->getCoords()->speedX;
    if(Y < 400)Variables::offsetY -= getAllEntities()->getPlayer()->getCoords()->speedY;
    if(Y > Variables::RES_HEIGHT-500)Variables::offsetY += getAllEntities()->getPlayer()->getCoords()->speedY;
}

void Session::save()
{
    std::fstream file;
    file.open("saves/save01.txt", std::ios::out);
    map->save(file);
    this->allPlans->save(file);
    file.close();
}