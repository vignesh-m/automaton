#include "nfa.hpp"
#include <iostream>

/*
    NFA with transition function as a map from characters to states.
*/

// internal functions
void NFA::advance(int state, char c, nfa_set &new_states){
    for(int new_state: transitions[state][c]){
        new_states[new_state] = 1;
    }
}
void NFA::advance_set(nfa_set reached_sets, char c, nfa_set &new_states){
    for(int i = 0; i < nstates; i++){
        if(reached_sets[i]) advance(i, c, new_states);
    }
}
void NFA::epsilon_closure(int state, nfa_set &closure){
    closure[state] = 1;
    for(int new_state: transitions[state][(char)0])
        if(!closure[new_state])
            epsilon_closure(new_state, closure);
}
void NFA::epsilon_closure_set(nfa_set reached_sets, nfa_set &closure){
    for(int i = 0; i < nstates; i++){
        if(reached_sets[i]) epsilon_closure(i, closure);
    }
}

void print_nfa_set(nfa_set s){
    for(int i = 0; i < MAX_NFA_STATES; i++){
        if(s[i]) std::cout<<i<<" ";
    }
    std::cout<<"\n";
}

// evaluate NFA on s
int NFA::accept(std::string s){
    // current_states[i] = 1 if the state is reached before c
    nfa_set current_states;
    // init to start_states
    for(int state: start_states)
        current_states[state] = 1;
    epsilon_closure_set(current_states, current_states);
    for(char c: s){
        // NOTE can we make do without a copy?
        nfa_set new_states = nfa_set();
        advance_set(current_states, c, new_states);
        // NOTE better copy?
        for(int i = 0; i < nstates; i++)
            current_states[i] = new_states[i];
        epsilon_closure_set(current_states, current_states);
    }
    for(int i = 0; i < nstates; i++){
        if(states[i].is_final && current_states[i])
            return true;
    }
    return false;
}

// NFA construction helpers
void NFA::add_transition(int from, int to, char c){
    if(transitions[from].count(c))
        transitions[from][c].push_back(to);
    else
        transitions[from][c] = vi(1,to);
}
void NFA::make_final(int state){
    states[state].is_final = 1;
}
void NFA::make_start(int state){
    if(std::find(start_states.begin(), start_states.end(), state) == start_states.end())
        start_states.push_back(state);
}

// simple tester
int testNFA(std::string s){
    NFA test(3);
    test.make_final(2);
    test.make_start(0);
    test.add_transition(0, 1, (char)0);
    test.add_transition(0,0,'a');
    test.add_transition(0,2,'a');
    test.add_transition(0,1,'c');
    test.add_transition(1,2,'b');
    return test.accept(s);
}
