#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


void buildWords(string partial, const string& in, string floating, const set<string>& dict, set<string>& results, int index);
bool matchesConstraints(const string& word, const string& in, string floating);

// definition of primary wordle function
set<string> wordle(
    const string& in,
    const string& floating,
    const set<string>& dict)
{
    set<string> results;
    buildWords("", in, floating, dict, results, 0);
    return results;
}

// recursive helper function to build all possible words
void buildWords(string partial, const string& in, string floating, const set<string>& dict, set<string>& results, int index)
{
    // base case: finished building a full word
    if(index == (int)in.size()){
        if(dict.find(partial) != dict.end() && matchesConstraints(partial, in, floating)){
            results.insert(partial);
        }
        return;
    }

    // fixed letter given
    if(in[index] != '-'){
        buildWords(partial + in[index], in, floating, dict, results, index + 1);
    }
    else{
        // try all lowercase letters at this position
        for(char c = 'a'; c <= 'z'; ++c){
            buildWords(partial + c, in, floating, dict, results, index + 1);
        }
    }
}

// checks if a completed word satisfies floating letter requirements
bool matchesConstraints(const string& word, const string& in, string floating)
{
    // make a copy of floating letters to cross off
    for(int i = 0; i < (int)word.size(); ++i){
        if(in[i] == '-'){
            size_t pos = floating.find(word[i]);
            if(pos != string::npos){
                floating.erase(pos, 1);
            }
        }
        else{
            if(word[i] != in[i]){
                return false;
            }
        }
    }
    // must have used up all floating letters
    return floating.empty();
}
