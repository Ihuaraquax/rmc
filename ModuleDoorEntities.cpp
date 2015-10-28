/* 
 * File:   ModuleDoorEntities.cpp
 * Author: Adiutant
 * 
 * Created on 28 październik 2015, 21:47
 */

#include "ModuleDoorEntities.h"

ModuleDoorEntities::ModuleDoorEntities() {
}

void ModuleDoorEntities::SetDownDoor(Entity* downDoor) {
    this->downDoor = downDoor;
}

Entity* ModuleDoorEntities::GetDownDoor() const {
    return downDoor;
}

void ModuleDoorEntities::SetRightDoor(Entity* rightDoor) {
    this->rightDoor = rightDoor;
}

Entity* ModuleDoorEntities::GetRightDoor() const {
    return rightDoor;
}

void ModuleDoorEntities::SetLeftDoor(Entity* leftDoor) {
    this->leftDoor = leftDoor;
}

Entity* ModuleDoorEntities::GetLeftDoor() const {
    return leftDoor;
}

void ModuleDoorEntities::SetUpDoor(Entity* upDoor) {
    this->upDoor = upDoor;
}

Entity* ModuleDoorEntities::GetUpDoor() const {
    return upDoor;
}