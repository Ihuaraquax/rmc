/* 
 * File:   ExplosiveBarrel.h
 * Author: Qb
 *
 * Created on 16 marzec 2015, 16:46
 */

#ifndef EXPLOSIVEBARREL_H
#define	EXPLOSIVEBARREL_H
#include "Entity.h"

class ExplosiveBarrel : public Entity {
public:
    ExplosiveBarrel();
    void setCoords(double X, double Y);
    void update();
    void executeAgony();
    
    void save(std::fstream &file);
    void load(std::fstream &file);
    
    static Entity *CreateBarrel(double X, double Y);
private:
    int barrelType;
};

#endif	/* EXPLOSIVEBARREL_H */

