#ifndef STRING_TOKENIZER_INCLUDE
#define STRING_TOKENIZER_INCLUDE

#include <string>
#include <vector>

using namespace std;

// string_tokenizer is used by arena parse map files in this project
class string_tokenizer {
  private:
    vector<string> val;
    vector<string>::iterator it;
  
  public:
    string_tokenizer();
    string_tokenizer(string& str, char delim);
    vector<string>::iterator get_iterator();
    bool has_token();
    string next();
    void reset_iterator();
};

#endif