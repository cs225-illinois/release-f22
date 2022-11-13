/**
 * Program for printing a huffman tree, given .huff file.

   Note: The frequencies will not be printed because the file format for storing the tree
   doesn't save the frequencies.
 */
#include <string>

#include "binary_file_reader.h"
#include "huffman_tree.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "error: huffman tree file path is not specified" << endl;
        exit(1);
    }

    string inputFileName = argv[1];

    ifstream myFile(inputFileName);
    if(myFile.fail()){
        cerr << "error: input file \"" << inputFileName << "\" does not exist." << endl;
        exit(1);
    }

    BinaryFileReader bfile(inputFileName);
    HuffmanTree htree(bfile);
    htree.print(cout);
}
