#include <catch2/catch_test_macros.hpp>

#include "InorderTraversal.h"

#include "binarytree/util.h"
#include "binarytree.h"
#include "binarytree.hpp"


#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <vector>
#include <string>
#include <utility>

using namespace std;

// Left-hand side is not ordered
typename BinaryTree<int>::Node* genNonIsOrderedTreeLeft()
{
  typename BinaryTree<int>::Node* bottomLeft = new typename BinaryTree<int>::Node(8);
  bottomLeft->left = new typename BinaryTree<int>::Node(2);
  typename BinaryTree<int>::Node* five_node = new typename BinaryTree<int>::Node(5);
  five_node->left = bottomLeft;
  typename BinaryTree<int>::Node* zero_node = new typename BinaryTree<int>::Node(0);
  zero_node->left = five_node;
  zero_node->right = new typename BinaryTree<int>::Node(3);
  zero_node->right->right = new typename BinaryTree<int>::Node(4);
  typename BinaryTree<int>::Node* seven_node = new typename BinaryTree<int>::Node(7);
  seven_node->left = new typename BinaryTree<int>::Node(10);
  seven_node->right = new typename BinaryTree<int>::Node(9);
  typename BinaryTree<int>::Node* root = new typename BinaryTree<int>::Node(6);
  root->left = zero_node;
  root->right = seven_node;
  return root;
}

typename BinaryTree<int>::Node* genNonIsOrderedTreeRight()
{
  typename BinaryTree<int>::Node* root = new typename BinaryTree<int>::Node(4);
  typename BinaryTree<int>::Node* six_node = new typename BinaryTree<int>::Node(6);
  six_node->left = new typename BinaryTree<int>::Node(3);
  six_node->right = new typename BinaryTree<int>::Node(8);
  root->right = six_node;
  typename BinaryTree<int>::Node* two_node = new typename BinaryTree<int>::Node(1);
  two_node->left = new typename BinaryTree<int>::Node(0);
  two_node->right = new typename BinaryTree<int>::Node(2);
  root->left = two_node;
  return root;
}

void genIsOrderedTree(BinaryTree<int>& tree)
{
  tree.insert(6);
  tree.insert(10);
  tree.insert(7);
  tree.insert(4);
  tree.insert(0);
  tree.insert(8);
  tree.insert(9);
  tree.insert(11);
  tree.insert(1);
  tree.insert(3);
  tree.insert(2);
  tree.insert(5);
}

void assertMirror(vector<int> a, vector<int> b)
{
    REQUIRE(a.size() == b.size());

    for(size_t i = 0; i < a.size(); i++){
        CHECK(a[i] == b[b.size()-1-i]);
    }
}

void assert_path(vector<vector <int> > a, vector<vector<int> > b)
{
    REQUIRE(a.size() == b.size());
    for(size_t i = 0; i < a.size(); i++){
        REQUIRE(a[i].size() == b[i].size());
        for(size_t j=0; j<a[i].size();j++){
            CHECK(a[i][j]==b[i][j]);
        }
    }
}

////////////////////////////////////////////////////////////////
//////////////////////// Start of Tests ////////////////////////
////////////////////////////////////////////////////////////////

TEST_CASE("test_mirror", "[weight=10]"){
    vector<int> nodes;
    nodes.push_back(58); //         58
    nodes.push_back(35); //
    nodes.push_back(72); //    35        72
    nodes.push_back(10); //
    nodes.push_back(40); //  10  40    61  80
    nodes.push_back(61); //
    nodes.push_back(80); // 0 19            93
    nodes.push_back(93); //
    nodes.push_back(0); //
    nodes.push_back(19); //

    BinaryTree<int> tree;
    for(size_t i = 0; i < nodes.size(); i++)
        tree.insert(nodes[i]);

    vector<int> beforeMirror;
    vector<int> afterMirror;

    tree.inOrder(beforeMirror);

    tree.mirror();

    tree.inOrder(afterMirror);

    assertMirror(beforeMirror, afterMirror);
}

TEST_CASE("test_isOrderedRecursive", "[weight=10]"){
    BinaryTree<int> treeLeft(genNonIsOrderedTreeLeft());

    REQUIRE(treeLeft.isOrderedRecursive() == false);

    BinaryTree<int> treeRight(genNonIsOrderedTreeRight());

    REQUIRE(treeRight.isOrderedRecursive() == false);

    BinaryTree<int> tree2;
    genIsOrderedTree(tree2);

    REQUIRE(tree2.isOrderedRecursive() == true);
}

TEST_CASE("test_isOrderedIterative", "[weight=10]"){
    BinaryTree<int> treeLeft(genNonIsOrderedTreeLeft());

    REQUIRE(treeLeft.isOrderedIterative() == false);

    BinaryTree<int> treeRight(genNonIsOrderedTreeRight());

    REQUIRE(treeRight.isOrderedIterative() == false);

    BinaryTree<int> tree2;
    genIsOrderedTree(tree2);

    REQUIRE(tree2.isOrderedIterative() == true);
}

TEST_CASE("test_InorderTraversal", "[weight=10]"){
    vector<int> nodes;
    nodes.push_back(52); //         52
    nodes.push_back(39); //
    nodes.push_back(71); //    39         71
    nodes.push_back(17); //
    nodes.push_back(47); //  17   47     69   80
    nodes.push_back(69); //
    nodes.push_back(80); // 0 24             90
    nodes.push_back(90); //
    nodes.push_back(0); //
    nodes.push_back(24); //

    BinaryTree<int> tree;
    for(size_t i = 0; i < nodes.size(); i++)
        tree.insert(nodes[i]);

    InorderTraversal<int> t(tree.getRoot());
    TreeTraversal<int>::Iterator it = t.begin();
    REQUIRE( (*it)->elem == 0  ); ++it;
    REQUIRE( (*it)->elem == 17 ); ++it;
    REQUIRE( (*it)->elem == 24 ); ++it;
    REQUIRE( (*it)->elem == 39 ); ++it;
    REQUIRE( (*it)->elem == 47 ); ++it;
    REQUIRE( (*it)->elem == 52 ); ++it;
    REQUIRE( (*it)->elem == 69 ); ++it;
    REQUIRE( (*it)->elem == 71 ); ++it;
    REQUIRE( (*it)->elem == 80 ); ++it;
    REQUIRE( (*it)->elem == 90 ); ++it;

}
