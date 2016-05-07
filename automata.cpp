#include "automata.h"

void Automata::push(std::map < char, int > state)
{
    states.push_back(state);
}

void Automata::add_accept(int state)
{
    accepting_states.push_back(state);
}