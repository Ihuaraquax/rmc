/* 
 * File:   AllDecals.h
 * Author: Qb
 *
 * Created on 19 marzec 2015, 20:29
 */

#ifndef ALLDECALS_H
#define	ALLDECALS_H
#include "Decal.h"
#include "templateList.h"


class AllDecals {
public:
    AllDecals();
    ~AllDecals();
    void update();
    void display();
    void addDecal(Decal *decal);
    void deleteDecal(Decal *decal);
private:
    templateList<Decal> *decalList;
};

#endif	/* ALLDECALS_H */

