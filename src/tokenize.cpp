#include "tokenize.h"
#include <algorithm>
#include <iostream> //REMOVE(plesslie): DEBUG
//------------------------------------------------------------------------------
Tokens tokenize(std::istream& is)
{
    Tokens ret;
    std::string str;
    while (is >> str) {
        do {
            const auto pos = str.find_first_of("()");
            ret.push_back(str.substr(0, pos));

            if (pos == std::string::npos) break;
            
            ret.push_back(str.substr(pos, 1));
            str = str.substr(pos+1);

        } while(!str.empty());
    }

    auto pos = std::remove_if(std::begin(ret), std::end(ret),
                              [](const std::string& s) { return s.empty(); });
    ret.erase(pos, std::end(ret));
    return ret;
}
//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Tokens& tokens)
{
    os << "Tokens( ";
    for (const auto token: tokens) os << "'" << token << "' ";
    os << ")";
    return os;
}
