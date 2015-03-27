/* 
 * File:   BuffRod.h
 * Author: Qb
 *
 * Created on 12 marzec 2015, 13:20
 */

#ifndef BUFFROD_H
#define	BUFFROD_H
#include "Entity.h"
#include "GenericBuffer.h"

class BuffRod : public Entity {
public:
    BuffRod(GenericBuffer * buff);
    void update();
    void display();
    void setCoords(double X, double Y);
    void executeAgony();
    void save(std::fstream &file);
private:
    GenericBuffer *buffer;
};

#endif	/* BUFFROD_H */

