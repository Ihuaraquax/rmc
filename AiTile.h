/* 
 * File:   AiTile.h
 * Author: Qb
 *
 * Created on 27 styczeń 2015, 19:45
 */

#ifndef AITILE_H
#define	AITILE_H
#include "Coordinates.h"

class AiTile {
public:
    AiTile(bool obstructed, int roomId, int base);
    bool isObstructed();
    void setRoomId(int roomId);
    int getRoomId() const;
    void resetAIValue();
    void updateCurrenTAIValue();
    int getCurrentAIValue() const;
    void setAdjacentTile(int index, AiTile *tile);
    AiTile** getAdjacentTiles() const;
    void setOpenDoorValue(int index, bool value);
    Coordinates* getTarget() const;
    void setObstructed(bool obstructed);
    void setBaseAIValue(int baseAIValue);
    bool isOpenDoor(int direction);
    void changeEntitiesAiValue(int delta);
private:
    AiTile **adjacentTiles;
    int roomId;
    bool obstructed;
    int baseAIValue;
    int currentAIValue;
    int entitiesAiValue;
    bool openDoors[8];
    Coordinates *target;
};

#endif	/* AITILE_H */

