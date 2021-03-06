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
    Explosives();
    void setCoords(double X, double Y);
    void update();
    void executeAgony();
    void save(std::fstream &file);
    void load(std::fstream &file);
    
    static Entity *CreateExplosives(double X, double Y);
private:
};

#endif	/* EXPLOSIVES_H */

