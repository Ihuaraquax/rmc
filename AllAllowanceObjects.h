/* 
 * File:   AllAllowanceObjects.h
 * Author: Adiutant
 *
 * Created on 1 październik 2015, 19:21
 */

#ifndef ALLALLOWANCEOBJECTS_H
#define	ALLALLOWANCEOBJECTS_H
#include "templateList.h"
#include "AllowanceObject.h"

class AllAllowanceObjects {
public:
    AllAllowanceObjects();
    AllAllowanceObjects(const AllAllowanceObjects& orig);
    virtual ~AllAllowanceObjects();
    void addObject(AllowanceObject *object);
    void deleteObject (AllowanceObject *toDelete);
    AllowanceObject *getRandomObject(int type);
    void setUsableTiles();
private:
    templateList<AllowanceObject> *allAllowanceObjects;
    templateList<AllowanceObject> **typedAllowanceObjects;
    int listSize;
    int *typedListSize;
};

#endif	/* ALLALLOWANCEOBJECTS_H */

