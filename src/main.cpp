#include <iostream>
#include <sstream>
#include "tokenize.h"
#include "parse_number.h"
#include "number.h"
#include "empty.h"
#include "boolean.h"
#include "str.h"
#include "vec.h"
#include "symbol.h"
#include "procedure.h"
#include "primitive.h"

int main(int argc, char** argv)
{
//    std::cout << ">";
    std::stringstream ss;
    ss << "(+ 1 2)\n";
    const auto ret = tokenize(ss);
    std::cout << "Tokens: " << ret << std::endl;

    if (ret.empty()) {
        std::cout << "No Tokens!" << std::endl;
        return 0;
    }
    auto first = std::begin(ret);
    if (*first == ")") {
        std::cout << "Invalid token: " << *first << std::endl;
    }
    else if (is_number(*first)) {
        std::unique_ptr<Object> number(new Number(first->c_str()));
        std::cout << *number << std::endl;
    }
    else if (*first == "(") { // begin expr
        ++first;
        if (first == std::end(ret)) {
            std::cout << "Expression not completed!" << std::endl;
        }
        else {
            std::unique_ptr<Object> primitive = createPrimitive(*first);
            if (!primitive) {
                std::cout << "Invalid token: " << *first << std::endl;
            }
            else {
                std::cout << *primitive << std::endl;
            }
        }
    }
    else {
        std::cout << "Invalid token: " << *first << std::endl;
    }
    
    return 0;
}
