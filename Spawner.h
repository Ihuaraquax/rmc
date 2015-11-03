/* 
 * File:   Spawner.h
 * Author: Qb
 *
 * Created on 8 marzec 2015, 12:43
 */

#ifndef SPAWNER_H
#define	SPAWNER_H
#include <vector>
#include "Entity.h"

class Spawner : public Entity{
public:
    Spawner();
    void setRandomCoords();
    void update();
    void save(std::fstream &file);
    void load(std::fstream &file);
    void setStartingTile();
    void setMonsterType(std::vector<int> typeList);
    std::string getEntityType();
    
    static Entity *CreateSpawner(double X, double Y);
    Entity *getMonster(double X, double Y);
    void spawnMonster();
    int getThreatLevel() const;
private:
    int monsterType;
    int spawnTimer;
    int spawnCountdown;
    int threatLevel;
};

#endif	/* SPAWNER_H */

