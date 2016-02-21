#include "nfa.hpp"
#include <iostream>
#include "prettyprint.hpp"

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
    for(int i = 0; i < size; i++){
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
    for(int i = 0; i < size; i++){
        if(reached_sets[i]) epsilon_closure(i, closure);
    }
    // std::cout<<"eps closure of "<<reached_sets<<" is "<<closure<<"\n";
}

// evaluate NFA on s
int NFA::accept(std::string s){
    // current_states[i] = 1 if the state is reached before c
    nfa_set current_states;
    // init to start_states
    for(int state: start_states)
        current_states[state] = 1;
    // NOTE will this be buggy?
    epsilon_closure_set(current_states, current_states);
    for(char c: s){
        // NOTE can we make do without a copy?
        nfa_set new_states = nfa_set();
        advance_set(current_states, c, new_states);
        // NOTE better copy?
        for(int i = 0; i < size; i++)
            current_states[i] = new_states[i];
        epsilon_closure_set(current_states, current_states);
    }
    // std::cout<<" at end of processing "<<current_states<<"\n";
    for(int i = 0; i < size; i++){
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

// NFA operations
NFA NFA_Op::branch(NFA n1, NFA n2){
    return n1;
}

// simple tester
int testNFA(std::string s){
    NFA test(4); // [a|b]*
    test.make_final(3);
    test.make_start(0);
    test.add_transition(0, 1, (char)0);
    test.add_transition(0, 3, (char)0);
    test.add_transition(2, 1, (char)0);
    test.add_transition(2, 3, (char)0);
    test.add_transition(1,2,'a');
    test.add_transition(1,2,'b');
    // std::cout<<test.transitions<<"\n";
    return test.accept(s);
}
