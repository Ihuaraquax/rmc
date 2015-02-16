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
public:
    Helmet();
    virtual ~Helmet();
    void specificUpdate();
private:

};

#endif	/* HELMET_H */

