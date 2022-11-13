#include <catch2/catch_test_macros.hpp>

#include "utils.h"
#include "bst.h"

#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <vector>
#include <string>
#include <utility>
#include <map>

template <class K, class V>
void match_walk(BST<K, V> & tree, std::vector<K> & ans){
  std::vector<K> lexW = tree.getInorderTraversal();

  REQUIRE(lexW.size() == ans.size());

  for(size_t i = 0; i < ans.size(); ++i){
    if(lexW[i]!=ans[i]){ 
      INFO("At index value " + std::to_string(i) + " your lexWalk was incorrect.");
      INFO("Check your printed tree for incorrect structure.");
      REQUIRE(lexW[i] == ans[i]);
    }
  }
}

void match_vector(std::vector<int> & out, std::vector<int> & ans){

  REQUIRE(out.size() == ans.size());

  for(size_t i = 0; i < ans.size(); ++i){
    if(out[i]!=ans[i]){ 
      INFO("At index value " + std::to_string(i) + " your vector was incorrect.");
      REQUIRE(out[i] == ans[i]);
    }
  }
}
  

TEST_CASE("test_insert 1", "[weight=5]"){
    std::vector<int> nodes;
    nodes.push_back(58); //         58
    nodes.push_back(35); //
    nodes.push_back(72); //    35        72
    nodes.push_back(40); //
    nodes.push_back(10); //  10  40    61  80
    nodes.push_back(80); //
    nodes.push_back(93); // 0 19            93
    nodes.push_back(0); //
    nodes.push_back(19); //
    nodes.push_back(61); //

    BST<int, int> tree;
    for(size_t i = 0; i < nodes.size(); i++){
        tree.insert(nodes[i],i);
    }

    std::sort(nodes.begin(), nodes.end());

    match_walk(tree, nodes);
}

TEST_CASE("test_insert 2", "[weight=5]"){
    std::vector<std::string> nodes;
    nodes.push_back("Hi");
    nodes.push_back("My"); 
    nodes.push_back("Name"); 
    nodes.push_back("Is"); 
    nodes.push_back("What");
    nodes.push_back("My"); 
    nodes.push_back("Name"); 
    nodes.push_back("Is"); 
    nodes.push_back("Who");

    BST<std::string, int> tree;
    std::set<std::string> temp;
    for(size_t i = 0; i < nodes.size(); i++){
        tree.insert(nodes[i],i);
        temp.insert(nodes[i]);
    }

    nodes.assign(temp.begin(), temp.end());
    std::sort(nodes.begin(), nodes.end());

    match_walk(tree, nodes);
}

TEST_CASE("test_insert 3", "[weight=5]"){
    std::vector<std::string> nodes = file_to_list("../tests/data/sonnets1.txt");

    BST<std::string, int> tree;
    std::set<std::string> temp;
    for(size_t i = 0; i < nodes.size(); i++){
        tree.insert(nodes[i],i);
        temp.insert(nodes[i]);
    }

    nodes.assign(temp.begin(), temp.end());
    std::sort(nodes.begin(), nodes.end());

    match_walk(tree, nodes);
}

TEST_CASE("test_find 1", "[weight=5]"){
    std::vector<int> nodes;
    nodes.push_back(58); //         58
    nodes.push_back(35); //
    nodes.push_back(72); //    35        72
    nodes.push_back(40); //
    nodes.push_back(10); //  10  40    61  80
    nodes.push_back(80); //
    nodes.push_back(93); // 0 19            93
    nodes.push_back(0); //
    nodes.push_back(19); //
    nodes.push_back(61); //

    BST<int, int> tree;
    for(size_t i = 0; i < nodes.size(); i++){
        tree.insert(nodes[i],i);
    }

    for(size_t i = 0; i < nodes.size(); i++){
        size_t temp = tree.find(nodes[i]);
        REQUIRE(temp == i);
    }
}

TEST_CASE("test_find 2", "[weight=5]"){
    std::vector<std::string> nodes;
    nodes.push_back("Hi");
    nodes.push_back("My"); 
    nodes.push_back("Name"); 
    nodes.push_back("Is"); 
    nodes.push_back("What");
    nodes.push_back("My"); 
    nodes.push_back("Name"); 
    nodes.push_back("Is"); 
    nodes.push_back("Who");

    BST<std::string, int> tree;
    std::set<std::string> temp;
    std::map<std::string, size_t> values;
    for(size_t i = 0; i < nodes.size(); i++){
        tree.insert(nodes[i],i);
        temp.insert(nodes[i]);
        if(! values.count(nodes[i])){
            values[nodes[i]]=i;
        }
    }

    for(size_t i = 0; i < nodes.size(); i++){
        size_t temp = tree.find(nodes[i]);
        REQUIRE(temp == values[nodes[i]]);
    }
}

TEST_CASE("test_find 3", "[weight=5]"){
    std::vector<std::string> nodes = file_to_list("../tests/data/sonnets1.txt");

    BST<std::string, int> tree;
    std::set<std::string> temp;
    std::map<std::string, size_t> values;
    for(size_t i = 0; i < nodes.size(); i++){
        tree.insert(nodes[i],i);
        temp.insert(nodes[i]);
        if(! values.count(nodes[i])){
            values[nodes[i]]=i;
        }
    }

    for(size_t i = 0; i < nodes.size(); i++){
        size_t temp = tree.find(nodes[i]);
        REQUIRE(temp == values[nodes[i]]);
    }
}

TEST_CASE("test_remove (0 child)", "[weight=5]"){
    std::vector<int> nodes;
    nodes.push_back(58); //         58
    nodes.push_back(35); //
    nodes.push_back(72); //    35        72
    nodes.push_back(40); //
    nodes.push_back(10); //  10  40    61  80
    nodes.push_back(80); //
    nodes.push_back(93); // 0 19            93
    nodes.push_back(0); //
    nodes.push_back(19); //
    nodes.push_back(61); //

    BST<int, int> tree;
    for(size_t i = 0; i < nodes.size(); i++){
        tree.insert(nodes[i],i);
    }

    tree.remove(40);
    tree.remove(93);

    nodes.clear(); 
    nodes.push_back(58); 
    nodes.push_back(35); 
    nodes.push_back(72); 
    nodes.push_back(10); 
    nodes.push_back(80); 
    nodes.push_back(0); 
    nodes.push_back(19); 
    nodes.push_back(61); 


    std::sort(nodes.begin(), nodes.end());

    match_walk(tree, nodes);
}

TEST_CASE("test_remove (1 child)", "[weight=5]"){
    BST<int, int> tree;
    tree.insert(5, 0);
    tree.insert(4, 1);
    tree.insert(9, 2);
    tree.insert(10, 3);
    tree.insert(12, 4);
    tree.insert(2, 7);

    tree.remove(9);
    tree.remove(10);

    std::vector<int> nodes;
    nodes.push_back(5);
    nodes.push_back(4);
    nodes.push_back(12);
    nodes.push_back(2);

    std::sort(nodes.begin(), nodes.end());

    match_walk(tree, nodes);
}

TEST_CASE("test_remove (2 child)", "[weight=5]"){
    BST<int, int> tree;
    tree.insert(5, 0);
    tree.insert(4, 1);
    tree.insert(9, 2);
    tree.insert(12, 3);
    tree.insert(7, 4);
    tree.insert(8, 5);
    tree.insert(11, 6);
    tree.insert(2, 7);

    tree.remove(9);
    tree.remove(5);

    std::vector<int> nodes;
    nodes.push_back(4);
    nodes.push_back(12);
    nodes.push_back(7);
    nodes.push_back(8);
    nodes.push_back(11);
    nodes.push_back(2);

    std::sort(nodes.begin(), nodes.end());

    match_walk(tree, nodes);
}

TEST_CASE("test_listBuild 1", "[weight=5]"){
    std::vector<std::pair<std::string, int> >  nodes = file_to_listPair("../tests/data/file1.txt");

    BST<std::string, int> tree;
    std::set<std::string> temp;
    for(size_t i = 0; i < nodes.size(); i++){
        tree.insert(nodes[i].first,nodes[i].second);
        temp.insert(nodes[i].first);
    }

    std::vector<std::string> n2;
    n2.assign(temp.begin(), temp.end());
    std::sort(n2.begin(), n2.end());

    match_walk(tree, n2);
}

TEST_CASE("test_listBuild 2", "[weight=5]"){
    std::vector<std::pair<std::string, int> >  nodes = file_to_listPair("../tests/data/file2.txt");

    BST<std::string, int> tree;
    std::set<std::string> temp;
    for(size_t i = 0; i < nodes.size(); i++){
        tree.insert(nodes[i].first,nodes[i].second);
        temp.insert(nodes[i].first);
    }

    std::vector<std::string> n2;
    n2.assign(temp.begin(), temp.end());
    std::sort(n2.begin(), n2.end());

    match_walk(tree, n2);
}

TEST_CASE("test_listBuild 3", "[weight=5]"){
    std::vector<std::pair<std::string, int> >  nodes = file_to_listPair("../tests/data/file3.txt");

    BST<std::string, int> tree;
    std::set<std::string> temp;
    for(size_t i = 0; i < nodes.size(); i++){
        tree.insert(nodes[i].first,nodes[i].second);
        temp.insert(nodes[i].first);
    }

    std::vector<std::string> n2;
    n2.assign(temp.begin(), temp.end());
    std::sort(n2.begin(), n2.end());

    match_walk(tree, n2);
}

TEST_CASE("test_allBuild 1", "[weight=5]"){
    std::vector<std::pair<std::string, int> >  nodes = file_to_listPair("../tests/data/file1_unique.txt");

    std::vector<int> ans = {0, 2, 4};
    std::vector<int> out = allBuild(nodes);

    match_vector(out, ans);
}

TEST_CASE("test_allBuild 2", "[weight=5]"){
    std::vector<std::pair<std::string, int> >  nodes = file_to_listPair("../tests/data/file2.txt");

    std::vector<int> ans = {0, 0, 0, 55040, 168768, 104448, 30016, 4352, 256};
    std::vector<int> out = allBuild(nodes);

    match_vector(out, ans);
}

TEST_CASE("test_allBuild 3", "[weight=5]"){
    std::vector<std::pair<std::string, int> >  nodes = file_to_listPair("../tests/data/file4.txt");

    std::vector<int> ans = {0, 0, 40, 64, 16};
    std::vector<int> out = allBuild(nodes);

    match_vector(out, ans);
}