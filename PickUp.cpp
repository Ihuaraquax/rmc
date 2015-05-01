/* 
 * File:   PickUp.cpp
 * Author: Qb
 * 
 * Created on 27 kwiecień 2015, 21:47
 */

#include "PickUp.h"
#include "globalVariables.h"
#include "Player.h"

PickUp::PickUp() {
    image = Variables::images->getPickUp();
    type = rand()%12;
    health = 1200;
    coords = new Coordinates();
    coords->angle = 1;
    coords->width = 25;
    coords->height = 25;
}

void PickUp::update()
{
    health--;
}

void PickUp::executeAgony()
{
    Player *player = dynamic_cast<Player*>(Variables::session->getAllEntities()->getPlayer());
    if(health < -100)
    {
        switch(type)
        {
            case 0: player->heal(100);
            break;
            case 1: player->addAmmo(100, 0);
            break;
            case 2: player->addAmmo(100, 1);
            break;
            case 3: player->addAmmo(100, 2);
            break;
            case 4: player->addAmmo(100, 3);
            break;
            case 5: player->addAmmo(100, 4);
            break;
            case 6: player->addAmmo(100, 5);
            break;
            case 7: player->addAmmo(100, 6);
            break;
            case 8: player->addAmmo(100, 7);
            break;
            case 9: player->addAmmo(100, 8);
            break;
            case 10: player->addAmmo(100, 9);
            break;
            case 11: 
//                GenericBuffer *buff new TimedBuffer();
//                player->addBuffer()
            break;
        }
    }
}