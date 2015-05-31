/* 
 * File:   AllLightSources.h
 * Author: Qb
 *
 * Created on 23 maj 2015, 21:47
 */

#ifndef ALLLIGHTSOURCES_H
#define	ALLLIGHTSOURCES_H
#include "LightSource.h"
#include <list>

class AllLightSources {
public:
    AllLightSources();
    AllLightSources(const AllLightSources& orig);
    virtual ~AllLightSources();
    void update();
    void display();
    void addSource(LightSource *source);
    void deleteDeadSources();
    void setUseNightvision(bool useNightvision);
private:
    std::list<LightSource*> sources;
    LightSource *nightvision;
    bool useNightvision;
};

#endif	/* ALLLIGHTSOURCES_H */

