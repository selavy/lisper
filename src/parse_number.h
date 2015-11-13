#ifndef PARSE_NUMBER__H_
#define PARSE_NUMBER__H_

#include <string>

// digit := [0-9]
bool is_digit(char c);

// number := <digit> | <digit><number>
bool is_number(const std::string& num);

#endif // PARSE_NUMBER__H_
