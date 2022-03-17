#ifndef VALUETYPE_H_INCLUDED
#define VALUETYPE_H_INCLUDED

#include <string>
#include "Entity.h"
#include "Utility.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

class CompleteValue
{
    public:
    static int EntitySelected;
    int Value=0;
    char ValueType=0;
    char ValueOperator=0;
    int ValueTypeValue=0;
    char m_EntitySelected=-1;

    void operator=(const std::string &STR);
     CompleteValue(std::string STR);
    void getInt(int &ReturnedInt,int EntitySelected);
    void getInt(char &ReturnedInt,int EntitySelected);
    int returnInt(int EntitySelected);
    operator int();

};
#endif // VALUETYPE_H_INCLUDED
