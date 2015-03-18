/* 
 * File:   AiTile.cpp
 * Author: Qb
 * 
 * Created on 27 styczeń 2015, 19:45
 */

#include "AiTile.h"
#include "Coordinates.h"
#include "globalVariables.h"
#include <stdlib.h>
#include <iostream>

AiTile::AiTile(bool obstructed, int roomId, int base) {
    adjacentTiles = new AiTile*[8];
    this->obstructed = obstructed;
    this->roomId = roomId;
    this->baseAIValue = base;
    if(obstructed)this->baseAIValue -= 50;
    this->entitiesAiValue = 0;
    for(int i = 0; i < 8; i++)openDoors[i] = false;
    target = new Coordinates();
    target->X = -1;
    target->Y = -1;
}


void AiTile::setRoomId(int roomId) {
    this->roomId = roomId;
}

int AiTile::getRoomId() const {
    return roomId;
}


bool AiTile::isObstructed()
{
    return obstructed;
}

void AiTile::resetAIValue()
{
    target->X = -1;
    target->Y = -1;
    currentAIValue = baseAIValue + entitiesAiValue;
}

void AiTile::updateCurrentAIValue() {
    if(currentAIValue >= 5)
    {
        for(int i = 0; i < 8; i++)
        {
            if(adjacentTiles[i] != NULL)
            if(adjacentTiles[i]->obstructed == false &&
               (adjacentTiles[i]->roomId == roomId || openDoors[i]))
            {
                if(adjacentTiles[i]->currentAIValue < currentAIValue-5)
                {
                    adjacentTiles[i]->currentAIValue = currentAIValue - 5;
                    adjacentTiles[i]->updateCurrentAIValue();
                }
            }
        }
    }
}

int AiTile::getCurrentAIValue() const {
    return currentAIValue;
}

void AiTile::setAdjacentTile(int index, AiTile* tile)
{
    adjacentTiles[index] = tile;
}

AiTile** AiTile::getAdjacentTiles() const {
    return adjacentTiles;
}

void AiTile::setOpenDoorValue(int index, bool value)
{
    openDoors[index] = value;
}

Coordinates* AiTile::getTarget() const {
    return target;
}

void AiTile::setObstructed(bool obstructed) {
    this->obstructed = obstructed;
}

void AiTile::setBaseAIValue(int baseAIValue) {
    this->baseAIValue = baseAIValue;
}

bool AiTile::isOpenDoor(int direction)
{
    return this->openDoors[direction];
}

void AiTile::changeEntitiesAiValue(int delta) {
    this->entitiesAiValue += delta;    
    if(baseAIValue + entitiesAiValue > currentAIValue)currentAIValue = baseAIValue + entitiesAiValue;
}