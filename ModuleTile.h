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
    ModuleTile(bool obstructed, int roomId, int base);
    void setAdjacentTiles(ModuleTile **tiles);
    
    void addToWallList(Wall *walls);
    void addToDoorList(Door *doors);
    void addToEntityList(Entity *toAdd);
    
    std::list<Door*> getDoorList() const;
    templateList<Wall> *getWallList() const;
    ModuleTile** getAdjacentTiles() const;
    
    void deleteFromEntityList(Entity *toDelete);
    templateList<Entity>* getEntityList() const;
    void deleteWall(Wall *toDelete);
    
    AiTile* getAiTile() const;
private:
    ModuleTile **adjacentTiles;
    templateList<Entity> *entityList;
    templateList<Wall> *wallList;
    std::list<Door*>doorList;
    AiTile *aiTile;
};

#endif	/* MODULETILE_H */

