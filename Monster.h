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
    Monster(int monsterType);
    void setCoords(double X, double Y);
    void setRandomCoords();
    virtual ~Monster();
    void update();
    void executeAgony();
    void save(std::fstream &file);
    void load(std::fstream &file);
    void setStartingTile();
    
    static Entity *CreateMonster(double X, double Y, int monsterType);
private:
    void getValuesFromFile();
    int monsterType;
    bool turnRight(double targetAngle);
    int getDirection();
    void checkForAttack();
    bool isBadSpawningPoint();
    int expirience;
    int aiType;
};

#endif	/* MONSTER_H */

