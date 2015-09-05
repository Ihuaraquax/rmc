/* 
 * File:   ValueReader.cpp
 * Author: Adiutant
 * 
 * Created on 5 wrzesień 2015, 18:53
 */

#include "ValueReader.h"
#include <fstream>

ValueReader::ValueReader() {
    getValues();
}

ValueReader::ValueReader(const ValueReader& orig) {
}

ValueReader::~ValueReader() {
}

double ValueReader::getByName(std::string name)
{
    int value = valueMap[name];
    return value;
}

void ValueReader::getValues()
{
    std::fstream file;
    file.open("fixtures/valuesMap.txt", std::ios::in);
    std::string name;
    double value;
    while(!file.eof())
    {
        file >> name >> value;
        valueMap.insert(std::pair<std::string, double>(name, value));
    }
}

