#ifndef TOKENIZE__H_
#define TOKENIZE__H_

#include <string>
#include <vector>
#include <istream>
#include <ostream>

typedef std::string Token;
typedef std::vector<Token> Tokens;

Tokens tokenize(std::istream& is);

std::ostream& operator<<(std::ostream& os, const Tokens& tokens);

#endif // TOKENIZE__H_
