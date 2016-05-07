#include <map>
#include <vector>


class Automata
{
    std::vector < std::map < char, int > > states;
    std::vector < int > accepting_states;
    
    public:
    void push(std::map < char, int >);
    void add_accept(int);
};