#include <algorithm>

#include "automata.h"
#include "output.h"

Automata::Automata()
{
    started = false;
}

void Automata::push(std::map < char, int > state)
{
    states.push_back(state);
}

void Automata::add_accept(std::pair < int, int > state)
{
    accepting_states.push_back(state);
}

bool Automata::start_automata(char move)
{
    for(unsigned i = 0; i < starting_states.size(); ++i)
    {
        current_state = starting_states[i];
        //printf("checking state: %d\n", current_state);
        if(states[current_state].find(move) != states[current_state].end())
        {
            //printf("Found start state: %d\n", current_state);
            started = true;
            return true;
        }
    }
    return false;
}

int Automata::next_state(char move)
{
    if(!started)
    {
        if(!start_automata(move))
        {
            print_error("ERROR: automata not started\n");
        }        
    }
    if(states[current_state].find(move) != states[current_state].end())
    {
        //print_log("Change state with move \'%c\': %d -> ", move, current_state);
        current_state = states[current_state][move];
        //print_log("%d\n", current_state);
        return current_state;
    }
    return -1;
}

int Automata::get_state()
{
    return current_state;
}

int Automata::get_accept()
{
    if(!started)
    {
        return -1;
    }
    for(unsigned i = 0; i < accepting_states.size(); ++i)
    {
        if(accepting_states[i].first == current_state)
        {
            return accepting_states[i].second;
        }
    }
    return -1;
}

void Automata::reset()
{
    started = false;
}

bool Automata::is_started()
{
    return started;
}

void Automata::add_start_state(int start)
{
    starting_states.push_back(start);
}