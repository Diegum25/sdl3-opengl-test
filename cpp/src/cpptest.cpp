#include "cpptest.hpp"
#include "cpptest.h"

int TestClass::getCoolInt()
{
    return this->coolInt;
}

extern "C"{
    TestClass* TestClass_Create(){
        return new TestClass();
    };
    int TestClass_GetCoolInt(TestClass* C){
        return C->getCoolInt();
    };
}