// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void findWords(std::set<std::string>& words, int loc, int empty, std::string& word, 
                std::string& floating, const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> words;
    std::string word = in;
    std::string yellows = floating;
    int empty = 0;
    for (auto l : word)
    {
        if (l == '-')
        {
            empty++;
        }
    }
    findWords(words, 0, empty, word, yellows, dict);
    return words;
}

// Define any helper functions here
void findWords(std::set<std::string>& words, int loc, int empty, std::string& word, 
                std::string& floating, const std::set<std::string>& dict)
{
    if (loc == int(word.size()))
    {
        if (dict.find(word) != dict.end())
        {
            words.insert(word);
        }
        return;
    }
    if (word[loc] != '-')
    {
        findWords(words, loc+1, empty, word, floating, dict);
        return;
    }
    if (empty <= int(floating.size()) && floating.size() > 0)
    {
        for (auto l : floating)
        {
            std::string temp = floating;
            word[loc] = l;
            floating.erase(floating.find(l), 1);
            findWords(words, loc+1, empty-1, word, floating, dict);
            floating = temp;
        }
        word[loc] = '-';
    }
    else
    {
        for (char letter = 'a'; letter <= 'z'; letter++)
        {
            word[loc] = letter;
            if (floating.find(letter) != floating.npos)
            {
                std::string temp = floating;
                floating.erase(floating.find(letter), 1);
                findWords(words, loc+1, empty-1, word, floating, dict);
                floating = temp;
            }
            else
            {
                findWords(words, loc+1, empty-1, word, floating, dict);
            }
        } 
        word[loc] = '-'; 
    }
    return;
}