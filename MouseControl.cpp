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
    contentIndex = -1;
    isLeftButtonPressed = false;
    fromChest = false;
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
     if(Variables::substate == chest)chestActions();
     if(Variables::substate == inventory)inventoryAction();
}

void MouseControl::chestActions()
{     
     int inventoryIndex = Variables::session->getPlayerInventory()->getWeaponIndex();
     int chestIndex = Variables::session->getOpenChest()->getSelectedField();
     if(Variables::mouse_state.buttons & 1)
     {
         if(!isLeftButtonPressed)if(contentIndex == -1)
         {
             if(inventoryIndex != -1)
             {
                 contentIndex = inventoryIndex;
                 if(!dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->isWeapon(contentIndex))contentIndex = -1;
                 fromChest = false;
             }
             else
             {
                 contentIndex = chestIndex;
                 if(!Variables::session->getOpenChest()->isFieldNotEmpty(contentIndex))contentIndex = -1;
                 fromChest = true;
             }
         }
         isLeftButtonPressed = true;
     } else
     {
         if(isLeftButtonPressed)if(contentIndex != -1) 
         {
             if(fromChest && inventoryIndex != -1)
             {
                 Variables::session->getPlayerInventory()->swapWeapons(false, contentIndex);
                 contentIndex = -1;
             }
             if(fromChest && chestIndex != -1 && chestIndex != contentIndex)
             {
                 Variables::session->getOpenChest()->swapContent(chestIndex, contentIndex);
                 contentIndex = -1;
             }
             if(!fromChest && inventoryIndex != -1 && inventoryIndex != contentIndex)
             {
                Variables::session->getPlayerInventory()->swapWeapons(true, contentIndex);
                contentIndex = -1;
             }
             if(!fromChest && chestIndex != -1)
             {
                 Variables::session->getPlayerInventory()->storeInChest(chestIndex, contentIndex);
                 contentIndex = -1;
             }
         }             
         isLeftButtonPressed = false;
     }     
}

void MouseControl::inventoryAction()    
{
     int inventoryIndex = Variables::session->getPlayerInventory()->getWeaponIndex();
     if(Variables::mouse_state.buttons & 1)
     {
         if(!isLeftButtonPressed)if(contentIndex == -1)
         {
             contentIndex = inventoryIndex;
             if(!dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer())->isWeapon(contentIndex))contentIndex = -1;
         }
         isLeftButtonPressed = true;
     } else
     {
         if(isLeftButtonPressed)if(contentIndex != -1) 
         {
             if(inventoryIndex != -1 && inventoryIndex != contentIndex)
             {
                 Variables::session->getPlayerInventory()->swapWeapons(true, contentIndex);
                 contentIndex = -1;
             }
         }
         isLeftButtonPressed = false;    
     }
}