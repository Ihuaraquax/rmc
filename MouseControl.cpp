/* 
 * File:   MouseControl.cpp
 * Author: Qb
 * 
 * Created on 4 listopad 2014, 22:27
 */

#include "MouseControl.h"
#include "globalVariables.h"
#include "Player.h"

MouseControl::MouseControl() {
}

void MouseControl::mouseActions()
{
     al_get_mouse_state(&Variables::mouse_state);
     Variables::mouse_x = al_get_mouse_state_axis(&Variables::mouse_state, 0);
     Variables::mouse_y = al_get_mouse_state_axis(&Variables::mouse_state, 1);
     
     Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
     
     if(Variables::mouse_state.buttons & 1)player->attack(0 + player->getSelecetedWeaponSet()*2);
     
     if(Variables::mouse_state.buttons & 2)player->attack(1 + player->getSelecetedWeaponSet()*2);
}