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
    keyPressed[0] = false;
    keyPressed[1] = false;
}

void MouseControl::mouseActions()
{
     al_get_mouse_state(&Variables::mouse_state);
     Variables::mouse_x = al_get_mouse_state_axis(&Variables::mouse_state, 0);
     Variables::mouse_y = al_get_mouse_state_axis(&Variables::mouse_state, 1);
     
     Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
     if(Variables::substate == game)
     {
         if(Variables::mouse_state.buttons & 1)player->attack(0 + player->getSelecetedWeaponSet()*2);     
         if(Variables::mouse_state.buttons & 2)player->attack(1 + player->getSelecetedWeaponSet()*2);
     }
     else if(Variables::substate == plan)
     {
         if(onPress(0))Variables::session->getAllPlans()->getCurrentPlan()->createStepAtMouse();
         if(Variables::mouse_state.buttons & 2)Variables::session->getAllPlans()->getCurrentPlan()->destroyStepAtMouse();
     }
     if(Variables::substate == chest)Variables::session->getHud()->mouseChestControls();
     if(Variables::substate == inventory)Variables::session->getHud()->mouseInventoryControls();
}

bool MouseControl::onPress(int mosueKey)
{
    if(!keyPressed[mosueKey] && Variables::mouse_state.buttons & mosueKey+1)
    {
        keyPressed[mosueKey] = true;
        return true;
    }
    if(keyPressed[mosueKey] && !Variables::mouse_state.buttons & mosueKey+1)
    {
        keyPressed[mosueKey] = false;
    }
    return false;
}