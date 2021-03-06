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
    void updateCurrentAIValue();
    int getCurrentAIValue() const;
    void setAdjacentTile(int index, AiTile *tile);
    AiTile** getAdjacentTiles() const;
    Coordinates* getTarget() const;
    void setObstructed(bool obstructed);
    void setBaseAIValue(int baseAIValue);
    void changeEntitiesAiValue(int delta);
private:
    AiTile **adjacentTiles;
    int roomId;
    bool obstructed;
    int baseAIValue;
    int currentAIValue;
    int entitiesAiValue;
    Coordinates *target;
};

#endif	/* AITILE_H */

