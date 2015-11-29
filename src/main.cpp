#include <iostream>
#include <sstream>
#include <locale>
#include <cstdlib>
#include <deque>
#include <vector>
#include <list>
#include "tokenize.h"
#include "number.h"
#include "integer.h"
#include "str.h"
#include "boolean.h"
#include "pair.h"
#include "symbol.h"
#include "empty.h"

template <class CONT>
std::list<typename CONT::value_type> toList(const CONT& container)
{
    std::list<typename CONT::value_type> ret;
    for (const auto& it: container)
        ret.push_back(it);
    return ret;
}

ObjectPtr evaluate(std::list<Token>& tokens)
{
    // Base cases:
    // [LET (TOKEN = first token in tokens, C = first character of token)]
    // tokens empty       -> Empty()
    // C ~ [1-9]          -> Integer() [TODO: expand numerical types]
    // C ~ "              -> String()
    // C ~ #[tf]          -> Boolean()
    // C ~ #\[a-zA-Z1-9]+ -> Character() [TODO: add unicode character class]
    // anything else      -> Symbol()

    // Recursive cases:
    // C ~ (              -> List()
    
    if (tokens.empty()) {
        return ObjectPtr(new Empty);
    }

    Token token = tokens.front();
    tokens.pop_front();
    if (std::isdigit(token[0])) {
        return ObjectPtr(new Integer(token.c_str()));
    }
    else if (token[0] == '"') {
        return ObjectPtr(new String(token.c_str()));
    }
    else if (Boolean::isBoolean(token.c_str())) {
        return ObjectPtr(new Boolean(token.c_str()));
    }
    else if (token[0] == '(') {
        //[TODO: implement recursive case]
        return ObjectPtr(new Pair(evaluate(tokens).release(), ObjectPtr(new Empty).release()));
    }
    else if (token[0] == ')') {
        return ObjectPtr(new Empty);
    }
    else {
        return ObjectPtr(new Symbol(token.c_str()));
    }    
}

ObjectPtr process(const char* str)
{
    std::cout << "> " << str << std::endl;
    std::stringstream ss;
    ss << str;
    std::list<Token> tokens = toList(tokenize(ss));
    return evaluate(tokens);
}

int main(int argc, char** argv)
{
    std::vector<std::string> cases = {
        "\"Hello\"",
        "1",
        "100",
        "10000",
        "#t",
        "#f",
        "(+ 1 2)"
    };

    for (const auto& c : cases)
    {
        ObjectPtr res = std::move(process(c.c_str()));
        if (res) {
            std::cout << "  " << *res << std::endl;
        }
        else {
            std::cout << "(null)" << std::endl;
        }
    }
    
    return 0;
}
