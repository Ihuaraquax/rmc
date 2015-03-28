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
    Monster(bool isLoad);
    Monster(double X, double Y);
    virtual ~Monster();
    void update();
    void executeAgony();
    void save(std::fstream &file);
    void load(std::fstream &file);
private:
    bool turnRight(double targetAngle);
    int getDirection();
    void checkForAttack();
    bool isBadSpawningPoint();
    int expirience;
};

#endif	/* MONSTER_H */

