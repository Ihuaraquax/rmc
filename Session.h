/* 
 * File:   Session.h
 * Author: Qb
 *
 * Created on 4 listopad 2014, 22:27
 */

#ifndef SESSION_H
#define	SESSION_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "Menu.h"
#include "HUD.h"
#include "AllEntities.h"
#include "MouseControl.h"
#include "KeyboardControl.h"
#include "Map.h"
#include "AllPlans.h"
#include "LightSource.h"
#include "Tooltip.h"

enum MainGameState
{
    MAP, MODULE
};

class Session {
public:
    Session();
    virtual ~Session();
    void display();
    void create();
    void update();
    void config();
    void loadSave();
    void loadNew();
    void save();
    void loop();
    void destroy();
    Map* getMap() const;
    AllEntities* getAllEntities() const;
    Menu* getMainMenu() const;
    HUD* getHud() const;
    AllPlans* getAllPlans() const;
    Tooltip* getTooltip() const;
    
    static MainGameState gameState;
private:
    void updateOffset();
    
    Menu *mainMenu;
    MouseControl *mouse;
    KeyboardControl *keyboard;
    Map *map;
    HUD *hud;
    Image *winImage;
    Coordinates *coords;
    AllPlans *allPlans;
    Tooltip *tooltip;
};

#endif	/* SESSION_H */

