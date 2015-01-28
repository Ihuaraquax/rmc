/* 
 * File:   Player.h
 * Author: Qb
 *
 * Created on 16 grudzień 2014, 20:50
 */

#ifndef PLAYER_H
#define	PLAYER_H
#include "Entity.h"

class Player : public Entity{
public:
    Player();
    virtual ~Player();
    void playerMove(double X, double Y);
    void update();
    void display();
private:
    void setTestValues();
};

#endif	/* PLAYER_H */

