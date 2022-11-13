#include <catch2/catch_test_macros.hpp>
#include "binary_file_reader.h"
#include "decoder.h"
#include "encoder.h"
#include "huffman_tree.h"

#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

void duplicateChar(char c, int freq, ostream& s) {
  for (int i = 0; i < freq; i++) {
    s << c;
  }
}

void buildText() {
  ofstream text("../tests/text.txt");
  duplicateChar('a', 20, text);
  duplicateChar('b', 30, text);
  duplicateChar('c', 60, text);
  duplicateChar('d', 40, text);
  text.close();
}

void buildText2() {
  ofstream text( "../tests/text.txt");
  duplicateChar('a', 5, text);
  duplicateChar('b', 6, text);
  duplicateChar('c', 12, text);
  duplicateChar('d', 13, text);
  duplicateChar('e', 7, text);
  duplicateChar('f', 8, text);
  text.close();
}

void buildText(int start) {
    ofstream text("../tests/text.txt");
    for (char c = 'a'; c < 'f'; ++c) {
        duplicateChar(c, start, text);
        start *= 2;
    }
    text << endl;
    text.close();
}

void compareBinaryFiles(string yourFile, string ourFile) {
  ifstream yourBinary(yourFile, ios::binary);
  stringstream yours;
  yours << yourBinary.rdbuf();
  ifstream ourBinary(ourFile, ios::binary);
  stringstream ours;
  ours << ourBinary.rdbuf();
  if (yours.str() != ours.str()) {
    FAIL( "Your binary file \"" + yourFile + "\" does not match our binary file \"" + ourFile + "\"");
  }
}

HuffmanTree constructTree( string inputFile ) {
  ifstream toEncode( inputFile );
  stringstream data;
  data << toEncode.rdbuf();
  string str(data.str());
  unordered_map<char, int> freqs;
  for (size_t i = 0; i < str.length(); ++i) {
    freqs[str[i]]++;
  }
  vector<Frequency> buildWith;
  for (auto it = freqs.begin(); it != freqs.end(); ++it) {
    buildWith.push_back(Frequency(it->first, it->second));
  }
  return HuffmanTree(buildWith);
}

TEST_CASE("test_remove_smallest", "[weight=1]") {
  vector<Frequency> single;
  vector<Frequency> merge;
  for (int i = 1; i < 5; i++) {
    single.push_back(Frequency('a'+2*i, 2*i));
    merge.push_back(Frequency('a'+i, i));
  }
  Frequency expected1 = HuffmanTree::testRemoveSmallest(single, merge);
  REQUIRE(expected1 == merge[0]);
  single[0] = merge[0];
  Frequency expected2 = HuffmanTree::testRemoveSmallest(single, merge);
  REQUIRE(expected2 == single[0]);
}

TEST_CASE("test_encoder_binary", "[weight=1]") {
  buildText();
  encoder::encodeFile("../tests/text.txt", "../tests/test.bin", "../tests/tree.huff");
  compareBinaryFiles("../tests/test.bin", "../tests/soln_test.bin");
}

TEST_CASE("test_encoder_binary2", "[weight=1]") {
  buildText2();
  encoder::encodeFile("../tests/text.txt", "../tests/test.bin", "../tests/tree.huff");
  compareBinaryFiles("../tests/test.bin", "../tests/soln_test2.bin");
}

TEST_CASE("test_encoder_writetree", "[weight=1]") {
  buildText();
  encoder::encodeFile("../tests/text.txt", "../tests/test.bin", "../tests/tree.huff");
  compareBinaryFiles("../tests/tree.huff", "../tests/soln_tree.huff");
}

TEST_CASE("test_encoder_writetree2", "[weight=1]") {
  buildText2();
  encoder::encodeFile("../tests/text.txt", "../tests/test.bin", "../tests/tree.huff");
  compareBinaryFiles("../tests/tree.huff", "../tests/soln_tree2.huff");
}

TEST_CASE("test_decode", "[weight=1]") {
  buildText();
  HuffmanTree htree = constructTree("../tests/text.txt");
  BinaryFileReader bfile("../tests/soln_test.bin");
  string decoded = htree.decodeFile(bfile);
  ifstream in("../tests/text.txt");
  stringstream expected;
  expected << in.rdbuf();
  REQUIRE(expected.str() == decoded);
}

TEST_CASE("test_decode2", "[weight=1]") {
  buildText2();
  HuffmanTree htree = constructTree("../tests/text.txt");
  BinaryFileReader bfile("../tests/soln_test2.bin");
  string decoded = htree.decodeFile(bfile);
  ifstream in("../tests/text.txt");
  stringstream expected;
  expected << in.rdbuf();
  REQUIRE(expected.str() == decoded);
}

TEST_CASE("test_decode_readtree", "[weight=1]") {
  buildText();
  decoder::decodeFile("../tests/soln_test.bin", "../tests/soln_tree.huff", "../tests/out.txt");
  stringstream expected;
  stringstream decoded;
  ifstream expect("../tests/text.txt");
  expected << expect.rdbuf();
  ifstream out("../tests/out.txt");
  decoded << out.rdbuf();
  REQUIRE(expected.str() == decoded.str());
}

TEST_CASE("test_decode_readtree2", "[weight=1]") {
  buildText2();
  decoder::decodeFile("../tests/soln_test2.bin", "../tests/soln_tree2.huff", "../tests/out.txt");
  stringstream expected;
  stringstream decoded;
  ifstream expect("../tests/text.txt");
  expected << expect.rdbuf();
  ifstream out("../tests/out.txt");
  decoded << out.rdbuf();
  REQUIRE(expected.str() == decoded.str());
}

TEST_CASE("test_the_works", "[weight=5][valgrind]") {
  buildText(2);
  encoder::encodeFile("../tests/text.txt", "../tests/test.bin", "../tests/tree.huff");
  decoder::decodeFile("../tests/test.bin", "../tests/tree.huff", "../tests/out.txt");
  stringstream expected;
  stringstream decoded;
  ifstream expect("../tests/text.txt");
  expected << expect.rdbuf();
  ifstream out("../tests/out.txt");
  decoded << out.rdbuf();
  REQUIRE(expected.str() == decoded.str());
  compareBinaryFiles("../tests/tree.huff", "../tests/soln_tree_2.huff");
  compareBinaryFiles("../tests/test.bin", "../tests/soln_test_2.bin");
}
