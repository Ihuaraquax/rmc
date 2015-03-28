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
    RemoteCharges(bool isLoad);
    RemoteCharges(double X, double Y);
    void update();
    void executeAgony();
    void setSignalId(int signalId);
    int getSignalId() const;
    void save(std::fstream &file);
    void load(std::fstream &file);
private:
    int signalId;
};

#endif	/* REMOTECHARGES_H */

