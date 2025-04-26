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

// definition of primary wordle function
void buildWords(string partial, const string& in, string floating, const set<string>& dict, set<string>& results, int index, int blanksRemaining);

// definition of primary wordle function
set<string> wordle(
    const string& in,
    const string& floating,
    const set<string>& dict)
{
    set<string> results;
    int blanks = 0;
    for(unsigned int i = 0; i < in.size(); ++i){
        if(in[i] == '-'){
            ++blanks;
        }
    }
    buildWords("", in, floating, dict, results, 0, blanks);
    return results;
}

// recursive helper function to build all possible words
void buildWords(string partial, const string& in, string floating, const set<string>& dict, set<string>& results, int index, int blanksRemaining)
{
    if(index == (int)in.size()){
        if(floating.empty() && dict.find(partial) != dict.end()){
            results.insert(partial);
        }
        return;
    }

    if(in[index] != '-'){
        buildWords(partial + in[index], in, floating, dict, results, index + 1, blanksRemaining);
    }
    else{
        set<char> options;

        // manually loop through floating string to add options
        for(unsigned int i = 0; i < floating.size(); ++i){
            options.insert(floating[i]);
        }

        // if blanks are more than floating letters, allow any letter
        if(floating.size() < (unsigned int)blanksRemaining){
            char c = 'a';
            while(c <= 'z'){
                options.insert(c);
                ++c;
            }
        }

        set<char>::iterator it;
        for(it = options.begin(); it != options.end(); ++it){
            string updatedFloating = floating;
            size_t pos = updatedFloating.find(*it);
            if(pos != string::npos){
                updatedFloating.erase(pos, 1);
            }
            buildWords(partial + *it, in, updatedFloating, dict, results, index + 1, blanksRemaining - 1);
        }
    }
}