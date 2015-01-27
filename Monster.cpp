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
    health = 20;
    teamId = 0;
}


Monster::~Monster() {
}

void Monster::update()
{
    ModuleTile *tile = Variables::session->getMap()->getCurrentModule()->
            getModuleTileAt(coords->X + 25 - coords->width/2,
            coords->Y + 25 - coords->height/2);
    int biggestAIValue = tile->getAiTile()->getCurrentAIValue();
    int direction = -1;
    for(int i = 0; i < 8; i++)
    {
        if(tile->getAdjacentTiles()[i] != NULL)
        if(tile->getAdjacentTiles()[i]->getAiTile()->getCurrentAIValue() > biggestAIValue)
        {
            biggestAIValue = tile->getAiTile()->getAdjacentTiles()[i]->getCurrentAIValue();
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
