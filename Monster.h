/* 
 * File:   Monster.h
 * Author: Qb
 *
 * Created on 16 grudzień 2014, 20:50
 */

#ifndef MONSTER_H
#define	MONSTER_H
#include "Entity.h"

class Monster : public Entity {
public:
    Monster();
    Monster(const Monster& orig);
    virtual ~Monster();
    void update();
private:

};

#endif	/* MONSTER_H */

