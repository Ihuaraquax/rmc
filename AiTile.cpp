/* 
 * File:   AiTile.cpp
 * Author: Qb
 * 
 * Created on 27 styczeń 2015, 19:45
 */

#include "AiTile.h"
#include "Coordinates.h"
#include <stdlib.h>
#include <iostream>

AiTile::AiTile(bool obstructed, int roomId, int base) {
    adjacentTiles = new AiTile*[8];
    this->obstructed = obstructed;
    this->roomId = roomId;
    this->baseAIValue = base;
    if(obstructed)this->baseAIValue -= 50;
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
    currentAIValue = baseAIValue;
    for(int i = 0; i < 8; i++)
    {
        if(adjacentTiles[i] != NULL)
        if((adjacentTiles[i]->roomId == roomId || openDoors[i])&&
           adjacentTiles[i]->currentAIValue != adjacentTiles[i]->baseAIValue)
                adjacentTiles[i]->resetAIValue();
    }
}

void AiTile::setCurrentAIValue(int currentAIValue) {
    this->currentAIValue = currentAIValue;
    for(int i = 0; i < 8; i++)
    {
        if(adjacentTiles[i] != NULL)
        if(adjacentTiles[i]->obstructed == false &&
           (adjacentTiles[i]->roomId == roomId || openDoors[i]) &&
           adjacentTiles[i]->currentAIValue < currentAIValue-5)
                adjacentTiles[i]->setCurrentAIValue(currentAIValue-5);
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