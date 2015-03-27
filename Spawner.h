/* 
 * File:   Spawner.h
 * Author: Qb
 *
 * Created on 8 marzec 2015, 12:43
 */

#ifndef SPAWNER_H
#define	SPAWNER_H
#include "Entity.h"

class Spawner : public Entity{
public:
    Spawner();
    void update();
    void save(std::fstream &file);
private:
    void spawnMonster();
    int monsterType;
    int spawnTimer;
    int spawnCountdown;
};

#endif	/* SPAWNER_H */

