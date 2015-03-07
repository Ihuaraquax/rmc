/* 
 * File:   Chestplate.h
 * Author: Qb
 *
 * Created on 16 luty 2015, 19:52
 */

#ifndef CHESTPLATE_H
#define	CHESTPLATE_H
#include "Equipment.h"

class Chestplate : public Equipment {
    friend class EquipmentLoader;
public:
    Chestplate();
    virtual ~Chestplate();
    void specificUpdate();
    std::string getFilePath();
private:
    void activate();
    void deactivate();
};

#endif	/* CHESTPLATE_H */

