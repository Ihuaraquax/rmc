/* 
 * File:   UsableItemLoader.h
 * Author: Qb
 *
 * Created on 23 luty 2015, 19:00
 */

#ifndef USABLEITEMLOADER_H
#define	USABLEITEMLOADER_H
#include "UsableItem.h"
#include <iostream>

class UsableItemLoader {
public:
    static void loadItem(UsableItem *item, int type);
    static std::string loadItemPath(int type);
private:
};

#endif	/* USABLEITEMLOADER_H */

