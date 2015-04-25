/* 
 * File:   AllPlans.cpp
 * Author: Qb
 * 
 * Created on 24 kwiecień 2015, 20:07
 */

#include "AllPlans.h"
#include "globalVariables.h"

AllPlans::AllPlans() {
    plans = new Plan*[10];
    for(int i = 0; i < 10; i++)plans[i] = new Plan();
    currentPlanIndex = 0;
}

AllPlans::AllPlans(const AllPlans& orig) {
}

AllPlans::~AllPlans() {
    for(int i = 0; i < 10; i++)delete plans[i];
    delete []plans;
}

void AllPlans::display()
{
    if(Variables::substate == game)plans[currentPlanIndex]->displayCurrent();
    else if(Variables::substate == plan)plans[currentPlanIndex]->displayAll();
}

void AllPlans::update()
{
    plans[currentPlanIndex];
}

Plan *AllPlans::getCurrentPlan()
{
    return plans[currentPlanIndex];
}