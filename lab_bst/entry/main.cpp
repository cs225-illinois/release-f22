/**
 * @file main.cpp
 * Contains code for testing the BST class.
 */

#include <iostream>
#include <sstream>
#include <string>
#include "bst.h"
#include "binarytree/coloredout.h"

using namespace std;

void printHeader(const string& headline)
{
    cout << string(64, colored_out::BORDER_CHAR) << endl;
    colored_out::output_bold(headline);
    cout << endl << string(64, colored_out::BORDER_CHAR) << endl;
}

void printBefore()
{
    cout << "~";
    colored_out::output_bold("Before");
    cout << "~" << endl;
}

void printAfter(int inserted)
{
    cout << endl << "~";
    colored_out::output_bold("After insert(");
    colored_out::output_bold(inserted);
    colored_out::output_bold(")");
    cout << "~" << endl;
}

void printEnd()
{
    cout << endl << endl;
}

void exampleFind()
{
    BST<string, string> tree;
    printHeader("Running Find");
    tree.insert("C", "C++");
    tree.insert("free", "delete");
    tree.insert("malloc", "new");
    tree.insert("bool", "void");
    tree.print();
    tree.printFunctionOrder();
    cout << "find(C) -> " << tree.find("C") << endl;
    cout << "find(free) -> " << tree.find("free") << endl;
    cout << "find(malloc) -> " << tree.find("malloc") << endl;
    cout << "find(bool) -> " << tree.find("bool") << endl;
    cout << "find(NOTPRESENT) -> " << tree.find("NOTPRESENT") << endl;
    printEnd();
}

void exampleRemove()
{
    BST<int, int> tree;
    printHeader("Running Find");
    tree.insert(5, 0);
    tree.insert(4, 0);
    tree.insert(9, 0);
    tree.insert(12, 0);
    tree.insert(7, 0);
    tree.insert(8, 0);
    tree.insert(11, 0);
    tree.insert(2, 0);
    tree.print();
    tree.remove(2);
    tree.print();
    tree.remove(9);
    tree.print();
    printEnd();
}

void exampleRemove2()
{
    BST<int, int> tree;
    printHeader("Running Find");
    tree.insert(5, 0);
    tree.insert(4, 0);
    tree.insert(9, 0);
    tree.insert(7, 0);
    tree.insert(8, 0);
    tree.insert(2, 0);
    tree.print();
    tree.remove(2);
    tree.print();
    tree.remove(9);
    tree.print();
    printEnd();
}

void exampleBuildFromList()
{
    std::vector<std::pair<std::string, int>> outList = file_to_listPair("../tests/data/sonnets1.txt");

    BST<string, int> tree = listBuild(outList);

    cout << tree.height() << endl;

    /*
    for(unsigned i = 0; i < outList.size(); i++){
        cout << outList[i].first << " " << outList[i].second << endl;
    }
    */
}

void exampleAllBuild()
{
    std::vector<std::pair<std::string, int>> inList = file_to_listPair("../tests/data/file4.txt");

    std::vector<int> out = allBuild(inList);

    for(unsigned i = 0; i < out.size(); i++){
        cout << out[i] << endl;
    }
}

void exampleManyInsertions()
{
    BST<int, string> tree;
    printHeader("Running Many Insertions");
    tree.insert(94, "data for 94");
    tree.insert(87, "data for 87");
    tree.insert(61, "data for 61");
    tree.insert(96, "data for 96");
    tree.insert(76, "data for 76");
    tree.insert(92, "data for 92");
    tree.insert(42, "data for 42");
    tree.insert(78, "data for 78");
    tree.insert(17, "data for 17");
    tree.insert(11, "data for 11");
    tree.insert(41, "data for 41");
    tree.insert(95, "data for 95");
    tree.insert(36, "data for 36");
    tree.insert(26, "data for 26");
    tree.insert(23, "data for 23");
    tree.insert(93, "data for 93");
    tree.insert(31, "data for 31");
    tree.insert( 3, "data for 3");
    tree.insert(45, "data for 45");
    tree.insert(18, "data for 18");
    tree.insert(73, "data for 73");
    tree.insert(24, "data for 24");
    tree.insert(74, "data for 74");
    tree.insert( 1, "data for 1");
    tree.insert(71, "data for 71");
    tree.insert(82, "data for 82");
    tree.print();
    printEnd();
}

void exampleManyRemovals()
{
    BST<int, string> tree;
    printHeader("Running Many Removals");
    tree.insert(94, "data for 94");
    tree.insert(87, "data for 87");
    tree.insert(61, "data for 61");
    tree.insert(96, "data for 96");
    tree.insert(76, "data for 76");
    tree.insert(92, "data for 92");
    tree.insert(42, "data for 42");
    tree.insert(78, "data for 78");
    tree.insert(17, "data for 17");
    tree.insert(11, "data for 11");
    tree.insert(41, "data for 41");
    tree.insert(95, "data for 95");
    tree.insert(36, "data for 36");
    tree.insert(26, "data for 26");
    tree.insert(23, "data for 23");
    tree.insert(93, "data for 93");
    tree.insert(31, "data for 31");
    tree.insert( 3, "data for 3");
    tree.insert(45, "data for 45");
    tree.insert(18, "data for 18");
    tree.insert(73, "data for 73");
    tree.insert(24, "data for 24");
    tree.insert(74, "data for 74");
    tree.insert( 1, "data for 1");
    tree.insert(71, "data for 71");
    tree.insert(82, "data for 82");
    tree.remove(95);
    tree.remove(94);;
    tree.remove(61);
    tree.remove(76);
    tree.remove(73);
    tree.remove(71);
    tree.print();
    printEnd();
}

int main(int argc, char** argv)
{
    exampleAllBuild();

    return 0;
}
