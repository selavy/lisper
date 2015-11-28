#include <iostream>
#include <sstream>
#include <locale>
#include <cstdlib>
#include "tokenize.h"
#include "number.h"
#include "integer.h"
#include "abstract_syntax_tree.h"

void process(const char* str)
{
    std::stringstream ss;
    ss << str;
    const auto tokens = tokenize(ss);
    std::cout << "Tokens: " << tokens << std::endl;

    for (const auto& token: tokens) {
        if (token == "(") {
            std::cout << "BEGIN EXPR\n";
        }
        else if (token == ")") {
            std::cout << "END EXPR\n";
        }
        else if (token[0] == '"') {
            std::cout << "STRING\n";
        }
        else if (std::isdigit(token[0])) {
            std::cout << "NUMBER\n";
        }
        else {
            std::cout << "SYMBOL\n";
        }
    }
}

int main(int argc, char** argv)
{
    process("(+ 1 2)");
    process("(writeln \"hello world\")");

    // token is either part of:
    // list, if starts with "("
    // string, if starts with '"'
    // number, if starts with digit
    // else symbol
    
    return 0;
}
