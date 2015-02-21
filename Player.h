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
#include "Attributes.h"

class Player : public Entity{
    friend class Helmet;
    friend class Chestplate;
    friend class Greaves;
    friend class Attributes;
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
    
    void recalculateEquipmentBenefits();
    void changeHelmet(int newHelmetIndex);
    void changeChestplate(int newChestplateIndex);
    void changeGreaves(int newGreavesIndex);
    void useEquipment(int equipmentIndex);
    
    void addExpirience(int exp);
    int getExpirience() const;
    void increaseAttribute(int attribute, int amount);
    
    void recalculateCritical();
    void recalculateAccuracy();
private:
    void setTestValues();
    int selecetedWeaponSet;
    Equipment *chestplate;
    Equipment *helmet;
    Equipment *greaves;
    
    Weapon *shoulderGun;
    int expirience;
    
    Attributes *attributes;
};

#endif	/* PLAYER_H */

