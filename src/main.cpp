#include <iostream>
#include <sstream>
#include <locale>
#include <cstdlib>
#include "tokenize.h"
#include "number.h"
#include "integer.h"
#include "str.h"
#include "boolean.h"
#include "abstract_syntax_tree.h"

ObjectPtr process(const char* str)
{
    std::cout << "> " << str << std::endl;
    std::stringstream ss;
    ss << str;
    const auto tokens = tokenize(ss);
    // std::cout << "Tokens: " << tokens << std::endl;

    for (const auto& token: tokens) {
        if (token == "(") {
            std::cout << "BEGIN EXPR\n";
        }
        else if (token == ")") {
            std::cout << "END EXPR\n";
        }
        else if (token[0] == '"') {
            return ObjectPtr(new String(token.c_str()));
        }
        else if (std::isdigit(token[0])) {
            return ObjectPtr(new Integer(token.c_str()));
        }
        else if (Boolean::isBoolean(token.c_str())) {
            return ObjectPtr(new Boolean(token.c_str()));
        }
        else {
            std::cout << "SYMBOL\n";
        }
    }

    return ObjectPtr();
}

int main(int argc, char** argv)
{
    std::vector<std::string> cases = {
        "\"Hello\"",
        "1",
        "100",
        "10000",
        "#t",
        "#f"
//        "(+ 1 2)"
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
    // conditional if is "if" (impl "cond" in terms of "if")
    // else symbol
    
    return 0;
}
