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
    friend class MonsterLoader;
public:
    Monster();
    Monster(double X, double Y);
    virtual ~Monster();
    void update();
    void executeAgony();
private:
    int getDirection();
    void checkForAttack();
    bool isBadSpawningPoint();
    int expirience;
};

#endif	/* MONSTER_H */

