/**
 * @file fac.cpp
 * Contains factorial-calculating functions both utilizing and not
 * utilizing memoization.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "fac.h"

#include <iostream>
#include <map>
#include <cstring>
#include <stdexcept>

using namespace std;

/**
 * Calculates the factorial of the given number.
 * @param n Number to calculate factorial for.
 * @return n!.
 */
unsigned long fac(unsigned long n)
{
    if (n == 0) {
        return 1;
    }
    return n * fac(n - 1);
}

/**
 * Calculates the factorial of the given number.
 * This version utilizes memoization.
 * @param n Number to calculate factorial for.
 * @return n!.
 */
unsigned long memoized_fac(unsigned long n)
{
    /* Fancy initialization of the static map with an initializer list Maps 0->1 */
    static map<unsigned long, unsigned long> memo = {
        {0, 1},
    };

    map<unsigned long, unsigned long>::iterator lookup = memo.find(n);
    if (lookup != memo.end()) {
        return lookup->second;
    } else {
        unsigned long result = n * memoized_fac(n - 1);
        memo[n] = result;
        return result;
    }
}
