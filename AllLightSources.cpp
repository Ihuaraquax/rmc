/* 
 * File:   AllLightSources.cpp
 * Author: Qb
 * 
 * Created on 23 maj 2015, 21:47
 */

#include "AllLightSources.h"

AllLightSources::AllLightSources() {
}

AllLightSources::AllLightSources(const AllLightSources& orig) {
}

AllLightSources::~AllLightSources() {
}

void AllLightSources::addSource(LightSource* source)
{
    sources.push_front(source);
}

void AllLightSources::display()
{
    for(std::list<LightSource*>::iterator i = sources.begin(); i != sources.end(); ++i)
    {
        LightSource *temp = *i;
        temp->display();
    }
}

void AllLightSources::update()
{
    for(std::list<LightSource*>::iterator i = sources.begin(); i != sources.end(); ++i)
    {
        LightSource *temp = *i;
        temp->update();
    }
    this->deleteDeadSources();
}

void AllLightSources::deleteDeadSources()
{
    std::list<LightSource*>::iterator i = sources.begin();
    while (i != sources.end())
    {
        LightSource *toDelete = *i;
        if(toDelete != NULL)if(toDelete->getTime() == 0)
        {
            toDelete->decreaseTileLightValue();
            sources.erase(i++);
            delete toDelete;
        }
        i++;
    }
}

void AllLightSources::setUseNightvision(bool useNightvision) {
    this->useNightvision = useNightvision;
}