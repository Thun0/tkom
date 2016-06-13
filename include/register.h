#ifndef REGISTER_H
#define REGISTER_H

#include "operand.h"

class Register : public Operand
{
public:
    char index;
    char type;  // 32/64 bit
    Register();
    ~Register();
};

#endif