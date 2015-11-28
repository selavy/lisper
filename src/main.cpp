#include <iostream>
#include <sstream>
#include "tokenize.h"
#include "number.h"
#include "integer.h"
#include "abstract_syntax_tree.h"

int main(int argc, char** argv)
{
    std::cout << ">";
    std::stringstream ss;
    ss << "(+ 1 2)\n";
    const auto tokens = tokenize(ss);
    std::cout << "Tokens: " << tokens << std::endl;

    AbstractSyntaxTree ast;
    for (const auto& token : tokens)
        ast.addToken(token);

    std::cout << "AST: " << ast << std::endl;

    return 0;
}
