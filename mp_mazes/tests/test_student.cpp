#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;


TEST_CASE("PUT YOUR TESTS HERE!!!", "[tag1][tag2]") {
    // Feel free to use this to put your own test cases.
    // Look at other test files for inspiration!
    string expected = "I put my own test cases here.";
    string actual = "I DON'T HAVE ANY TEST CASES :'(";
    REQUIRE(expected == actual);
}