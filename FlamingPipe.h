/* 
 * File:   FlamingPipe.h
 * Author: Adiutant
 *
 * Created on 23 listopad 2015, 23:18
 */

#ifndef FLAMINGPIPE_H
#define	FLAMINGPIPE_H
#include "Entity.h"

class FlamingPipe : public Entity {
public:
    FlamingPipe();
    FlamingPipe(const FlamingPipe& orig);
    virtual ~FlamingPipe();
    void display();
    void update();
    static Entity* getFlamingPipe(double X, double Y);
private:

};

#endif	/* FLAMINGPIPE_H */

