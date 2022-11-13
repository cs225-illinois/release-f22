#include <catch2/catch_test_macros.hpp>
#include "tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "List.h"

using namespace cs225;


//
// Non-iterator Tests:
//
TEST_CASE("List::insertFront size", "[weight=1][part=1][valgrind]") {
    List<int> list;

    for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }

    REQUIRE( 10 == list.size() );
}

TEST_CASE("List::insertBack size", "[weight=2][part=1][valgrind]") {
    List<int> list;

    for (unsigned i = 0; i < 10; i++) { list.insertBack(i); }

    REQUIRE( 10 == list.size() );
}

TEST_CASE("List::insert contents", "[weight=4][part=1][valgrind]") {
    List<int> list;

    list.insertBack(3);
    list.insertBack(2);
    list.insertBack(1);
    list.insertFront(3);
    list.insertFront(2);
    list.insertFront(1);

    stringstream s;
    list.print(s);

    REQUIRE( "< 1 2 3 3 2 1 >" == s.str() );
}

TEST_CASE("List::triplerotate basic", "[weight=5][part=1][valgrind]") {
    List<int> list;

    for (int i = 1; i <= 2; i++)
        list.insertBack(i);

    list.tripleRotate();

    stringstream s;

    list.print(s);

    REQUIRE("< 1 2 >" == s.str());
}

TEST_CASE("List::triplerotate simple", "[weight=10][part=1][valgrind]") {
    List<int> list;

    for (int i = 1; i <= 6; i++)
        list.insertBack(i);

    list.tripleRotate();

    stringstream s;

    list.print(s);

    REQUIRE("< 2 3 1 5 6 4 >" == s.str());
}

TEST_CASE("List::split simple", "[weight=5][part=1][valgrind]") {
    List<int> list;

    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    list.insertBack(4);

    List<int> slist = list.split(2);
    stringstream s1, s2;

    list.print(s1);
    slist.print(s2);

    REQUIRE( "< 1 2 >" == s1.str() );
    REQUIRE( "< 3 4 >" == s2.str() );
}

TEST_CASE("List::split images", "[weight=5][part=1]") {

    PNG in;         in.readFromFile("../tests/split.png");
    PNG expected_1; expected_1.readFromFile("../tests/expected-split_1.png");
    PNG expected_2; expected_2.readFromFile("../tests/expected-split_2.png");
    PNG expected_3; expected_3.readFromFile("../tests/expected-split_3.png");

    List<HSLAPixel> list1;
    for (unsigned i = 0; i < in.width(); i++)
        for (unsigned j = 0; j < in.height(); j++)
            list1.insertBack(in.getPixel(i, j));
    List<HSLAPixel> list2 = list1.split(400 * 240);
    List<HSLAPixel> list3 = list2.split(400 * 240);

    vector<HSLAPixel> im1vect(list1.begin(), list1.end());
    vector<HSLAPixel> im2vect(list2.begin(), list2.end());
    vector<HSLAPixel> im3vect(list3.begin(), list3.end());

    PNG out1(400, 240);
    unsigned x = 0;
    for (unsigned i = 0; i < im1vect.size(); i++) {
        unsigned y = i % 240;
        out1.getPixel(x, y) = im1vect[i];
        if (y == 239) { x++; }
    }
    out1.writeToFile("actual-split_1.png");

    INFO("First split output saved as actual-split_1.png");
    REQUIRE(out1 == expected_1);


    PNG out2(400, 240);
    x = 0;
    for (size_t i = 0; i < im2vect.size(); i++) {
        int y = i % 240;
        out2.getPixel(x, y) = im2vect[i];
        if (y == 239)
            x++;
    }
    out2.writeToFile("actual-split_2.png");

    INFO("Second split output saved as actual-split_2.png");
    REQUIRE(out2 == expected_2);


    PNG out3(400, 240);
    x = 0;
    for (size_t i = 0; i < im3vect.size(); i++) {
        int y = i % 240;
        out3.getPixel(x, y) = im3vect[i];
        if (y == 239)
            x++;
    }
    out3.writeToFile("actual-split_3.png");

    INFO("Third split output saved as actual-split_3.png");
    REQUIRE(out3 == expected_3);
}

TEST_CASE("List::_destroy empty list", "[weight=3][part=1][valgrind]") {

    List<int>* list = new List<int>();
    delete list;

    SUCCEED("Didn't crash!");
}

//
// Iterator Tests:
//
TEST_CASE("List::begin() returns an iterator to the front of the list", "[weight=1][part=1][valgrind]") {
    List<int> list;
    for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }

    List<int>::ListIterator iter = list.begin();
    REQUIRE( *iter == 9 );
}

TEST_CASE("List::ListIterator::operator++ advances the iterator (pre-increment)", "[weight=1][part=1][valgrind]") {
    List<unsigned> list;
    for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }

    List<unsigned>::ListIterator iter = list.begin();
    ++iter;
    REQUIRE( *iter == 8 );
}

TEST_CASE("List::ListIterator::operator++ advances the iterator (post-increment)", "[weight=1][part=1][valgrind]") {
    List<unsigned> list;
    for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }

    List<unsigned>::ListIterator iter = list.begin();
    iter++;
    iter++;
    REQUIRE( *iter == 7 );
}

TEST_CASE("List::ListIterator::operator++ (post-increment) returns an un-incremented iterator", "[weight=1][part=1][valgrind]") {
    List<unsigned> list;
    for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }

    List<unsigned>::ListIterator iter = list.begin();
    List<unsigned>::ListIterator pre = iter++;

    REQUIRE( *pre == 9 );
}

TEST_CASE("List::ListIterator::operator-- moves the iterator backwards", "[weight=1][part=1][valgrind]") {
    List<unsigned> list;
    for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }

    List<unsigned>::ListIterator iter = list.begin();

    iter++;  REQUIRE( *iter == 8 );
    iter++;  REQUIRE( *iter == 7 );
    iter--;  REQUIRE( *iter == 8 );
    iter--;  REQUIRE( *iter == 9 );
}

TEST_CASE("List::ListIterator::operator-- (post-increment) returns an un-incremented iterator", "[weight=1][part=1][valgrind]") {
    List<unsigned> list;
    for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }

    List<unsigned>::ListIterator iter = list.begin();

    iter++; // 9 --> 8
    iter++; // 8 --> 7
    List<unsigned>::ListIterator seven = iter--;

    REQUIRE( *seven == 7 );
}

TEST_CASE("List::ListIterator::end is reached", "[weight=1][part=1][valgrind]") {
    List<unsigned> list;
    list.insertFront(1);
    list.insertFront(2);
    list.insertFront(3);

    List<unsigned>::ListIterator iter = list.begin();
    iter++;
    iter++;
    iter++;

    REQUIRE( (bool)(iter == list.end()) );
}

TEST_CASE("List::ListIterator::end is not ::begin in a non-empty list", "[weight=1][part=1][valgrind]") {
    List<unsigned> list;
    list.insertFront(1);
    list.insertFront(2);
    list.insertFront(3);

    REQUIRE( (bool)(list.begin() != list.end()) );
}


