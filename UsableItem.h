/* 
 * File:   UsableItem.h
 * Author: Qb
 *
 * Created on 22 luty 2015, 13:51
 */

#ifndef USABLEITEM_H
#define	USABLEITEM_H
#include <iostream>

class UsableItem {
    friend class UsableItemLoader;
public:
    UsableItem();
    virtual ~UsableItem();
    void activate();
    int getCharges() const;
    std::string getImagePath() const;
private:
    int action;
    std::string imagePath;
    int charges;
};

#endif	/* USABLEITEM_H */

