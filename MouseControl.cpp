/* 
 * File:   MouseControl.cpp
 * Author: Qb
 * 
 * Created on 4 listopad 2014, 22:27
 */

#include "MouseControl.h"
#include "globalVariables.h"

MouseControl::MouseControl() {
}

void MouseControl::mouseActions()
{
     al_get_mouse_state(&Variables::mouse_state);
     Variables::mouse_x = al_get_mouse_state_axis(&Variables::mouse_state, 0);
     Variables::mouse_y = al_get_mouse_state_axis(&Variables::mouse_state, 1);
     
     if(Variables::mouse_state.buttons & 1)
         Variables::session->getAllEntities()->getPlayer()->attack(0);
     
     if(Variables::mouse_state.buttons & 2)
         Variables::session->getAllEntities()->getPlayer()->attack(1);
}