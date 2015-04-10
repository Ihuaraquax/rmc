/* 
 * File:   Lock.h
 * Author: Qb
 *
 * Created on 7 kwiecień 2015, 18:57
 */

#ifndef LOCK_H
#define	LOCK_H
#include "Entity.h"

class Lock : public Entity, public UsableObject {
public:
    Lock();
    void update();
    void display();
    void save(std::fstream &savefile);
    void load(std::fstream &savefile);
    void getHit(int damage, int damageType);
    static Entity *CreateLock(double X, double Y);
    void use();
private:
    int keyValue;
};

#endif	/* LOCK_H */

