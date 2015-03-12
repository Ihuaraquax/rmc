/* 
 * File:   TimedBuffer.h
 * Author: Qb
 *
 * Created on 12 marzec 2015, 12:16
 */

#ifndef TIMEDBUFFER_H
#define	TIMEDBUFFER_H
#include "GenericBuffer.h"

class TimedBuffer : public GenericBuffer {
public:
    TimedBuffer(int type, double value, int time);
    void SetBuffTime(int buffTime);
    int GetBuffTime() const;
private:
    int buffTime;
};

#endif	/* TIMEDBUFFER_H */

