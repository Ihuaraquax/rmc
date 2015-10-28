/* 
 * File:   ModuleDoorEntities.h
 * Author: Adiutant
 *
 * Created on 28 październik 2015, 21:47
 */

#ifndef MODULEDOORENTITIES_H
#define	MODULEDOORENTITIES_H
#include "Entity.h"

class ModuleDoorEntities {
public:
    ModuleDoorEntities();
    void SetDownDoor(Entity* downDoor);
    Entity* GetDownDoor() const;
    void SetRightDoor(Entity* rightDoor);
    Entity* GetRightDoor() const;
    void SetLeftDoor(Entity* leftDoor);
    Entity* GetLeftDoor() const;
    void SetUpDoor(Entity* upDoor);
    Entity* GetUpDoor() const;
private:
    Entity *upDoor;
    Entity *leftDoor;
    Entity *rightDoor;
    Entity *downDoor;
};

#endif	/* MODULEDOORENTITIES_H */

