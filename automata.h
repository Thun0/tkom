#include <map>
#include <vector>

class Automata
{
    int current_state;
    bool started;
    std::vector < std::map < char, int > > states;
    std::vector < std::pair < int, int > > accepting_states;
    std::vector < int > starting_states;
    bool start_automata(char);
    
    public:
    Automata();
    void push(std::map < char, int >);
    void add_accept(std::pair < int, int >);
    void add_start_state(int);
    int next_state(char);
    int get_state();
    int get_accept();
    void reset();
};