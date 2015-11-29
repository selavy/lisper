#include <iostream>
#include <sstream>
#include <locale>
#include <cstdlib>
#include <deque>
#include <vector>
#include "tokenize.h"
#include "number.h"
#include "integer.h"
#include "str.h"
#include "boolean.h"
#include "abstract_syntax_tree.h"

template <class CONT>
std::deque<typename CONT::value_type> toDeque(const CONT& container)
{
    std::deque<typename CONT::value_type> ret;
    for (const auto& it: container)
        ret.push_back(it);
    return ret;
}

ObjectPtr interpretSimpleToken(Token token)
{
    if (std::isdigit(token[0])) {
        return ObjectPtr(new Integer(token.c_str()));
    }
    else if (token[0] == '"') {
        return ObjectPtr(new String(token.c_str()));
    }
    else if (Boolean::isBoolean(token.c_str())) {
        return ObjectPtr(new Boolean(token.c_str()));
    }
    else {
        throw std::runtime_error("Unrecognized token: " + token + "!");
    }
}

ObjectPtr readFromTokens(std::deque<Token>& tokens)
{
    if (tokens.empty()) {
        throw std::runtime_error("Unexpected EOF!");
    }

    for (const auto& token: tokens) {
        if (token == "(") {
             
        }
        else if (token == ")") {
            continue;
        }
        else {
            return interpretSimpleToken(token);
        }
    }

    return ObjectPtr();

    // Token token = tokens.front();
    // tokens.pop_front();
    // if (token == "(") {
    //     std::cout << "BEGIN EXPR\n";
    //     // while (token != ")") {
            
    //     // }
    // }
    // // else if (token == ")") {
    // //     std::cout << "END EXPR\n";
    // // }
    // else if (token[0] == '"') {
    //     return ObjectPtr(new String(token.c_str()));
    // }
    // else if (std::isdigit(token[0])) {
    //     return ObjectPtr(new Integer(token.c_str()));
    // }
    // else if (Boolean::isBoolean(token.c_str())) {
    //     return ObjectPtr(new Boolean(token.c_str()));
    // }
    // else {
    //     // check if primitive
    //     std::cout << "SYMBOL\n";
    // }
    // return ObjectPtr();
}

ObjectPtr process(const char* str)
{
    std::cout << "> " << str << std::endl;
    std::stringstream ss;
    ss << str;
    std::deque<Token> tokens = toDeque(tokenize(ss));
    return readFromTokens(tokens);
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

    // token is either part of:
    // list, if starts with "("
    // string, if starts with '"'
    // number, if starts with digit
    // boolean if is "#f" or "#t"
    // character if starts with "#\..."
    // conditional if is "if" (impl "cond" in terms of "if")
    // else symbol
    
    return 0;
}
