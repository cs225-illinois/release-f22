#include "utils.h"
#include <sstream>
#include <fstream>
#include <fenv.h>
#include <signal.h>
#include <vector>

std::string TrimRight(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(tmp.find_last_not_of(" ") + 1);
}

std::string TrimLeft(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(0, tmp.find_first_not_of(" "));
}

std::string Trim(const std::string & str) {
    std::string tmp = str;
    return TrimLeft(TrimRight(str));
}

//
// Split string str into fields separated by sep
// field numbers start at 0
//
int SplitString(const std::string & str1, char sep, std::vector<std::string> &fields) {
    std::string str = str1;
    std::string::size_type pos;
    while((pos=str.find(sep)) != std::string::npos) {
        fields.push_back(str.substr(0,pos));
        str.erase(0,pos+1);  
    }
    fields.push_back(str);
    return fields.size();
}

/**
 * Takes a filename and reads in all the text from the file
 * Newline characters are also just characters in ASCII
 * 
 * @param filename The name of the file that will fill the string
 */
std::vector<std::pair<std::string, int> > file_to_listPair(const std::string& filename){
  std::ifstream text(filename);

  std::string word;
  std::vector<std::pair<std::string, int>> output;
  int count = 0;
  while(text >> word){
      std::pair<std::string, int> temp(word, count);
      output.push_back(temp);
      count++;
  }
  return output;
}

/**
 * Takes a filename and reads in all the text from the file
 * Newline characters are also just characters in ASCII
 * 
 * @param filename The name of the file that will fill the string
 */
std::vector<std::string> file_to_list(const std::string& filename){
  std::ifstream text(filename);

  std::string word;
  std::vector<std::string> output;
  while(text >> word){
      output.push_back(word);
  }
  return output;
}