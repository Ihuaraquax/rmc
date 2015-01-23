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

KeyboardControl::KeyboardControl() {
}

void KeyboardControl::keyboardActions()
{
     al_get_keyboard_state(&Variables::key_state);
     if(al_key_down(&Variables::key_state, ALLEGRO_KEY_ESCAPE))Variables::status = END;
     if(Variables::status == GAME)this->gameKeyboardActions();
}

void KeyboardControl::gameKeyboardActions()
{
     if(al_key_down(&Variables::key_state, ALLEGRO_KEY_UP))Variables::offsetY-=5;
     if(al_key_down(&Variables::key_state, ALLEGRO_KEY_DOWN))Variables::offsetY+=5;
     if(al_key_down(&Variables::key_state, ALLEGRO_KEY_LEFT))Variables::offsetX-=5;
     if(al_key_down(&Variables::key_state, ALLEGRO_KEY_RIGHT))Variables::offsetX+=5;
     
     Entity *player = Variables::session->getAllEntities()->getPlayer();
     
     if(al_key_down(&Variables::key_state, ALLEGRO_KEY_W))dynamic_cast<Player*>(player)->playerMove(0,-1);
     if(al_key_down(&Variables::key_state, ALLEGRO_KEY_S))dynamic_cast<Player*>(player)->playerMove(0,1);
     if(al_key_down(&Variables::key_state, ALLEGRO_KEY_A))dynamic_cast<Player*>(player)->playerMove(-1,0);
     if(al_key_down(&Variables::key_state, ALLEGRO_KEY_D))dynamic_cast<Player*>(player)->playerMove(1,0);
}