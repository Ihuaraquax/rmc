/* 
 * File:   AllDecals.cpp
 * Author: Qb
 * 
 * Created on 19 marzec 2015, 20:29
 */

#include "AllDecals.h"

AllDecals::AllDecals() {
    decalList = NULL;
}

AllDecals::~AllDecals()
{
    
    templateList<Decal> *decals = this->decalList;
    while(decals != NULL)
    {
        templateList<Decal> *toDelete = decals;
        decals = decals->next;
        delete toDelete->data;
        delete toDelete;
    }
}

void AllDecals::update()
{
    templateList<Decal> *decals = this->decalList;
    while(decals != NULL)
    {
        decals->data->update();
        decals = decals->next;
    }
}
void AllDecals::display()
{
    
    templateList<Decal> *decals = this->decalList;
    while(decals != NULL)
    {
        decals->data->display();
        decals = decals->next;
    }
}
void AllDecals::addDecal(Decal *decal)
{
    templateList<Decal> *newDecal = new templateList<Decal>();
    newDecal->data = decal;
    newDecal->next = decalList;
    decalList = newDecal;
}
void AllDecals::deleteDecal(Decal *decal)
{
    templateList<Decal> *toDelete = decalList->find(decal);
    if(toDelete == decalList)
    {
        decalList = decalList->next;
    }
    else
    {
        templateList<Decal> *prev = decalList->findPrevious(decal);
        prev->next = toDelete->next;
    }
    delete toDelete->data;
    delete toDelete;
}