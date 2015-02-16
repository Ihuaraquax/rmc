/* 
 * File:   Player.h
 * Author: Qb
 *
 * Created on 16 grudzień 2014, 20:50
 */

#ifndef PLAYER_H
#define	PLAYER_H
#include "Entity.h"
#include "Equipment.h"

class Player : public Entity{
public:
    Player();
    virtual ~Player();
    void playerMove(double X, double Y);
    void update();
    void display();
    void interact();
    void selectWeaponSet(int set);
    int getSelecetedWeaponSet() const;
    
    Equipment* getGreaves() const;
    Equipment* getHelmet() const;
    Equipment* getChestplate() const;
private:
    void setTestValues();
    int selecetedWeaponSet;
    Equipment *chestplate;
    Equipment *helmet;
    Equipment *greaves;
};

#endif	/* PLAYER_H */

