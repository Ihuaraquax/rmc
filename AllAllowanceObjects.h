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
    AllowanceObject *getRandomObject();
private:
    templateList<AllowanceObject> *objects;
    int listSize;
};

#endif	/* ALLALLOWANCEOBJECTS_H */

