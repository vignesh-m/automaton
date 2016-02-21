#include <iostream>
#include <string>
using namespace std;

#include "nfa.hpp"

int main(int argc, char *argv[]) {
    cout<<"Hello\n";
    string s;
    while(cin>>s){
        cout<<testNFA(s)<<"\n";
    }
    return 0;
}
