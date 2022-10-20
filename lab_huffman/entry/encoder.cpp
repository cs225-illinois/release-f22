/**
 * Program for encoding files with HuffmanTrees.
 */

#include "encoder.h"

using namespace std;

int main(int argc, char** argv)
{
    vector<string> args(argv, argv + argc);
    return encoder::main(args);
}
