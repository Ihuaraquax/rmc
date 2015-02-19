/* 
 * File:   EquipmentLoader.h
 * Author: Qb
 *
 * Created on 17 luty 2015, 21:53
 */

#ifndef EQUIPMENTLOADER_H
#define	EQUIPMENTLOADER_H
#include "Equipment.h"

class EquipmentLoader {
public:
    EquipmentLoader();
    virtual ~EquipmentLoader();
    void static loadNewEquipment(Equipment *equipment, int index, std::string path);
private:
    void static displayLogsToConsole(Equipment *equipment);
};

#endif	/* EQUIPMENTLOADER_H */

