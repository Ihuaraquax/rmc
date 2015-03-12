/* 
 * File:   DistanceBuffer.cpp
 * Author: Qb
 * 
 * Created on 12 marzec 2015, 12:16
 */

#include "DistanceBuffer.h"
#include "GenericBuffer.h"
#include "globalVariables.h"

DistanceBuffer::DistanceBuffer(int type, double value, double distance) {
    this->buffType = type;
    this->buffValue = value;
    this->distance = distance;
    this->moduleTileDistance = ceil(distance / Variables::tileSize);
}
int DistanceBuffer::GetModuleTileDistance() const {
    return moduleTileDistance;
}

double DistanceBuffer::GetDistance() const {
    return distance;
}