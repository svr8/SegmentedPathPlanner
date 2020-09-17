#include <string_tokenizer.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

string_tokenizer::string_tokenizer() {
}

string_tokenizer::string_tokenizer(string& str, char delim) {
  stringstream ss(str);
  string s;

  while(getline(ss, s, delim))
    val.push_back(s);
  
  it = val.begin();
}

vector<string>::iterator string_tokenizer::get_iterator() {
  return it;
}

bool string_tokenizer::has_token() {
  return it != val.end();
}

string string_tokenizer::next() {
  string str = *(it);
  it++;
  return str;
}

void string_tokenizer::reset_iterator() {
  it = val.begin();
}

