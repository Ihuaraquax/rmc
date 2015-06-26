/* 
 * File:   UsableItem.h
 * Author: Qb
 *
 * Created on 22 luty 2015, 13:51
 */

#ifndef USABLEITEM_H
#define	USABLEITEM_H
#include <iostream>
#include <fstream>

class UsableItem {
    friend class UsableItemLoader;
public:
    UsableItem();
    virtual ~UsableItem();
    void activate();
    int getCharges() const;
    std::string getImagePath() const;
    int getAction() const;
    void save(std::fstream &file);
    void load(std::fstream &file);
    std::string getName() const;
private:
    std::string name;
    bool getPointedCoords(double &X, double &Y);
    bool isTileNearToPlayer(double X, double Y);
    int action;
    std::string imagePath;
    int charges;
    int additionalData;
};

#endif	/* USABLEITEM_H */

