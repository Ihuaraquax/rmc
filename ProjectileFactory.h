/* 
 * File:   ProjectileFactory.h
 * Author: Qb
 *
 * Created on 4 marzec 2015, 20:02
 */

#ifndef PROJECTILEFACTORY_H
#define	PROJECTILEFACTORY_H
#include "Entity.h"

class ProjectileFactory {
public:
    static Entity *provideProjectile(int weaponId, int weaponModificator);
private:

};

#endif	/* PROJECTILEFACTORY_H */

