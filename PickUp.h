/* 
 * File:   PickUp.h
 * Author: Qb
 *
 * Created on 27 kwiecień 2015, 21:47
 */

#ifndef PICKUP_H
#define	PICKUP_H
#include "Entity.h"

class PickUp : public Entity {
public:
    PickUp();
    void update();
    void executeAgony();
private:
    int type;
};

#endif	/* PICKUP_H */

