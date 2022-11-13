#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"
#include <random>

using namespace std;

int main()
{
    // Write your own main here
    cout << "Add your own tests here! Modify main.cpp" << endl;
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 6);
    std::uniform_int_distribution<int> walls(0,1);
    for (size_t i = 0; i <= 6; i++) {
        std::cout<<dist(rd)<<" "<<" Wall = "<< walls(rd)<<", ";
    }
    std::cout<<"\n";
    return 0;
}
