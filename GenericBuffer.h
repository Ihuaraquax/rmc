/* 
 * File:   GenericBuffer.h
 * Author: Qb
 *
 * Created on 12 marzec 2015, 12:20
 */

#ifndef GENERICBUFFER_H
#define	GENERICBUFFER_H

class GenericBuffer {
public:
    GenericBuffer();
    int GetBuffValue() const;
    int GetBuffType() const;
protected:
    int buffType;
    double buffValue;
};

#endif	/* GENERICBUFFER_H */

