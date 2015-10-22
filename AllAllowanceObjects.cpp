/* 
 * File:   AllAllowanceObjects.cpp
 * Author: Adiutant
 * 
 * Created on 1 październik 2015, 19:21
 */

#include "AllAllowanceObjects.h"
#include "globalVariables.h"

AllAllowanceObjects::AllAllowanceObjects() {
    this->listSize = 0;
    this->allAllowanceObjects = NULL;
    this->typedAllowanceObjects = new templateList<AllowanceObject>*[Variables::allowancObjectMaxCount];
    typedListSize = new int[Variables::allowancObjectMaxCount];
    for(int i = 0; i < Variables::allowancObjectMaxCount; i++)
    {
        typedAllowanceObjects[i] = NULL;
        typedListSize[i] = 0;
    }
}

AllAllowanceObjects::AllAllowanceObjects(const AllAllowanceObjects& orig) {
}

AllAllowanceObjects::~AllAllowanceObjects() {
}

void AllAllowanceObjects::addObject(AllowanceObject* object)
{
    templateList<AllowanceObject> *newObject= new templateList<AllowanceObject>();
    newObject->data = object;
    newObject->next = allAllowanceObjects;
    allAllowanceObjects = newObject;
    listSize++;
    
    int type = object->getType();
    
    templateList<AllowanceObject> *newTypedObject= new templateList<AllowanceObject>();
    newTypedObject->data = object;
    newTypedObject->next = typedAllowanceObjects[type];
    typedAllowanceObjects[type] = newObject;
    typedListSize[type]++;
}

void AllAllowanceObjects::deleteObject(AllowanceObject* object)
{
    templateList<AllowanceObject> *toDelete = allAllowanceObjects->find(object);
    if(toDelete == allAllowanceObjects)
    {
        allAllowanceObjects = allAllowanceObjects->next;
    }
    else
    {
        templateList<AllowanceObject> *prev = allAllowanceObjects->findPrevious(object);
        prev->next = toDelete->next;
    }
    delete toDelete;
    listSize--;
    
    int type = object->getType();
    
    templateList<AllowanceObject> *typedToDelete = typedAllowanceObjects[type]->find(object);
    if(typedToDelete == typedAllowanceObjects[type])
    {
        typedAllowanceObjects[type] = typedAllowanceObjects[type]->next;
    }
    else
    {
        templateList<AllowanceObject> *prev = typedAllowanceObjects[type]->findPrevious(object);
        prev->next = typedToDelete->next;
    }
    delete typedToDelete;
    typedListSize[type]--;
}

AllowanceObject *AllAllowanceObjects::getRandomObject(int type)
{
    AllowanceObject *result = NULL;
    int size = typedListSize[type];
    if(size > 0)
    {
        int index = rand()%typedListSize[type];
        templateList<AllowanceObject> *iterator = typedAllowanceObjects[type];
        while(index > 0)
        {
            iterator = iterator->next;
            index--;
        }
        if(iterator->data->getType() == type)
        {
            result = iterator->data;
        }
    }
    return result;
}


void AllAllowanceObjects::setUsableTiles()
{
    templateList<AllowanceObject> *temp = allAllowanceObjects;
    while(temp != NULL)
    {
        AllowanceObject * object = dynamic_cast<AllowanceObject*>(temp->data);
        object->setStartingTile();
        object->setUsableTiles();
        temp = temp->next;
    }
}

void AllAllowanceObjects::update()
{
    templateList<AllowanceObject> *temp = this->allAllowanceObjects;
    while(temp != NULL)
    {
        temp->data->specificUpdate();
        temp = temp -> next;
    }
}