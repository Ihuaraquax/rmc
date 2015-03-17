/* 
 * File:   RemoteCharges.h
 * Author: Qb
 *
 * Created on 17 marzec 2015, 21:46
 */

#ifndef REMOTECHARGES_H
#define	REMOTECHARGES_H
#include "Entity.h"

class RemoteCharges : public Entity {
public:
    RemoteCharges(double X, double Y);
    void update();
    void executeAgony();
    void setSignalId(int signalId);
    int getSignalId() const;
private:
    int signalId;
};

#endif	/* REMOTECHARGES_H */

