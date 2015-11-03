/* 
 * File:   AllEntities.h
 * Author: Qb
 *
 * Created on 16 listopad 2014, 11:31
 */

#ifndef ALLENTITIES_H
#define	ALLENTITIES_H
#include <list>
#include <vector>
#include "Entity.h"
#include "ModuleDoorEntities.h"

class AllEntities {
public:
    AllEntities();
    ~AllEntities();
    void init();
    void update();
    void display();
    void displayPlan();
    void loadFile();
    void loadNew();
    void addEntity(Entity *newEntity);
    void deleteEntity(Entity *toDelete);
    Entity* getPlayer() const;
    
    void addRemoteCharge(Entity *toAdd);
    bool deleteRemoteCharge(int signalId);
    void applyModifiers();
    void setPlayer(Entity* player);
    
    void save(std::fstream &file);
    void load(std::fstream &file);
    bool isOnList(Entity *entity);
    void setPlanCoords(int X, int Y);
    
    void createAllowanceObjects(int X, int Y);
    void createModuleDoor(int X, int Y);
    void updateVirtualThreatLevel(bool currentModule);
    void recreateSpawners();
private:
    void deleteDead();
    void createObstacles();
    void createDoors();
    void collisions();
    
    void getMonstersFromAdjacentModules();
    void spawnMonstersFromSpawners();
    Entity* getMonsterFromModule(double X, double Y);
    
    std::list<Entity*> entityList;
    templateList<Entity> *remoteCharges;
    Entity *player;
    double threatLevel;
    double virtualThreatLevel;
    double maxThreatLevel;
    ModuleDoorEntities *moduleDoors;
    std::vector<int> possibleMonsterTypes;
    int threatLevelIncrement;
    std::vector<Entity*> spawnerList;
};

#endif	/* ALLENTITIES_H */

