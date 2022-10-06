#include <catch2/catch_test_macros.hpp>

#include "avltree.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

template<typename K, typename V>
void verifyTree(AVLTree<K, V> const& tree, vector<K> const& solnPreorderTraversal, vector<string> const& solnFuncCalls) {
    // This is based on the following assertion:
    // "Consider the AVL tree A. If some tree B has an in-order traversal that
    // produces a non-decreasing list of values and a pre-order traversal that
    // matches that of A, then A == B"
    // In this case, A is our solution tree and B is the student tree. If we
    // can show that those properties of B match those of A, then they must be
    // the same tree.
    vector<string> funcCalls = tree.getFunctionOrder();
    vector<int> preorderTraversal = tree.getPreorderTraversal();
    vector<int> inorderTraversal = tree.getInorderTraversal();

    REQUIRE(solnFuncCalls == funcCalls);
    REQUIRE(solnPreorderTraversal == preorderTraversal);
    REQUIRE(std::is_sorted(inorderTraversal.begin(), inorderTraversal.end()));
}

TEST_CASE("test_find", "[weight=10][valgrind]") {
	AVLTree<string, string> tree;
    tree.insert("C", "C++");
    tree.insert("free", "delete");
    tree.insert("malloc", "new");
    tree.insert("bool", "void");
    tree.insert("Nico", "nii");
    REQUIRE(tree.find("C").compare("C++") == 0);
    REQUIRE(tree.find("free").compare("delete") == 0);
    REQUIRE(tree.find("malloc").compare("new") == 0);
    REQUIRE(tree.find("bool").compare("void") == 0);
    REQUIRE(tree.find("Nico").compare("nii") == 0);
}

TEST_CASE("test_insert_small", "[weight=5]") {
    AVLTree<int, int> tree;
    tree.insert(1,2);
    tree.insert(4,5);
    tree.insert(5,4);

    vector<int> solnTraversal = {4, 1, 5};
    vector<string> solnFuncCalls = {"rotateLeft"};

    verifyTree(tree, solnTraversal, solnFuncCalls);
}

TEST_CASE("test_insert_find", "[weight=10]") {
    AVLTree<int, int> tree;
    vector<int> elems = {5, 1, 8, 0, 3, 2};
    for (auto e : elems) {
        tree.insert(e, e);
    }

    vector<int> solnTraversal = {3, 1, 0, 2, 5, 8};
    vector<string> solnFuncCalls = {
        "rotateLeftRight",
        "rotateLeft",
        "rotateRight",
    };

    verifyTree(tree, solnTraversal, solnFuncCalls);
    for (auto e : elems) {
        REQUIRE(e == tree.find(e));
    }
}

TEST_CASE("test_insert_big", "[weight=10][valgrind]") {
    AVLTree<int, string> tree;
    vector<int> elems = {55, 45, 12, 34, 56, 46, 13, 35, 57, 47, 14, 36, 58, 48, 15, 37};
    for (auto e : elems) {
        tree.insert(e, "");
    }

    vector<int> solnTraversal = {45, 34, 13, 12, 14, 15, 36, 35, 37, 55, 47, 46, 48, 57, 56, 58};
    vector<string> solnFuncCalls = {
        "rotateRight",
        "rotateRightLeft",
        "rotateRight",
        "rotateLeft",
        "rotateLeft",
        "rotateLeft",
        "rotateLeft",
        "rotateLeft",
    };

    verifyTree(tree, solnTraversal, solnFuncCalls);
}

TEST_CASE("test_remove_small", "[weight=5]") {
    AVLTree<int, string> tree;
    vector<int> elems = {5, 1, 8, 0, 3, 2};
    for (auto e : elems) {
        tree.insert(e, "");
    }

    for (int i = 0; i < 4; i++) {
        tree.remove(i);
    }

    vector<int> solnTraversal = {5, 8};
    vector<string> solnFuncCalls = {
        "rotateLeftRight",
        "rotateLeft",
        "rotateRight",
        "rotateLeft",
    };

    verifyTree(tree, solnTraversal, solnFuncCalls);
}

TEST_CASE("test_remove_big", "[weight=10][valgrind]") {
    AVLTree<int, string> tree;
    vector<int> elems = {94, 87, 61, 96, 76, 92, 42, 78, 17, 11, 41, 95, 36, 26, 23, 93, 31, 3, 45, 18, 73, 24, 74, 1, 71, 82};
    for (auto e : elems) {
        tree.insert(e, "");
    }

    for (int r : {95, 94, 61, 76, 73, 71}) {
        tree.remove(r);
    }

    vector<int> solnTraversal = {45, 26, 17, 3, 1, 11, 23, 18, 24, 36, 31, 42, 41, 87, 78, 74, 82, 93, 92, 96};
    vector<string> solnFuncCalls = {
        "rotateRight",
        "rotateRight",
        "rotateRight",
        "rotateRight",
        "rotateRightLeft",
        "rotateRight",
        "rotateLeft",
        "rotateLeft",
        "rotateLeftRight",
        "rotateLeft",
        "rotateRight",
        "rotateRight",
        "rotateLeft",
    };

    verifyTree(tree, solnTraversal, solnFuncCalls);
}
