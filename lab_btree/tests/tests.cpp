#include <catch2/catch_test_macros.hpp>

#include "btree.h"

#include <utility>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <numeric>
#include <vector>

const static std::vector<size_t> sizes = {
    10,
    100,
    1000,
    10000,
    100000,
};

std::vector<std::pair<int, int>> make_int_data(int n, bool random) {
    std::vector<std::pair<int, int>> data;
    if (random) {
        for (int i = 0; i < n; i++) {
            int rand_val = rand();
            data.emplace_back(rand_val, rand_val);
        }
    } else {
        for (int i = 0; i < n; i++) {
            data.emplace_back(i, i);
        }
    }
    return data;
}

template<class K, class V>
void do_inserts(std::vector<std::pair<K, V>>& data, BTree<K, V>& b) {
    for (auto& key_val : data) {
        b.insert(key_val.first, key_val.second);
    }
}
template<class K, class V>
void verify_finds(std::vector<std::pair<K, V>>& data, BTree< K, V>& b) {
    for (auto& key_val : data) {
        V ret = b.find(key_val.first);
        REQUIRE(key_val.second == ret);
    }
}

std::unordered_map<size_t, std::vector<int>> vecs;

TEST_CASE("test_insertion_idx_emp", "[weight=5][timeout=8000]") {
    std::vector<int> v;
    REQUIRE(0 == insertion_idx(v, 0));
}

TEST_CASE("test_insertion_idx_small", "[weight=5][timeout=8000]") {
    std::vector<int> data = { 1, 3, 5, 7 };
    REQUIRE(0 == insertion_idx(data, -1));
    REQUIRE(0 == insertion_idx(data, 1));
    REQUIRE(4 == insertion_idx(data, 99));
}

size_t insertion_idx_time(std::vector< int >* vec) {
    // check needed since monad calls this with a vector of size 1 (to ``warm up'' the generator/timing function)
    if (vec->size() <= 2) {
        size_t val = 0;
        size_t ret = insertion_idx(*vec, (*vec)[val]);
        REQUIRE(val == ret);
        return ret;
    }

    size_t val = 1;
    size_t ret = insertion_idx(*vec, (*vec)[val]);
    REQUIRE(val == ret);

    val = vec->size() - 2;
    ret = insertion_idx(*vec, (*vec)[val]);
    REQUIRE(val == ret);

    return ret;
}


std::vector<int>* vec_gen(size_t n) {
    size_t vec_key = n;
    if (vecs.find(vec_key) == vecs.end()) {
        vecs[vec_key] = std::vector<int>(n, 0);
        iota(vecs[vec_key].begin(), vecs[vec_key].end(), 0);
    }
    return &vecs[vec_key];
}

TEST_CASE("test_btree3_small", "[weight=5][valgrind][timeout=8000]") {
    std::vector<std::pair<int, int>> data = {
        {1, 5},
        {4, 7},
        {5, 43},
        {-43, 3},
        {99, 2},
        {23, 7},
        {3, 2},
        {9, 4},
    };
    BTree< int, int > b(3);
    do_inserts(data, b);
    verify_finds(data, b);
    REQUIRE(0 == b.find(-999));
    REQUIRE(b.is_valid(3));
}

TEST_CASE("test_btree3_large_seq", "[weight=5][timeout=8000]") {
    auto data = make_int_data(10000, false);
    BTree< int, int > b(3);
    do_inserts(data, b);
    verify_finds(data, b);
    REQUIRE(0 == b.find(-9999));
    REQUIRE(b.is_valid(3));
}

TEST_CASE("test_btree3_large_rand",  "[weight=5][timeout=8000]") {
    srand(225);
    auto data = make_int_data(10000, true);
    BTree< int, int > b(3);
    do_inserts(data, b);
    verify_finds(data, b);
    REQUIRE(b.is_valid(3));
}

TEST_CASE("test_btree64_large_seq",  "[weight=5][timeout=8000]") {
    auto data = make_int_data(100000, false);
    BTree< int, int > b(64);
    do_inserts(data, b);
    verify_finds(data, b);
    REQUIRE(0 == b.find(-9999));
    REQUIRE(b.is_valid(64));
}

TEST_CASE("test_btree64_large_rand",  "[weight=5][timeout=8000]") {
    srand(225);
    auto data = make_int_data(100000, true);
    BTree< int, int > b(64);
    do_inserts(data, b);
    verify_finds(data, b);
    REQUIRE(b.is_valid(64));
}

TEST_CASE("test_btree128_med_rand", "[weight=5][timeout=8000]") {
    srand(225);
    auto data = make_int_data(20000, true);
    BTree< int, int > b(128);
    do_inserts(data, b);
    verify_finds(data, b);
    REQUIRE(b.is_valid(128));
}

TEST_CASE("test_btree256_med_rand", "[weight=5][timeout=8000]") {
    srand(255);
    auto data = make_int_data(40000, true);
    BTree< int, int > b(256);
    do_inserts(data, b);
    verify_finds(data, b);
    REQUIRE(b.is_valid(256));
}

TEST_CASE("test_btree12_double", "[weight=5][timeout=8000]") {
    std::vector<std::pair<float, float>> data ={
        {0.1, 3.4},
        {3.5, 4.6},
        {2.4, 3.3},
        {1.0, 2.0},
        {9.0, 8.5},
        {7.6, 1.2},
        {8.0, 0.3},
        {6.5, 5.5},
        {4.6, 9.0},
        {1.1, 3.4},
    };
    BTree<float, float > b(5);
    do_inserts(data, b);
    verify_finds(data, b);
    REQUIRE(b.is_valid(5));
}


TEST_CASE("test_btree12_strings", "[weight=5][timeout=8000]") {
    std::vector<std::pair<std::string, std::string>> data ={
        {"lls", "skye"},
        {"mjoras", "yogi"},
        {"collin", "meco"},
        {"fred", "skye"},
        {"arya", "nymeria"},
        {"jon", "ghost"},
        {"bran", "summer"},
        {"robb", "grey wind"},
        {"sansa", "lady"},
        {"rickon", "shaggydog"},
    };
    BTree<std::string, std::string > b(5);
    do_inserts(data, b);
    verify_finds(data, b);
    REQUIRE(b.is_valid(5));
}
