#include <map>
#include <vector>


class Automata
{
    int current_state;
    std::vector < std::map < char, int > > states;
    std::vector < int > accepting_states;
    
    public:
    Automata();
    void push(std::map < char, int >);
    void add_accept(int);
    int next_state(char);
    int get_state();
    bool is_accepted();
    void reset();
};