/* 
 * File:   Monster.cpp
 * Author: Qb
 * 
 * Created on 16 grudzień 2014, 20:50
 */

#include "Monster.h"
#include "globalVariables.h"
#include "ModuleTile.h"

Monster::Monster() {
    this->projectile = false;
    this->coords = new Coordinates();
    this->coords->X = rand()%800 + 15;
    this->coords->Y = rand()%800 + 15;
    this->coords->angle = 0;
    this->coords->height = 25;
    this->coords->width = 25;
    this->coords->speedX = 1;
    this->coords->speedY = 1;
    std::string paths[] = {"images/monster.png"};
    this->image = new Image(1, paths, true);
    health = 2;
    teamId = 0;
}

Monster::Monster(const Monster& orig) {
}

Monster::~Monster() {
//    delete coords;
//    delete image;
}

void Monster::update()
{
    ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->
            getModuleTileAt(coords->X + 25 - coords->width/2,
            coords->Y + 25 - coords->height/2);
    int biggestAIValue = tile->getCurrentAIValue();
    int direction = -1;
    for(int i = 0; i < tile->getAdjacentTilesCount(); i++)
    {
        if(tile->getAdjacentTiles()[i] != NULL)
        if(tile->getRoomId() == tile->getAdjacentTiles()[i]->getRoomId())
        if(tile->getAdjacentTiles()[i]->getCurrentAIValue() > biggestAIValue)
        {
            biggestAIValue = tile->getAdjacentTiles()[i]->getCurrentAIValue();
            direction = i;
        }
    }
    if(direction >= 0)
    {
        coords->angle = direction * 45;
        double x,y;
        Variables::giveFactors(coords->angle, x,y);
        this->move(x,y);
    }
}
