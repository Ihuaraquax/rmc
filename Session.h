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
#include "AllEntities.h"
#include "MouseControl.h"
#include "KeyboardControl.h"
#include "Map.h"

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
    void update();
    void config();
    void loadSave();
    void loadNew();
    void loop();
    void destroy();
    Map* getMap() const;
    AllEntities* getAllEntities() const;
    Menu* getMainMenu() const;
    
    static MainGameState gameState;
private:
    Menu *mainMenu;
    AllEntities *allEntities;
    MouseControl *mouse;
    KeyboardControl *keyboard;
    Map *map;
};

#endif	/* SESSION_H */

