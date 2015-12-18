#include <iostream>
#include <sstream>
#include <locale>
#include <cstdlib>
#include <deque>
#include <vector>
#include <list>
#include <cstring>
#include <unordered_map>
#include <functional>
#include "environment.h"
#include "eval.h"
#include "init.h"
#include "procedure.h"
#include "closure.h"
#include "number.h"
#include "integer.h"
#include "str.h"
#include "boolean.h"
#include "pair.h"
#include "symbol.h"
#include "empty.h"
#include "procedure.h"
#include "primitive.h"
#include "vec.h"

template <class CONT>
std::list<typename CONT::value_type> toList(const CONT& container);

//\! Converts container of iterables to std::list.
template <class CONT>
std::list<typename CONT::value_type> toList(const CONT& container)
{
    std::list<typename CONT::value_type> ret;
    for (const auto& it: container)
        PUSH(ret, it);
    return ret;
}

//\! Take a string read in and evaluate it.
ObjectPtr process(const char* str, Environment& env)
{
    std::cout << "> " << str << std::endl;
    std::stringstream ss;
    ss << str;
    std::list<Token> tokens = toList(tokenize(ss));
    return evaluate(tokens, env);
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
        "(+ 1 2)",
        "(+ (+ 1 2) 4)",
        "(+ (+ 1 2) (+ 3 4) (+ 1 2 3 4 5 6))",
        "(+)",
        "(-)",
        "(- (+ 1 2) 3)",
        "(* 1 2 3 4 5 0)",
        "(* (+ 1 2) (+ 3 4))",
        "(*)",                                  // => 1
        "(/)",                                  // => 1
        "(/ 2)",                                // => 0
        "(write \"hello world!\")",
        "(/ 8 4)",
        "(boolean? #t)",                        // => #t
        "(boolean? #f)",                        // => #t
        "(boolean? \"hello\")",                 // => #f
        "(number? 1234)",                       // => #t
        "(string? \"hello\")",                  // => #t
        "(number? \"1234\")",                   // => #f
        "'()",                                  // => '()
        "'(1 2 3)",                             // => '(1 2 3)
        "(null? '())",                          // => #t
        "(pair? '(1 2))",                       // => #t
        "(pair? '(1 2 3 4 5 6))",               // => #t
        "#(1 2 3 4 5)",                         // => #(1 2 3 4 5)
        "(vector-length '#(1 2 3 4 5))",        // => 5
        "(vector-ref '#(1 1 2 3 5 8 13 21) 5)", // => 8
        "(vector-set! '#(0 1 2 3 4 5) 3 27)",   // this should raise &assertion exception for trying to set in constant vector
        "(if #t 1 2)",                          // => 1
        "(if #f 1 2)",                          // => 2
        "(if #t (+ 1 3) (+ 1 5))",              // => 4
        "(if #f (+ 1 3) (+ 1 5))",              // => 6
        "(if 1 1 2)",                           // => 1
        "(if #t (if #f 1 2) (if #f 3 4))",      // => 2
        "(quote (1 2 3))",                      // => '(1 2 3)
        "(begin (+ 1 2) (+ 3 4))",              // => 7
        "(define a 23)",                        // => '()
        "(begin (define a 23) (+ a 1))",        // => 24
        "(begin (define add1 (lambda (x) (+ x 1))) (add1 23))", // => 24
        "(if (string? 123) 1 2)",                // => 2
        "(begin (define a 23) (define b 24) (+ a b))", // => 47
        "(begin (define a 23) (define b 24) (define plus (lambda (x y) (+ x y))) (plus a b))" // => 47
    };

    for (const auto& c : cases)
    {
        try {
            Environment env;
            initializeEnvironment(env);                
            ObjectPtr res = std::move(process(c.c_str(), env));
            if (res) {
                std::cout << "  " << *res << std::endl;
            }
        }
        catch (std::runtime_error& ex) {
            std::cout << "Exception: " << ex.what() << "\n";                
        }
    }

    return 0;
}
