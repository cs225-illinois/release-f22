#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "schedule.h"
#include "tests_util.h"

TEST_CASE("schedule() Approximate Public Test 1", "[weight=2]") {
    const V2D roster = {{"CS577", "JydY", "MnWd", "tnkL"},\
     {"CS591", "gpDS", "94Ol", "tnkL"}, \
     {"CS386", "SjC0", "EYge", "Nvu1"}, \
     {"CS500", "MnWd", "uAcT", "EYge"}, \
     {"CS395", "gpDS", "EYge", "MnWd"}
     };

    std::vector<std::string> timeslots = {"9AM", "11AM", "1PM", "3PM"};

    V2D out = schedule(roster, timeslots);

    verifySchedule(roster, out, 4);
}

TEST_CASE("schedule() Public Test 1", "[weight=3]") {
    const V2D roster = {{"CS577", "JydY", "MnWd", "tnkL"},\
     {"CS591", "gpDS", "94Ol", "tnkL"}, \
     {"CS386", "SjC0", "EYge", "Nvu1"}, \
     {"CS500", "MnWd", "uAcT", "EYge"}, \
     {"CS395", "gpDS", "EYge", "MnWd"}
     };

    std::vector<std::string> timeslots = {"9AM", "11AM", "1PM"};

    V2D out = schedule(roster, timeslots);

    verifySchedule(roster, out, 3);
}

TEST_CASE("schedule() No Match Test Public 1", "[weight=5]") {
    const V2D roster = {
    {"CS101", "a", "b"}, \
    {"CS102", "b", "c"}, \
    {"CS103", "a", "c"}
    };

    std::vector<std::string> timeslots = {"9AM", "11AM"};

    V2D out = schedule(roster, timeslots);

    REQUIRE(out.size()==1);
    REQUIRE(out[0].size()==1);
    REQUIRE(out[0][0]=="-1");
}
