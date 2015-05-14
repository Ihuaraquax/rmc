/* 
 * File:   Plan.h
 * Author: Qb
 *
 * Created on 24 kwiecień 2015, 20:22
 */

#ifndef PLAN_H
#define	PLAN_H
#include "PlanStep.h"
#include "templateList.h"
#include <fstream>

class Plan {
public:
    Plan();
    Plan(const Plan& orig);
    virtual ~Plan();
    void displayCurrent();
    void displayAll();
    
    void createStepAtMouse();
    void destroyStepAtMouse();
    void addStep(PlanStep *step);
    void deleteStep(PlanStep *step);
    void changeCurrentStep(bool next);
    PlanStep* getCurrentStep() const;
    void save(std::fstream &savefile);
    void load(std::fstream &savefile);
private:
    templateList<PlanStep> *stepList;
    PlanStep *currentStep;
};

#endif	/* PLAN_H */

