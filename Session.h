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
#include "Inventory.h"
#include "Chest.h"

enum MainGameState
{
    MAP, MODULE
};

class Session {
public:
    Session();
    Session(const Session& orig);
    virtual ~Session();
    void display();
    void create();
    void update();
    void config();
    void loadSave();
    void loadNew();
    void loop();
    void destroy();
    Map* getMap() const;
    AllEntities* getAllEntities() const;
    Menu* getMainMenu() const;
    HUD* getHud() const;
    
    static MainGameState gameState;
private:
    void updateOffset();
    
    Menu *mainMenu;
    AllEntities *allEntities;
    MouseControl *mouse;
    KeyboardControl *keyboard;
    Map *map;
    HUD *hud;
};

#endif	/* SESSION_H */

