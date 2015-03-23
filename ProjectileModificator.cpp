/* 
 * File:   ProjectileModificator.cpp
 * Author: Qb
 * 
 * Created on 23 marzec 2015, 20:06
 */

#include "ProjectileModificator.h"
#include "Projectile.h"
#include "globalVariables.h"

void ProjectileModificator::modifyProjectile(Entity* projectile)
{
    Projectile *bullet = dynamic_cast<Projectile*>(projectile);
    double *table =Variables::session->getMap()->getCurrentModule()->getModificatorsTable();
    if(table[7] != 0)bullet->setAdditionalDamage(bullet->getDamage()/5, 1);
    if(table[8] != 0)bullet->setAdditionalDamage(bullet->getDamage()/5, 2);
    if(table[9] != 0)bullet->setAdditionalDamage(bullet->getDamage()/5, 3);
    if(table[10] != 0)bullet->setAdditionalDamage(bullet->getDamage()/5, 4);
    if(table[11] != 0)bullet->setDamage(bullet->getDamage() * 2);
    if(table[56] != 0)
    {
        bullet->getCoords()->speedX /=2;
        bullet->getCoords()->speedY /=2;
    }
    if(table[70] != 0 && rand()%100 == 0)bullet->setDamage(0);
    
}
//    normal = 0, 
//    fire = 1,
//    electric = 2,
//    poison = 3,
//    cold = 4,
//    explosive = 5