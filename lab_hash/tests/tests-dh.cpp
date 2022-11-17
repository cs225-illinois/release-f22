#include <catch2/catch_test_macros.hpp>

#include "cs225/textfile.h"
#include "dhhashtable.h"

#include <algorithm>
#include <map>
#include <vector>

using namespace std;

TEST_CASE("DH::testRemoveEASY", "[valgrind][weight=6]")
{
	TextFile infile("../tests/textEasy.txt");
	DHHashTable<string, int> hashTable(32);
	while (infile.good())
	{
		string word = infile.getNextWord();
		hashTable.insert(word, 0);
	}
	hashTable.insert("__SENTINEL__", 0);
	if (!hashTable.keyExists("__SENTINEL__"))
		FAIL("Insert did not work");
	hashTable.remove("all");
	if (hashTable.keyExists("all"))
		FAIL("Did not remove key: 'all'");
	hashTable.remove("base");
	if (hashTable.keyExists("base"))
		FAIL("Did not remove key: 'base'");

	REQUIRE(true);
}

TEST_CASE("DH::testRemoveHard", "[valgrind][weight=10]")
{
	TextFile infile("../tests/textHard.txt");
	DHHashTable<string, int> hashTable(32);
	while (infile.good())
	{
		string word = infile.getNextWord();
		if (hashTable.keyExists(word))
		{
			hashTable.remove(word);
			if (hashTable.keyExists(word))
				FAIL("Did not remove key on update");
			hashTable.insert(word, 1);
		}
		else
			hashTable.insert(word, 0);
	}
	hashTable.insert("__SENTINEL__", 0);
	if (!hashTable.keyExists("__SENTINEL__"))
		FAIL("Insert did not work");
	hashTable.remove("to");
	if (hashTable.keyExists("to"))
		FAIL("Did not remove key: 'to'");
	hashTable.remove("decided");
	if (hashTable.keyExists("decided"))
		FAIL("Did not remove key: 'decided'");

	REQUIRE(true);
}

TEST_CASE("DH::testResizeOnce", "[valgrind][weight=7]")
{
	TextFile infile("../tests/textLong.txt");
	DHHashTable<string, int> hashTable(16);
	int val = 0;
	while (infile.good())
	{
		string word = infile.getNextWord();
		if (!hashTable.keyExists(word))
		{
			val++;
			hashTable.insert(word, val);
		}
	}
	REQUIRE(hashTable.tableSize() >= val / 0.7);
	if (hashTable.find("got") != 2)
		FAIL("Didn't copy over existing lists properly on resize");
	if (hashTable.find("to") != 3)
		FAIL("Didn't re-hash keys properly");

	REQUIRE(true);
}

TEST_CASE("DH::testResizeAll", "[valgrind][weight=11]")
{
	vector<string> strings;
	for (int i = 'a'; i <= 'z'; i++)
	{
		string word = "";
		word += ((char)i);
		strings.push_back(word);
	}
	// cout << strings.size() << endl;
	DHHashTable<string, int> hashTable(16);
	int val = 0;
	for (unsigned int i = 0; i < strings.size(); i++)
	{
		val++;
		hashTable.insert(strings[i], val);
	}
	REQUIRE(hashTable.tableSize() >= strings.size() / 0.7);
	for (int i = 'a'; i <= 'z'; i++)
	{
		string word = "";
		word += ((char)i);
		if (!hashTable.keyExists(word))
			FAIL("Missed a key during resize: " + word);
	}

	REQUIRE(true);
}

TEST_CASE("DH::testInsertEasy", "[valgrind][weight=6]")
{
	TextFile infile("../tests/textEasy.txt");
	DHHashTable<string, int> hashTable(32);
	int val = 0;
	while (infile.good())
	{
		val++;
		string word = infile.getNextWord();
		hashTable.insert(word, val);
	}
	if (!hashTable.keyExists("all"))
		FAIL("Did not insert key: 'all'");
	if (!hashTable.keyExists("base"))
		FAIL("Did not insert key: 'base'");
	if (hashTable.find("are") != 4)
		FAIL("Did not insert key-value pair properly");

	REQUIRE(true);
}

TEST_CASE("DH::testInsertHard", "[valgrind][weight=10]")
{
	TextFile infile("../tests/textHard.txt");
	DHHashTable<string, int> hashTable(32);
	int val = 0;
	while (infile.good())
	{
		string word = infile.getNextWord();
		if (hashTable.keyExists(word))
			hashTable.remove(word);
		hashTable.insert(word, ++val);
	}
	if (!hashTable.keyExists("has"))
		FAIL("Did not insert properly key: 'has'");
	if (!hashTable.keyExists("far"))
		FAIL("Did not insert properly key: 'far'");
	if (hashTable.find("want") != 13)
		FAIL("Did not insert key-value pair properly");

	REQUIRE(true);
}
