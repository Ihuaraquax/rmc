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
protected:
    int action;
    int maxEnergy;
    int currentEnergy;
    int energyConsumption;
    int energyRegeneration;
    bool active;
    int armor;
    double *resistance;
    std::string imagePath;
};

#endif	/* EQUIPMENT_H */

