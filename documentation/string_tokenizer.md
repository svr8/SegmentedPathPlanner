# String Tokenizer
string_tokenizer is used by arena parse map files in this project

**Properties** 
| Name  | Data Type | Description |
| ------------- | ------------- | ------------- |
| val | vector<string> | holds current token |
| it | vector<string>::iterator | contains list of tokens |


**Constructors**
| Params | Description |
| ------------- | ------------- |
| - | Nothing |
| str, delim | string is the target string and delim is delimiter character for tokenizing str |

**Methods**
| Name | Return | Params | Description |
| ------------- | ------------- | ------------- | ------------- |
has_token | bool | - | returns true if there are any more tokens left |
| next | string | - | returns next token |
| reset_iterator | void | - | resets iterator to the starting token of `it` |
