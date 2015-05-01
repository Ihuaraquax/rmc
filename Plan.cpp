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
    double mouseX = Variables::mouse_x * (1/Variables::ScaleX) + Variables::offsetX - Variables::tileSize/2;
    double mouseY = Variables::mouse_y * (1/Variables::ScaleY) + Variables::offsetY - Variables::tileSize/2;
    if(mouseX >= 0 && mouseY >= 0)
    {
        int moduleX = mouseX / (Variables::tileSize * Variables::tilesPerRoom);
        int moduleY = mouseY / (Variables::tileSize * Variables::tilesPerRoom);
        if(moduleX >= 0 && moduleY >= 0 && moduleX < Variables::session->getMap()->getModulesTableSize() && moduleY < Variables::session->getMap()->getModulesTableSize())
        {
            PlanStep *step = new PlanStep();
            step->setCoords(mouseX, mouseY, moduleX, moduleY);
            this->addStep(step);
        }
    }
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
        this->changeCurrentStep(true);
        if(currentStep == NULL)
        {
            currentStep = step;
            this->changeCurrentStep(false);
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
    if(stepList == NULL)currentStep = NULL;
}

void Plan::changeCurrentStep(bool next)
{
    if(next)
    {
        if(stepList->data == currentStep)currentStep = NULL;
        else
        {
            if(stepList->findPrevious(currentStep) != NULL || stepList->findPrevious(currentStep) != stepList)currentStep = stepList->findPrevious(currentStep)->data;
            else currentStep = NULL;
        }
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
