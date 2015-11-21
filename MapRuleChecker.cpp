/* 
 * File:   MapRuleChecker.cpp
 * Author: Adiutant
 * 
 * Created on 21 listopad 2015, 15:36
 */

#include "MapRuleChecker.h"
#include "globalVariables.h"

// -1 cokolwiek
//  0 brak ściany
//  1 ściana
bool MapRuleChecker::applyStandarizedRule(int x, int y, int rule[5][5])
{
    bool result = true;    
    ModuleTile **temp = Variables::session->getMap()->getCurrentModule()->getModuleTiles();
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            int X = x+i-2, Y = y+j-2;
            if(X >= 0 && X < Variables::tilesPerRoom && Y >= 0 && Y < Variables::tilesPerRoom)
            {
                if(rule[i][j] == 0 && temp[X * Variables::tilesPerRoom + Y]->getObstacle() != NULL)
                {
                    result = false;
                    break;
                }
                if(rule[i][j] == 1 && temp[X * Variables::tilesPerRoom + Y]->getObstacle() == NULL)
                {
                    result = false;
                    break;
                }
            }
            if(result == false)break;
        }
    }
    return result;
}

bool MapRuleChecker::applyAnyRule(int x, int y, int **rule, int ruleSizeX, int ruleSizeY)
{
    bool result = true;    
    ModuleTile **temp = Variables::session->getMap()->getCurrentModule()->getModuleTiles();
    for(int i = 0; i < ruleSizeX; i++)
    {
        for(int j = 0; j < ruleSizeY; j++)
        {
            int X = x+i-(ruleSizeX/2), Y = y+j-(ruleSizeY/2);
            if(X >= 0 && X < Variables::tilesPerRoom && Y >= 0 && Y < Variables::tilesPerRoom)
            {
                if(rule[i][j] == 0 && temp[X * Variables::tilesPerRoom + Y]->getObstacle() != NULL)
                {
                    result = false;
                    break;
                }
                if(rule[i][j] == 1 && temp[X * Variables::tilesPerRoom + Y]->getObstacle() == NULL)
                {
                    result = false;
                    break;
                }
            }
            if(result == false)break;
        }
    }
    return result;
}