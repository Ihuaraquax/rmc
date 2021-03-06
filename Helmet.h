/* 
 * File:   Helmet.h
 * Author: Qb
 *
 * Created on 16 luty 2015, 19:52
 */

#ifndef HELMET_H
#define	HELMET_H
#include "Equipment.h"

class Helmet : public Equipment {
    friend class EquipmentLoader;
public:
    Helmet();
    virtual ~Helmet();
    void specificUpdate();
    std::string getFilePath();
private:
    void activate();
    void deactivate();
};

#endif	/* HELMET_H */

