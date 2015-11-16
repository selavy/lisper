#include <iostream>
#include "tokenize.h"

int main(int argc, char** argv)
{
    std::cout << ">";
    const auto ret = tokenize(std::cin);
    std::cout << "Tokens: " << ret << std::endl;
    return 0;
}
