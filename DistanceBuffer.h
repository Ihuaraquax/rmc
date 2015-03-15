/* 
 * File:   DistanceBuffer.h
 * Author: Qb
 *
 * Created on 12 marzec 2015, 12:16
 */

#ifndef DISTANCEBUFFER_H
#define	DISTANCEBUFFER_H
#include "GenericBuffer.h"

class DistanceBuffer : public GenericBuffer {
public:
    DistanceBuffer(int type, double value, double distance);
    int GetModuleTileDistance() const;
    double GetDistance() const;
    void SetDistance(double distance);
    void setCoords(double X, double Y);
    bool isInRange(double X, double Y);
private:
    double distance;
    int moduleTileDistance;
    double X, Y;
};

#endif	/* DISTANCEBUFFER_H */

