/* 
 * File:   ValueReader.h
 * Author: Adiutant
 *
 * Created on 5 wrzesień 2015, 18:53
 */

#ifndef VALUEREADER_H
#define	VALUEREADER_H
#include <map>
#include <iostream>


class ValueReader {
public:
    ValueReader();
    ValueReader(const ValueReader& orig);
    virtual ~ValueReader();
    void getValues();
    double getByName(std::string name);
private:
    std::map<std::string, double> valueMap;

};

#endif	/* VALUEREADER_H */

