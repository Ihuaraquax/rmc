/* 
 * File:   AllPlans.h
 * Author: Qb
 *
 * Created on 24 kwiecień 2015, 20:07
 */

#ifndef ALLPLANS_H
#define	ALLPLANS_H
#include "Plan.h"
#include <fstream>

class AllPlans {
public:
    AllPlans();
    AllPlans(const AllPlans& orig);
    virtual ~AllPlans();
    Plan *getCurrentPlan();
    void display();
    void update();
    void save(std::fstream &savefile);
    void load(std::fstream &savefile);
private:
    Plan **plans;
    int currentPlanIndex;
};

#endif	/* ALLPLANS_H */

