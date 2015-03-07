/* 
 * File:   Equipment.h
 * Author: Qb
 *
 * Created on 16 luty 2015, 20:43
 */

#ifndef EQUIPMENT_H
#define	EQUIPMENT_H
#include <iostream>

class Equipment {
    friend class EquipmentLoader;
public:
    Equipment();
    virtual ~Equipment();
    void update();
    void virtual specificUpdate();
    std::string getImagePath() const;
    double getResistance(int index) const;
    int getArmor() const;
    bool isActive() const;
    int getAction() const;
    void setActive(bool active);
    int getCurrentEnergy() const;
    int getMaxEnergy() const;
    std::string virtual getFilePath();
protected:
    void virtual activate();
    void virtual deactivate();
    
    int action;
    int maxEnergy;
    int currentEnergy;
    int energyConsumption;
    int energyRegeneration;
    bool active;
    int armor;
    double *resistance;
    std::string imagePath;
    std::string name;
};

#endif	/* EQUIPMENT_H */

