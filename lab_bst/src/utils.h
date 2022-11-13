#pragma once

#include <utility>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cassert>

/**
* Functions for the removal of whitespace to the left or right of a string (or both)
*
* @param str The string being processed
*/
std::string TrimRight(const std::string & str);
std::string TrimLeft(const std::string & str);
std::string Trim(const std::string & str);

/**
 * Given a string and character, split the string by the character and store in a vector
 * A 'split' string treats the character as a breakpoint and creates a separate item
 * in the output vector for each substring. 
 * 
 * NOTE: The separator character is not included in the substrings.
 * 
 * The total number of substrings created (the length of fields) is returned 
 *  
 * @param str1 The string being split
 * @param sep The separator character
 * @param fields The string vector storing all substrings created by the split
 */
int SplitString(const std::string & str1, char sep, std::vector<std::string> &fields);


/**
 * Takes a filename and reads in all the text from the file
 * Newline characters are also just characters in ASCII
 * 
 * @param filename The name of the file that will fill the string
 */
std::vector<std::pair<std::string, int> > file_to_listPair(const std::string& filename);

std::vector<std::string> file_to_list(const std::string& filename);