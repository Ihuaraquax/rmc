/* 
 * File:   ModuleTile.h
 * Author: Qb
 *
 * Created on 8 grudzień 2014, 18:53
 */

#ifndef MODULETILE_H
#define	MODULETILE_H
#include <list>
#include "Entity.h"
#include "Wall.h"
#include "Door.h"
#include "templateList.h"
#include "AiTile.h"

class ModuleTile {
public:
    void update();
    
    ModuleTile(bool obstructed, int roomId, int base);
    ~ModuleTile();
    void setAdjacentTiles(ModuleTile **tiles);
    
    void addToWallList(Wall *walls, int direction);
    void addToDoorList(Door *doors, int direction);
    void addToEntityList(Entity *toAdd);
    
    Door **getDoorList() const;
    Wall **getWallList() const;
    ModuleTile** getAdjacentTiles() const;
    
    void deleteFromEntityList(Entity *toDelete);
    templateList<Entity>* getEntityList() const;
    void deleteWall(Wall *toDelete);
    void deleteDoor(Door *toDelete);
    
    AiTile* getAiTile() const;
    bool hasOpenDoor(int direction);
    
    void addToThreatLevel(int threatLevel);
    int getThreatLevel() const;
    
    void propagateTurret(Entity *turret);
    void deleteTurret(Entity *turret);
    
    void setCenter(int X, int Y);
    Entity* getObstacle() const;
    void setObstacle(Entity* obstacle);
    void useDoor(int direction);
private:
    ModuleTile **adjacentTiles;
    templateList<Entity> *entityList;
    Wall **wallList;
    templateList<Entity> *turretList;
    Entity *obstacle;
    Door **doorList;
    AiTile *aiTile;
    int threatLevel;
    int centerX, centerY;    
    
    void deleteFromTurretList(Entity *toDelete);
};

#endif	/* MODULETILE_H */

