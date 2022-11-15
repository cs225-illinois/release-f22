#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "schedule.h"
#include "tests_util.h"

TEST_CASE("file_to_V2D Public Test 1", "[weight=5]") {
    V2D roster = file_to_V2D("../tests/data/c5_s10_3_roster.csv");

    const V2D correct_roster = {{"CS577", "JydY", "MnWd", "tnkL"},\
     {"CS591", "gpDS", "94Ol", "tnkL"}, \
     {"CS386", "SjC0", "EYge", "Nvu1"}, \
     {"CS500", "MnWd", "uAcT", "EYge"}, \
     {"CS395", "gpDS", "EYge", "MnWd"}
     };

    REQUIRE(roster == correct_roster);

    V2D students = file_to_V2D("../tests/data/c5_s10_3_students.csv");

    const V2D answer = {
        {"JydY", "CS577"}, \
        {"MnWd", "CS577", "CS500", "CS395"}, \
        {"tnkL", "CS577", "CS591"}, \
        {"gpDS", "CS591", "CS395"}, \
        {"94Ol", "CS591"}, \
        {"SjC0", "CS386"}, \
        {"EYge", "CS386", "CS500", "CS395"}, \
        {"Nvu1", "CS386"}, \
        {"uAcT", "CS500"}
        };
    REQUIRE(students == answer);
}

TEST_CASE("file_to_V2D Public Test 2", "[weight=5]") {
    V2D roster = file_to_V2D("../tests/data/c10_s50_2_roster.csv");

    const V2D correct_roster = {
        {"CS502", "RAq7", "4GUp"}, \
        {"CS512", "nEFp", "n4mr"}, \
        {"CS161", "n4mr", "gLbj"}, \
        {"CS259", "rJvt", "RAq7"}, \
        {"CS411", "OZOR", "nHTn"}, \
        {"CS299", "3p9F", "xrmC"}, \
        {"CS190", "STSG", "3p9F"}, \
        {"CS180", "ZFvu", "Mkds"}, \
        {"CS583", "UkhY", "Xxka"}, \
        {"CS245", "RAq7", "t57x"}
        };

    REQUIRE(roster == correct_roster);

    V2D students = file_to_V2D("../tests/data/c10_s50_2_students.csv");

    const V2D answer = {
        {"RAq7", "CS502", "CS259", "CS245"}, \
        {"4GUp", "CS502"}, \
        {"nEFp", "CS512"}, \
        {"n4mr", "CS512", "CS161"}, \
        {"gLbj", "CS161"}, \
        {"rJvt", "CS259"}, \
        {"OZOR", "CS411"}, \
        {"nHTn", "CS411"}, \
        {"3p9F", "CS299", "CS190"}, \
        {"xrmC", "CS299"}, \
        {"STSG", "CS190"}, \
        {"ZFvu", "CS180"}, \
        {"Mkds", "CS180"}, \
        {"UkhY", "CS583"}, \
        {"Xxka", "CS583"}, \
        {"t57x", "CS245"}
        };

    REQUIRE( students == answer);
}

TEST_CASE("clean() Public Test 1", "[weight=5]") {
    const V2D students = {
    {"JydY", "CS577"}, \
    {"MnWd", "CS577", "CS395"}, \
    {"tnkL", "CS577", "CS591"}, \
    {"gpDS", "CS591", "CS395"}, \
    {"94Ol", "CS591"}, \
    {"EYge", "CS500", "CS395"}, \
    {"Nvu1", "CS386"}, \
    {"uAcT", "CS500"}
    };

    const V2D roster = {
    {"CS577", "JydY", "MnWd", "tnkL"}, \
    {"CS591", "gpDS", "94Ol", "tnkL"}, \
    {"CS386", "SjC0"}, \
    {"CS500", "MnWd", "uAcT", "EYge"}, \
    {"CS395", "gpDS", "EYge", "MnWd"}
    };

    const V2D answer = {{ "CS577", "JydY", "MnWd", "tnkL"}, \
    { "CS591", "gpDS", "94Ol", "tnkL"}, \
    { "CS500", "uAcT", "EYge"}, \
    { "CS395", "gpDS", "EYge", "MnWd"}};

    V2D user = clean(roster, students);

    REQUIRE(user == answer);
}

TEST_CASE("clean() Public Test 2", "[weight=5]") {
    const V2D students = {
    {"RAq7", "CS502", "CS259", "CS245"}, \
    {"4GUp", "CS502"}, \
    {"n4mr", "CS512"}, \
    {"gLbj", "CS161"}, \
    {"rJvt", "CS259"}, \
    {"OZOR", "CS411"}, \
    {"nHTn", "CS411"}, \
    {"3p9F", "CS299", "CS190"}, \
    {"xrmC", "CS299"}, \
    {"STSG", "CS190"}, \
    {"Mkds", "CS180"}, \
    {"UkhY", "CS583"}, \
    {"t57x", "CS245"}
    };
    
    const V2D roster = {
    {"CS259", "rJvt", "RAq7"}, \
    {"CS502", "RAq7"}, \
    {"CS512", "nEFp", "n4mr"}, \
    {"CS161", "n4mr"}, \
    {"CS411", "OZOR", "nHTn"}, \
    {"CS299"}, \
    {"CS190", "STSG", "3p9F"}, \
    {"CS180", "Mkds"}, \
    {"CS583", "UkhY", "Xxka"}, \
    {"CS245", "RAq7", "abc5"}
    };

    const V2D answer = {{ "CS259", "rJvt", "RAq7"}, \
    { "CS502", "RAq7"}, \
    { "CS512", "n4mr"}, \
    { "CS411", "OZOR", "nHTn"}, \
    { "CS190", "STSG", "3p9F"}, \
    { "CS180", "Mkds"}, \
    { "CS583", "UkhY"}, \
    { "CS245", "RAq7"}};

    V2D user = clean(roster, students);

    REQUIRE(user == answer);
}
