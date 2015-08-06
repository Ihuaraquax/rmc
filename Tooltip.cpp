/* 
 * File:   Tooltip.cpp
 * Author: Qb
 * 
 * Created on 22 czerwiec 2015, 22:24
 */
#include "Tooltip.h"
#include "globalVariables.h"
#include "TextDisplayer.h"

Tooltip::Tooltip() {
    coords = new Coordinates();
    statName = new std::string*[4];
    statName[0] = new std::string[8];
    statName[0][0] = "DMG";
    statName[0][1] = "SPD";
    statName[0][2] = "ACC";
    statName[0][3] = "CRTCH";
    statName[0][4] = "CRTDMG";
    statName[0][5] = "RLD";
    statName[0][6] = "TYP";
    statName[0][7] = "SPECIAL";
    statName[1] = new std::string[3];
    statName[1][0] = "ARMOR";
    statName[1][1] = "ENERGY";
    statName[1][2] = "DESC";
    image = Variables::images->getByName("weaponTooltip");
    image->state = UI;
    this->isDisplay = false;
    baseValue = NULL;
    currentValue = NULL;
}

Tooltip::Tooltip(const Tooltip& orig) {
}

Tooltip::~Tooltip() {
    image = NULL;
    delete statName[0];
    delete []statName;
}
void Tooltip::display()
{
    if(isDisplay)
    {
        if(image != NULL)
        {
            image->display(coords);
            TextDisplayer::displayText(coords->X + 75, coords->Y + 5, name);
            switch(type)
            {
                case 0:
                    this->displayWeaponTooltips();
                    break;
                case 1:
                    this->displayEquipmentTooltips();
                    break;
            }
        }
        isDisplay = false;
    }
}
void Tooltip::displayWeaponTooltips()
{
    for(int i = 0; i < 8; i++)
    {
        TextDisplayer::displayTextToLeft(coords->X + 2, coords->Y + (23 *(i+1)+4),statName[0][i]);
        TextDisplayer::displayInt(coords->X + 125, coords->Y + (23 *(i+1)+4),baseValue[i]);
    }
}
void Tooltip::displayEquipmentTooltips()
{
    for(int i = 0; i < 3; i++)
    {
        TextDisplayer::displayTextToLeft(coords->X + 2, coords->Y + (23 *(i+1)+4),statName[1][i]);
        TextDisplayer::displayInt(coords->X + 125, coords->Y + (23 *(i+1)+4),baseValue[i]);
    }
}
void Tooltip::displaySkillTooltip()
{
    
}
void Tooltip::displayAttributeTooltip()
{
    
}
bool Tooltip::isDisplaing()
{

}
void Tooltip::setImage(Image *image)
{
    this->image = image;
    image->state = UI;
}
void Tooltip::setBaseValues(int *values)
{
    if(baseValue != NULL)delete []baseValue;
    int counter;
    switch(type)
    {
        case 0: counter = 8;
            break;
        case 1: counter = 3;
            break;
    }
    baseValue = new int[counter];
    for(int i = 0; i < counter; i++)baseValue[i] = values[i];
}
void Tooltip::setCurrentValues(int *values)
{
    if(currentValue != NULL)delete []currentValue;
    int counter;
    switch(type)
    {
        case 0: counter = 8;
            break;
    }
    currentValue = new int[counter];
    for(int i = 0; i < counter; i++)currentValue[i] = values[i];
}
void Tooltip::calculateCoords()
{
    coords->X = Variables::mouseCoords->X;
    coords->Y = Variables::mouseCoords->Y;
    if(coords->X + 150 > Variables::RES_WIDTH)coords->X -= 150;
    int yDelta = 200;
    if(type == 1)yDelta = 90;
    if(coords->Y + yDelta > Variables::RES_HEIGHT)coords->Y -= yDelta;
}

void Tooltip::setDisplay(bool Display) {
    isDisplay = Display;
}

void Tooltip::setType(int type)
{
    this->type = type;
}

void Tooltip::setName(std::string name) {
    this->name = name;
}

void Tooltip::setWeapon(Weapon* weapon)
{
    Variables::session->getTooltip()->calculateCoords();
    Variables::session->getTooltip()->setType(0);
    Variables::session->getTooltip()->setName(weapon->getName());
    Variables::session->getTooltip()->setImage(Variables::images->getByName("weaponTooltip"));
    int baseValues[8];
    baseValues[0] = weapon->damage;
    baseValues[1] = weapon->cooldown;
    baseValues[2] = weapon->targetSizeIncrement;
    baseValues[3] = weapon->criticalChance;
    baseValues[4] = weapon->criticalDamage;
    baseValues[5] = weapon->reloadSpeed;
    baseValues[6] = weapon->damageType;
    baseValues[7] = 0;
    Variables::session->getTooltip()->setBaseValues(baseValues);
    Variables::session->getTooltip()->setDisplay(true);
}

void Tooltip::setEquipment(Equipment* equipment)
{
    Variables::session->getTooltip()->calculateCoords();
    Variables::session->getTooltip()->setType(1);
    Variables::session->getTooltip()->setName(equipment->getName());
    Variables::session->getTooltip()->setImage(Variables::images->getByName("equipmentTooltip"));
    int baseValues[3];
    baseValues[0] = equipment->getArmor();
    baseValues[1] = equipment->getEnergyConsumption();
    baseValues[2] = 0;
    Variables::session->getTooltip()->setBaseValues(baseValues);
    Variables::session->getTooltip()->setDisplay(true);
}
void Tooltip::setUsableItem(UsableItem* usableItem)
{
    Variables::session->getTooltip()->calculateCoords();
    Variables::session->getTooltip()->setType(1);
    Variables::session->getTooltip()->setName(usableItem->getName());
    Variables::session->getTooltip()->setImage(Variables::images->getByName("equipmentTooltip"));
    int baseValues[3];
    baseValues[0] = 0;
    baseValues[1] = 0;
    baseValues[2] = 0;
    Variables::session->getTooltip()->setBaseValues(baseValues);
    Variables::session->getTooltip()->setDisplay(true);
}