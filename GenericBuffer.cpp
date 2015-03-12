/* 
 * File:   GenericBuffer.cpp
 * Author: Qb
 * 
 * Created on 12 marzec 2015, 12:20
 */

#include "GenericBuffer.h"
GenericBuffer::GenericBuffer(){
    
}

int GenericBuffer::GetBuffValue() const {
    return buffValue;
}

int GenericBuffer::GetBuffType() const {
    return buffType;
}