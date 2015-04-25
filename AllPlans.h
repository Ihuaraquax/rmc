/* 
 * File:   AllPlans.h
 * Author: Qb
 *
 * Created on 24 kwiecień 2015, 20:07
 */

#ifndef ALLPLANS_H
#define	ALLPLANS_H
#include "Plan.h"

class AllPlans {
public:
    AllPlans();
    AllPlans(const AllPlans& orig);
    virtual ~AllPlans();
    Plan *getCurrentPlan();
    void display();
    void update();
private:
    Plan **plans;
    int currentPlanIndex;
};

#endif	/* ALLPLANS_H */

