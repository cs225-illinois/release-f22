#include "fac.h"

#include <iostream>
#include <cstring>
#include <stdexcept>

using namespace std;


const string USAGE =
"USAGE: fac [NUM] [OPTIONS]\n"
"Calculates [NUM]! .\n"
"\n"
"  -m      Use memoization (defaults to not).\n";

int main(int argc, char* argv[])
{
    unsigned long n = 0;
    bool memoization = false;
    if (argc == 1) {
        cerr << USAGE << endl;
        return -1;
    }

    for (int i = 1; i < argc; i++) {
        /* Are we memoizing? Defaults to no. */
        if (strcmp(argv[i], "-m") == 0) {
            memoization = true;
        } else {
            /* stoi() will except for non-numeric values. */
            try {
                n = stoul(argv[i]);
            } catch (invalid_argument& e) {
                cerr << "Please enter a valid number." << endl;
                return -1;
            } catch (out_of_range& e) {
                cerr << "Number too large to take as input." << endl;
                return -1;
            }
        }
    }
    /* Function pointer points to either the memoized or normal function. */
    unsigned long (*fac_func)(unsigned long);
    fac_func = memoization ? memoized_fac : fac;

    unsigned long previous = 0;
    unsigned long result;
    for (unsigned long i = 0; i <= n; i++) {
        result = fac_func(i);
        if (previous <= result) {
            previous = result;
        } else {
            cout << previous << endl;
            cout << "Overflowed unsigned long!" << endl;
            return -1;
        }
    }
    cout << result << endl;
}