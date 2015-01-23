/* 
 * File:   Coordinates.h
 * Author: Qb
 *
 * Created on 4 listopad 2014, 22:27
 */

#ifndef COORDINATES_H
#define	COORDINATES_H

class Coordinates {
public:
    Coordinates();
    virtual ~Coordinates();
    double X, Y;
    double angle;
    double width;
    double height;
    double speedX, speedY;
private:
};

#endif	/* COORDINATES_H */

