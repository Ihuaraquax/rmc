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
    void setAdjacentTiles(ModuleTile **tiles);
    
    void addToWallList(Wall *walls);
    void addToDoorList(Door *doors, int direction);
    void addToEntityList(Entity *toAdd);
    
    Door **getDoorList() const;
    templateList<Wall> *getWallList() const;
    ModuleTile** getAdjacentTiles() const;
    
    void deleteFromEntityList(Entity *toDelete);
    templateList<Entity>* getEntityList() const;
    void deleteWall(Wall *toDelete);
    
    AiTile* getAiTile() const;
    bool hasOpenDoor(int direction);
    
    void addToThreatLevel(int threatLevel);
    int getThreatLevel() const;
    
    void propagateTurret(Entity *turret);
    
    void setCenter(int X, int Y);
private:
    ModuleTile **adjacentTiles;
    templateList<Entity> *entityList;
    templateList<Wall> *wallList;
    templateList<Entity> *turretList;
    Door **doorList;
    AiTile *aiTile;
    int threatLevel;
    int centerX, centerY;
};

#endif	/* MODULETILE_H */

