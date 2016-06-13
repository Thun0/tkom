#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <vector>

#include "operand.h"

class Instruction
{
public:
    std::string name;
    int address;
    int opcode;
    std::vector<Operand*> operands;
};

#endif