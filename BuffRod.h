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
    BuffRod();
    void update();
    void display();
    void setCoords(double X, double Y);
    void executeAgony();
    void save(std::fstream &file);
    void load(std::fstream &file);    
    void setBuffer(GenericBuffer* buffer);
    
    static Entity *CreateBuffRod(double X, double Y);
    static Entity *CreateBuffRod(double X, double Y, GenericBuffer * buff);
private:
    GenericBuffer *buffer;
};

#endif	/* BUFFROD_H */

