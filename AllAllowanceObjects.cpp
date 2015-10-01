/* 
 * File:   AllAllowanceObjects.cpp
 * Author: Adiutant
 * 
 * Created on 1 październik 2015, 19:21
 */

#include "AllAllowanceObjects.h"

AllAllowanceObjects::AllAllowanceObjects() {
    this->listSize = 0;
    this->objects = NULL;
}

AllAllowanceObjects::AllAllowanceObjects(const AllAllowanceObjects& orig) {
}

AllAllowanceObjects::~AllAllowanceObjects() {
}

void AllAllowanceObjects::addObject(AllowanceObject* object)
{
    templateList<AllowanceObject> *newObject= new templateList<AllowanceObject>();
    newObject->data = object;
    newObject->next = objects;
    objects = newObject;
    listSize++;
}

void AllAllowanceObjects::deleteObject(AllowanceObject* object)
{
    templateList<AllowanceObject> *toDelete = objects->find(object);
    if(toDelete == objects)
    {
        objects = objects->next;
    }
    else
    {
        templateList<AllowanceObject> *prev = objects->findPrevious(object);
        prev->next = toDelete->next;
    }
    delete toDelete;
    listSize--;
}

AllowanceObject *AllAllowanceObjects::getRandomObject()
{
    AllowanceObject *result = NULL;
    if(listSize > 0)
    {
        int index = rand()%listSize;
        templateList<AllowanceObject> *iterator = objects;
        while(index > 0)
        {
            iterator = iterator->next;
            index--;
        }
        result = iterator->data;
    }
    return result;
}
