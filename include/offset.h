#ifndef OFFSET_H
#define OFFSET_H

#include "operand.h"

class Offset : public Operand
{
public:
    int value;
    Offset();
    ~Offset();
};

#endif