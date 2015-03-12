/* 
 * File:   MonsterLoader.h
 * Author: Qb
 *
 * Created on 9 marzec 2015, 18:23
 */

#ifndef MONSTERLOADER_H
#define	MONSTERLOADER_H
#include "Entity.h"

class MonsterLoader {
public:
    void static loadMonster(Entity *entity, int type, int modifier);
private:
};

#endif	/* MONSTERLOADER_H */

