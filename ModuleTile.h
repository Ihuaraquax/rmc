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

class ModuleTile {
public:
    ModuleTile(bool obstructed, int roomId, int base);
    ModuleTile(const ModuleTile& orig);
    virtual ~ModuleTile();
    double getAngle();
    void updateDistances();
    bool isObstructed();
    void setRoomId(int roomId);
    int getRoomId() const;
    void resetAIValue();
    void setCurrentAIValue(int currentAIValue);
    int getCurrentAIValue() const;
    void setAdjacentTiles(ModuleTile **tiles);
    void setAdjacentTilesCount(int adjacentTilesCount);
    int getAdjacentTilesCount() const;
    void addToWallList(Wall *walls);
    void addToDoorList(Door *doors);
    std::list<Door*> getDoorList() const;
    std::list<Wall*> getWallList() const;
    ModuleTile** getAdjacentTiles() const;
    void addToEntityList(Entity *toAdd);
    void deleteFromEntityList(Entity *toDelete);
    templateList<Entity>* getEntityList() const;
private:
    int roomId;
    bool obstructed;
    int baseAIValue;
    int currentAIValue;
    ModuleTile **adjacentTiles;
    int adjacentTilesCount;
    double angle;
    templateList<Entity> *entityList;
    std::list<Wall*>wallList;
    std::list<Door*>doorList;
};

#endif	/* MODULETILE_H */

