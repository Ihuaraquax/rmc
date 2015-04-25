/* 
 * File:   Plan.cpp
 * Author: Qb
 * 
 * Created on 24 kwiecień 2015, 20:22
 */

#include "Plan.h"
#include "globalVariables.h"
#include "CollisionDetector.h"

Plan::Plan() {
    currentStep = NULL;
    stepList = NULL;
}

Plan::Plan(const Plan& orig) {
}

Plan::~Plan() {
}

void Plan::displayCurrent()
{
    if(currentStep != NULL)currentStep->display();
}

void Plan::displayAll()
{
    templateList<PlanStep> *temp = stepList;
    while(temp != NULL)
    {
        temp->data->display();
        if(temp->next != NULL)temp->data->displayPathToNext(temp->next->data->getCoords());
        temp = temp -> next;
    }
}

void Plan::createStepAtMouse()
{
    PlanStep *step = new PlanStep();
    step->setCoords((Variables::mouse_x) * (1/Variables::ScaleX) + Variables::offsetX - Variables::tileSize/2,
            (Variables::mouse_y) * (1/Variables::ScaleX) + Variables::offsetY - Variables::tileSize/2,
            0, 0);
    this->addStep(step);
}

void Plan::destroyStepAtMouse()
{
    Coordinates *coords = new Coordinates();
    coords->X = (Variables::mouse_x) * (1/Variables::ScaleX) + Variables::offsetX - Variables::tileSize/2;
    coords->Y = (Variables::mouse_y) * (1/Variables::ScaleX) + Variables::offsetY - Variables::tileSize/2;
    coords->width = 1;
    coords->height = 1;
    PlanStep *target = NULL;
    templateList<PlanStep> *temp = stepList;
    while(temp != NULL)
    {
        if(CollisionDetector::isBasicCollision(coords, temp->data->getCoords()))target = temp->data;
        temp = temp -> next;
    }
    if(target != NULL)this->deleteStep(target);
}

void Plan::addStep(PlanStep* step)
{
    templateList<PlanStep> *newStep = new templateList<PlanStep>();
    newStep->data = step;
    newStep->next = stepList;
    stepList = newStep;
    if(currentStep == NULL)currentStep = step;
    
}

void Plan::deleteStep(PlanStep* step)
{
    if(step == currentStep)
    {
        this->changeCurrentStep(false);
        if(currentStep == NULL)
        {
            currentStep = step;
            this->changeCurrentStep(true);
        }
    }
    if(stepList->data == step)
    {
        templateList<PlanStep> *temp = stepList;
        stepList = stepList -> next;
        delete temp;
    }
    else
    {
        templateList<PlanStep> *temp = stepList->findPrevious(step);
        templateList<PlanStep> *listToDelete = temp->next;
        temp->next = listToDelete->next;
        delete listToDelete;
    }
}

void Plan::changeCurrentStep(bool next)
{
    if(next)
    {
        if(stepList->findPrevious(currentStep) != NULL)currentStep = stepList->findPrevious(currentStep)->data;
        else currentStep = NULL;
    }
    else 
    {
        if(stepList->find(currentStep)->next != NULL)
        {
            currentStep = stepList->find(currentStep)->next->data;
        }
        else currentStep = NULL;
    }
}

PlanStep* Plan::getCurrentStep() const {
    return currentStep;
}
