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
    ExplosiveBarrel(bool isLoad);
    ExplosiveBarrel(double X, double Y, int type);
    void update();
    void executeAgony();
    
    void save(std::fstream &file);
    void load(std::fstream &file);
private:
    int barrelType;
};

#endif	/* EXPLOSIVEBARREL_H */

