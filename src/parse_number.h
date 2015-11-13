#ifndef PARSE_NUMBER__H_
#define PARSE_NUMBER__H_

#include <string>
#include <cstdint>

typedef int64_t Number;

// digit := [0-9]
bool is_digit(char c);

// number := <digit> | <digit><number>
bool is_number(std::string::const_iterator begin, std::string::const_iterator end);

bool is_number(const std::string& num);

// signed_number := <number> | '+'<number> | '-'<number>
bool is_signed_number(const std::string& num);

Number parse_digit(char c);

#endif // PARSE_NUMBER__H_
