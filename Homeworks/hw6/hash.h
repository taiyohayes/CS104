#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        unsigned long long w[5] = {0,0,0,0,0};
        int x = 4;
        for (int i = int(k.size()-6); i >= 0; i-=6)
        {
            std::string sub = k.substr(i,6);
            w[x] = letterDigitToNumber(sub[0/*sub.size()-1*/]);
            for (int j = 1; j < 6; j++)/*(int j = int(sub.size()-2); j >= 0; j--)*/
            {
                w[x] *= 36;
                w[x] += letterDigitToNumber(sub[j]);
            }
            x--;
        }
        if (k.size() % 6 != 0)
        {
            std::string rem = k.substr(0, k.size() - (6 * (4 - x)));
            w[x] = letterDigitToNumber(rem[0]);
            for (int m = 1; m < int(rem.size()); m++)
            {
                w[x] *= 36;
                w[x] += letterDigitToNumber(rem[m]);
            }
        }

        HASH_INDEX_T hash = 0;
        for (int n = 0; n < 5; n++)
        {
            hash += rValues[n] * w[n];
        }
        return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        HASH_INDEX_T val;
        letter = tolower(letter);
        if (letter >= 'a' && letter <= 'z')
        {
            val = HASH_INDEX_T(letter) - 97;
        }
        else
        {
            val = HASH_INDEX_T(letter) - 22;
        }
        return val;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
