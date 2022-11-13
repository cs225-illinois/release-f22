#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "cs225/PNG.h"
#include "dsets.h"
#include "maze.h"
#include "mazereader.h"


using std::cout;
using std::endl;
using std::string;



TEST_CASE("Adding min elements", "[dsets][addelements]") {
    // Feel free to use this to put your own test cases.
    // Look at other test files for inspiration!
    DisjointSets dj;
    dj.addelements(2);
    int expected = 1;
    int actual = dj.find(1);
    REQUIRE(expected == actual);
}
TEST_CASE("union", "[dsets][union]") {
    // Feel free to use this to put your own test cases.
    // Look at other test files for inspiration!
    DisjointSets dj;
    dj.addelements(2);
    dj.setunion(0,1);
    int expected = 0;
    int actual = dj.find(1);
    REQUIRE(expected == actual);
}
TEST_CASE("Making blank maze", "[SquareMaze][blank]") {
    // Feel free to use this to put your own test cases.
    // Look at other test files for inspiration!
    SquareMaze s;
    s.makeMaze(25,25);
    PNG* png = s.drawMazeWithSolution();
    png->writeToFile("25x25_out_w_soln.png");
}

