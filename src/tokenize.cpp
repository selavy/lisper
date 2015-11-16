#include "tokenize.h"
#include <algorithm>
#include <iostream> //REMOVE(plesslie): DEBUG
#include "infix_iterator.h"
//------------------------------------------------------------------------------
Tokens tokenize(std::istream& is)
{
    Tokens ret;
    char c;
    std::string curr;
    std::string tmp;
    bool inquote = false;

    while(is.get(c)) {
        if (inquote && c != '"') {
            if (c == ';') {
                throw std::runtime_error("Found ';' character inside string literal!");
            }
            curr += c;
        }
        else {
            switch (c) {
            case '"':
                if (inquote) {
                    curr += '"';
                    ret.push_back(curr);
                    curr = "";
                }
                else {
                    inquote = true;
                    curr = c;
                }
                break;
            case ' ' : // skip whitespace
            case '\t':
            case '\n':
            case '\r':
                if (!curr.empty()) {
                    ret.push_back(curr);
                    curr = "";
                }
                break;
            case ';': // comment
                std::getline(is, tmp, '\n'); // get rest of line
                break;
            case '(': // begin expr
                if (!curr.empty()) {
                    ret.push_back(curr);
                    curr = "";
                }
                ret.push_back("(");
                break;
            case ')': // end expr
                if (!curr.empty()) {
                    ret.push_back(curr);
                    curr = "";
                }
                ret.push_back(")");
                break;
            default:
                curr += c;
            }
        }
    }
    if (!curr.empty()) ret.push_back(curr);
    
    return ret;
}
//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Tokens& tokens)
{
    os << "Tokens( '";
    std::copy(std::begin(tokens), std::end(tokens),
              infix_ostream_iterator<Tokens::value_type>(os, "', '"));
    os << "' )";
    return os;
}
