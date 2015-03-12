/* 
 * File:   TimedBuffer.cpp
 * Author: Qb
 * 
 * Created on 12 marzec 2015, 12:16
 */

#include "TimedBuffer.h"
#include "GenericBuffer.h"

TimedBuffer::TimedBuffer(int type, double value, int time) {
    this->buffTime = time;
    this->buffType = type;
    this->buffValue = value;
}

void TimedBuffer::SetBuffTime(int buffTime) {
    this->buffTime = buffTime;
}

int TimedBuffer::GetBuffTime() const {
    return buffTime;
}