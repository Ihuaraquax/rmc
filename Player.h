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
#include "UsableItem.h"
#include "Inventory.h"
#include "Animation.h"
#include "Skills.h"

class Player : public Entity{
    friend class Helmet;
    friend class Chestplate;
    friend class Greaves;
    friend class Attributes;
    friend class Inventory;
public:
    Player();
    Player(bool isLoad);
    virtual ~Player();
    void playerMove(double X, double Y);
    void update();
    void updatePlanStep();
    void updatePickUps();
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
    
    void useItem();
    void changeItem(int index);
    
    int getAmmo(int index);
    void addAmmo(int ammo, int index);
    
    bool isWeapon(int index);
    
    void save(std::fstream &file);
    void load(std::fstream &file);
    void loadGeneric(std::fstream &file);
    void setKeyValue(int keyValue);
    int getKeyValue() const;
    Attributes* getAttributes() const;
    Skills* getSkills() const;
private:
    void setTransferCoords(int side);
    void setTestValues();
    void displayIsInBuffRange();
    int selecetedWeaponSet;
    Equipment *chestplate;
    Equipment *helmet;
    Equipment *greaves;
    UsableItem *item;
    Skills *skills;
    
    Weapon *shoulderGun;
    int expirience;
    int *ammo;
    
    Attributes *attributes;
    int keyValue;
    Animation *animation;
};

#endif	/* PLAYER_H */

