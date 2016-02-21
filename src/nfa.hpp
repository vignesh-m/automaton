/*
    NFA with transition function as a map from characters to states.
*/
#ifndef __AUTOMATON_NFA__
#define __AUTOMATON_NFA__

#include <vector>
#include <map>
#include <string>
#include <bitset>

#define EPS 0 // char 0 means epsilon transitions
struct state{
    int is_final; // true if final state
};
typedef std::map< char,std::vector<int> > transition;

const int MAX_NFA_STATES = 20;
typedef std::bitset<MAX_NFA_STATES> nfa_set;
typedef std::vector<state> state_vector;
typedef std::vector<int> vi;
class NFA{
private:


    void advance(int , char , nfa_set&);
    void advance_set(nfa_set , char , nfa_set&);
    void epsilon_closure(int state, nfa_set &closure);
    void epsilon_closure_set(nfa_set reached_sets, nfa_set &closure);

public:
    // TODO move to private
    // transitions contains map of next state indices for each state
    std::vector<transition> transitions;
    // number of states
    int size;
    // list of states
    state_vector states;
    // list of start state indices.
    vi start_states;

    // main evaluation function
    int accept(std::string s);

    // constructors
    NFA(state_vector _states, std::vector<transition> _transitions, std::vector<int> _start_states){
        states = _states;
        transitions = _transitions;
        start_states = _start_states;
        size = states.size();
    }
    NFA(int n){
        states = state_vector(n,(state){0});
        transitions = std::vector<transition>(n);
        start_states = vi();
        size = n;
    }
    void add_transition(int from, int to, char c);
    void make_final(int state);
    void make_start(int state);
};
int testNFA(std::string);
#endif
