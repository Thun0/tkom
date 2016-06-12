#ifndef OPERAND_H
#define OPERAND_H

#include <string>

class Operand
{
    std::string type;
    std::string value;
    Operand();
public:
    Operand(std::string, std::string);
    ~Operand();
};

#endif