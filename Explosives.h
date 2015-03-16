/* 
 * File:   Explosives.h
 * Author: Qb
 *
 * Created on 16 marzec 2015, 17:35
 */

#ifndef EXPLOSIVES_H
#define	EXPLOSIVES_H
#include "Entity.h"
class Explosives : public Entity{
public:
    Explosives(double X, double Y);
    void update();
    void executeAgony();
private:
};

#endif	/* EXPLOSIVES_H */

