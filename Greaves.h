/* 
 * File:   Greaves.h
 * Author: Qb
 *
 * Created on 16 luty 2015, 19:52
 */

#ifndef GREAVES_H
#define	GREAVES_H
#include "Equipment.h"

class Greaves : public Equipment {
    friend class EquipmentLoader;
public:
    Greaves();
    virtual ~Greaves();
    void specificUpdate();
private:
    void activate();
    void deactivate();
};

#endif	/* GREAVES_H */

