#include <catch2/catch_test_macros.hpp>

#include "stack.h"
#include "queue.h"
#include <iostream>
#include <sstream>
#include <string>

#include "exercises.h"
#include "quackfun.h"

using namespace std;
using namespace RecursionExercises;
using namespace QuackFun;

queue<char> stringToQueue(std::string s)
{
    queue<char> q;

    for (char c : s)
        q.push(c);

    return q;
}

TEST_CASE("sumDigits", "[valgrind][weight=1]"){
    SECTION("Base cases work") {
        REQUIRE(sumDigits(1) == 1);
        REQUIRE(sumDigits(0) == 0);
    }
    SECTION("Multiple digits sum correctly") {
        REQUIRE(sumDigits(243) == 9);
        REQUIRE(sumDigits(49) == 13);
    }
}

TEST_CASE("triangle", "[valgrind][weight=1]"){
    SECTION("Base cases work") {
        REQUIRE(triangle(0) == 0);
    }
    SECTION("Recursive cases work") {
        REQUIRE(triangle(3) == 6);
        REQUIRE(triangle(6) == 21);
        REQUIRE(triangle(8) == 36);
    }
}

TEST_CASE("sum", "[valgrind][weight=3]"){
    stack<int> s;
    for (int i = 0; i <= 16; i++)
        s.push(i);
    stack<int> s2 = s;
    SECTION("Sum is correct") {
        REQUIRE(QuackFun::sum(s) == 136);
    }
    SECTION("Stack is unchanged") {
        REQUIRE(s == s2);
    }

    stack<double> s3;
    for (int i = 0; i <= 10; i++) {
        s3.push(2.1+4.5*i);
    }
    stack<double> s4 = s3;

    stack<double>::_ctor_count = 0;
    double sumFloat = QuackFun::sum<double>(s3);

    SECTION("Float sum is correct") {
        if (sumFloat > 270.61 || sumFloat < 270.59) {
            FAIL("Expected sum = 270.6; Actual = " + to_string(sumFloat));
        }
    }
    SECTION("Stack is unchanged") {
        REQUIRE(s3 == s4);
    }
    SECTION("Did not make any additional stack objects") {
        REQUIRE(stack<double>::_ctor_count == 0);
    }
}

TEST_CASE("isBalanced", "[valgrind][weight=3]")
{

    SECTION("balanced") {
        std::vector<std::string> strings = {
            "",
            "[]",
            "cs225[]522sc",
            "[cs225]",
            ")[[[][]]]",
            "[)[([ )][]]]"
        };

        for (std::string & s : strings) {
            INFO(s);
            REQUIRE(QuackFun::isBalanced(stringToQueue(s)) == true);
        }
    }

    SECTION("unbalanced") {
        std::vector<std::string> strings = {
            "[",
            "[[]",
            "][][]",
            "[[()][][",
            "[]][[]",
            "[[[[[]]c]s]2]2]5"
        };

        for (std::string & s : strings) {
            INFO(s);
            REQUIRE(QuackFun::isBalanced(stringToQueue(s)) == false);
        }
    }

    SECTION("Only used 1 stack") {
        queue<char> q = stringToQueue("notempty");

        stack<char>::_ctor_count = 0;
        queue<char>::_ctor_count = 0;

        isBalanced(q);

        REQUIRE(stack<char>::_ctor_count == 1);
        REQUIRE(queue<char>::_ctor_count == 1);
    }
}

TEST_CASE("scramble 17", "[valgrind][weight=3]") {
    queue<int> q;
    for (int i = 1; i <= 17; i++) {
        q.push(i);
    }

    QuackFun::scramble<int>(q);

    stringstream scrambled_output;
    while (!q.empty()) {
        scrambled_output << q.front() << ' ';
        q.pop();
    }
    string scrambled = scrambled_output.str();
    string expected = "1 3 2 4 5 6 10 9 8 7 11 12 13 14 15 17 16 ";

    stringstream str;

    str << "Scrambled queue: " << scrambled << endl;
    str << "Expected:        " << expected << endl;

    INFO(str.str());

    if (scrambled != expected) {
        FAIL("See output above");
    }
}

TEST_CASE("scramble 9", "[valgrind][weight=3]") {
    queue<int> q;
    for (int i = 4; i <= 12; i++) {
        q.push(i);
    }

    QuackFun::scramble<int>(q);

    stringstream scrambled_output;
    while (!q.empty()) {
        scrambled_output << q.front() << ' ';
        q.pop();
    }
    string scrambled = scrambled_output.str();
    string expected = "4 6 5 7 8 9 12 11 10 ";

    stringstream str;

    str << "Scrambled queue: " << scrambled << endl;
    str << "Expected:        " << expected << endl;

    INFO(str.str());

    if (scrambled != expected) {
        FAIL("See output above");
    }
}


