/* 
 * File:   DoorFactory.h
 * Author: Qb
 *
 * Created on 22 marzec 2015, 12:28
 */

#ifndef DOORFACTORY_H
#define	DOORFACTORY_H

class DoorFactory {
public:
    void static createDoors();
private:
    bool static isRuleApplicable(int x, int y, int rule[5][5]);
};

#endif	/* DOORFACTORY_H */

