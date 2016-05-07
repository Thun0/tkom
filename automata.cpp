#include <algorithm>
#include <cstdio>
#include "automata.h"

Automata::Automata()
{
    current_state = 0;
}

void Automata::push(std::map < char, int > state)
{
    states.push_back(state);
}

void Automata::add_accept(int state)
{
    accepting_states.push_back(state);
}

int Automata::next_state(char move)
{
    if(states[current_state].find(move) != states[current_state].end())
    {
        //printf("Change state with move \'%c\': %d -> ", move, current_state);
        current_state = states[current_state][move];
        //printf("%d\n", current_state);
        return current_state;
    }
    return -1;
}

int Automata::get_state()
{
    return current_state;
}

bool Automata::is_accepted()
{
    return std::find(accepting_states.begin(), accepting_states.end(), current_state) != accepting_states.end();
}

void Automata::reset()
{
    current_state = 0;
}