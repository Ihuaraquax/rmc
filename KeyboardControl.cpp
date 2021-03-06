/* 
 * File:   KeyboardControl.cpp
 * Author: Qb
 * 
 * Created on 4 listopad 2014, 22:27
 */

#include "KeyboardControl.h"
#include "globalVariables.h"
#include "Entity.h"
#include "Player.h"
#include "AttributeEnum.h"
#include "Console.h"

KeyboardControl::KeyboardControl() {
    pressedKeys = new bool[ALLEGRO_KEY_MAX];
    for(int i = 0; i < ALLEGRO_KEY_MAX; i++)pressedKeys[i] = false;
}

void KeyboardControl::keyboardActions()
{
     al_get_keyboard_state(&Variables::key_state);
     if(isPressed(ALLEGRO_KEY_ESCAPE))
     {
         if(Variables::substate == console || Variables::substate == plan)Console::end();
         else Variables::status = END;
     }
     if(Variables::status == GAME)this->gameKeyboardActions();
}

void KeyboardControl::gameKeyboardActions()
{
     Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    
     if(Variables::substate == game || Variables::substate == plan)
     {
         if(al_key_down(&Variables::key_state, ALLEGRO_KEY_UP))Variables::offsetY-=5;
         if(al_key_down(&Variables::key_state, ALLEGRO_KEY_DOWN))Variables::offsetY+=5;
         if(al_key_down(&Variables::key_state, ALLEGRO_KEY_LEFT))Variables::offsetX-=5;
         if(al_key_down(&Variables::key_state, ALLEGRO_KEY_RIGHT))Variables::offsetX+=5;


         if(al_key_down(&Variables::key_state, ALLEGRO_KEY_W))player->playerMove(0,-1);
         if(al_key_down(&Variables::key_state, ALLEGRO_KEY_S))player->playerMove(0,1);
         if(al_key_down(&Variables::key_state, ALLEGRO_KEY_A))player->playerMove(-1,0);
         if(al_key_down(&Variables::key_state, ALLEGRO_KEY_D))player->playerMove(1,0);
     }
     
     if(isPressed(ALLEGRO_KEY_1))player->selectWeaponSet(0);
     if(isPressed(ALLEGRO_KEY_2))player->selectWeaponSet(1);
     if(isPressed(ALLEGRO_KEY_3))player->selectWeaponSet(2);
     
     if(isPressed(ALLEGRO_KEY_F))player->interact();
     if(isPressed(ALLEGRO_KEY_Z))player->useEquipment(0);
     if(isPressed(ALLEGRO_KEY_X))player->useEquipment(1);
     if(isPressed(ALLEGRO_KEY_C))player->useEquipment(2);
     if(isPressed(ALLEGRO_KEY_E))player->useItem();
     if(isPressed(ALLEGRO_KEY_P))Variables::session->save();
     if(isPressed(ALLEGRO_KEY_I))
     {
         if(Variables::substate == game)
         {
             Variables::session->getHud()->getPlayerInventory()->init();
             Variables::substate = inventory;
         }
         else if(Variables::substate == inventory)Variables::substate = game;
     }
     if(isPressed(ALLEGRO_KEY_M))
     {
         if(Variables::substate == game)
         {
             Variables::substate = plan;
             Variables::scale = 0.15;
             Variables::session->getMap()->setPlanCoords();
             Variables::session->getMap()->setOffest();
         }
         else if(Variables::substate == plan)
         {
             Variables::substate = game;
             Variables::scale = 1;
            Variables::session->getMap()->setOffest();
         }
     }
}

bool KeyboardControl::isPressed(int key)
{
    if(!pressedKeys[key] && al_key_down(&Variables::key_state, key))
    {
        pressedKeys[key] = true;
        return true;
    }
    if(pressedKeys[key] && !al_key_down(&Variables::key_state, key))
    {
        pressedKeys[key] = false;
    }
    return false;
}