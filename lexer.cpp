#include <cstdio>
#include <map>

#include "automata.h"

enum Type
{
    ADDRESS = 1,
    OPCODE,
    HEX_NUMBER,
    REGISTER,
    COMMENT,
    OFFSET,
    MEMORY_ACCESS,
    ERROR
};

Automata address_automata;

void init_address_automata()
{
    std::map < char, int > state0;
    state0['0'] = 0;
    state0['1'] = 0;
    state0['2'] = 0;
    state0['3'] = 0;
    state0['4'] = 0;
    state0['5'] = 0;
    state0['6'] = 0;
    state0['7'] = 0;
    state0['8'] = 0;
    state0['9'] = 0;
    state0['a'] = 0;
    state0['b'] = 0;
    state0['c'] = 0;
    state0['d'] = 0;
    state0['e'] = 0;
    state0['f'] = 0;
    state0[':'] = 1;
    address_automata.push(state0);
    address_automata.add_accept(1);
}

int main()
{
    return 0;
}