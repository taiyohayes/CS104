#include "fermat.h"

#include <vector>
#include <cassert>
#include <random>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>

// Calculates (base ^ exponent) % mod
std::uint32_t mod_exp(std::uint32_t base, std::uint32_t exponent, std::uint32_t mod)
{
    std::uint64_t x = 1, r = base % mod;
    while (exponent >= 1)
    {
        if (exponent % 2)
        {
            x = (x*r) % mod;
        }
        r = (r*r) % mod;
        exponent /= 2;
    }
    return x;
}

// Perform Fermat test on n.
// You should return true only if A^(n-1) % n == 1 for every A inside the tests vector
bool fermat_test(std::uint32_t n, const std::vector<std::uint32_t>& tests)
{
    for (unsigned int i = 0; i < tests.size(); i++)
    {
        if (mod_exp(tests[i], n-1, n) != 1)
        {
            return false;
        }
    }
    return true;
}
