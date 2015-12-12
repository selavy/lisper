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
#include "tokenize.h"
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
#include "environment.h"
#include "eval.h"
#include "init.h"
#include "closure.h"

typedef std::unordered_map<std::string, ObjectPtr> Primitives;

template <class CONT>
std::list<typename CONT::value_type> toList(const CONT& container);

std::list<ObjectPtr> readTail(std::list<Token>& tokens, Environment& env);

ObjectPtr createList(ObjectPtr curr, std::list<ObjectPtr>& objs);

ObjectPtr evaluate(std::list<Token>& tokens, Environment& env);

std::list<ObjectPtr> unwrapPairs(ObjectPtr pair);

//\! Converts container of iterables to std::list.
template <class CONT>
std::list<typename CONT::value_type> toList(const CONT& container)
{
    std::list<typename CONT::value_type> ret;
    for (const auto& it: container)
        PUSH(ret, it);
    return ret;
}

//\! Converts a std::list<> to a linked list of pairs (recursive)
ObjectPtr createList(ObjectPtr curr, std::list<ObjectPtr>& objs)
{
    ObjectPtr head = curr;
    while (!objs.empty()) {
        ObjectPtr front = objs.front();
        POP(objs);
        head = ObjectPtr(new Pair(front, head));
    }
    return head;
}

//\! evaluate a list of tokens into an object.
ObjectPtr evaluate(std::list<Token>& tokens, Environment& env)
{
    // [LET (TOKEN = first token in tokens, C = first character of token)]
    //------------------------------------------------------------------------
    // [Case]             | [Result]
    //------------------------------------------------------------------------
    // Base cases:    
    //------------------------------------------------------------------------
    // tokens empty       | Empty()
    // C ~ [1-9]          | Integer() [TODO: expand numerical types]
    // C ~ "              | String()
    // C ~ #[tf]          | Boolean()
    // C ~ #\[a-zA-Z1-9]+ | Character() [TODO: add unicode character class]
    // anything else      | Symbol()
    //------------------------------------------------------------------------
    // Recursive cases:
    //------------------------------------------------------------------------
    // C ~ (              | List()
    
    if (tokens.empty()) {
        return ObjectPtr(new Empty);
    }

    Token token = tokens.front();
    POP(tokens);

    if (std::isdigit(token[0])) {
        return ObjectPtr(new Integer(token.c_str()));
    }
    else if (token[0] == '"') {
        return ObjectPtr(new String(token.c_str()));
    }
    else if (token == "'") {
        token = tokens.front();
        POP(tokens);
        if (token == "(") { // quoted list
            std::list<ObjectPtr> objs = std::move(readTail(tokens, env));
            if (objs.empty()) {
                return ObjectPtr(new Empty);
            }
            else {
                return createList(ObjectPtr(new Empty), objs);
            }
        }
        else {
            throw std::runtime_error("Invalid token: " + token);
        }
    }
    else if (Boolean::isBoolean(token.c_str())) {
        return ObjectPtr(new Boolean(token.c_str()));
    }
    else if (token == "#" || token == "'#") {
        token = tokens.front();
        POP(tokens);
        if (token == "(") { // vector
            ObjectPtr vec(new Vector);
            Token front = tokens.front();
            while (front != ")") {
                dynamic_cast<Vector*>(vec.get())->append(std::move(evaluate(tokens, env)));
                front = tokens.front();
            }
            POP(tokens); // remove final ')' character
            return vec;
        }
        else {
            //TODO(plesslie): handle characters
            throw std::runtime_error("Invalid token: " + token);
        }
    }
    else if (token == "(") {
        Token front = tokens.front();
        if (front == "quote") { // REVISIT(plesslie): not working correctly, CURRENTLY: (quote (1 2 3)) => '(2 3), should be '(1 2 3)
            tokens.front() = "'";
            return evaluate(tokens, env);
        }
        else if (front == "begin") {
            POP(tokens);
            std::list<ObjectPtr> lst = std::move(readTail(tokens, env));
            return lst.back();
        }
        else if (front == "define") {
            POP(tokens);
            Token symbol = tokens.front();
            POP(tokens);
            std::list<ObjectPtr> lst = std::move(readTail(tokens, env));
            if (lst.size() != 1) {
                throw std::runtime_error("Expected 2 arguments, given " + std::to_string(lst.size() + 1));
            }
            env.emplace(std::move(symbol), std::move(FIRST(lst)));
            return ObjectPtr(new Empty);
        }
        else if (front == "if") {
            POP(tokens);
            std::list<ObjectPtr> lst = std::move(readTail(tokens, env));
            if (lst.size() != 3) {
                throw std::runtime_error("if statement expects 3 arguments, given " + std::to_string(lst.size()));
            }
            auto first = FIRST(lst);
            if (toBoolean(first)->value()) {
                return SECOND(lst);
            }
            else {
                return THIRD(lst);
            }
        }
        else if (front == "lambda") {
            std::list<std::string> arguments;
            POP(tokens);
            front = tokens.front();
            if (front == "(") {
                front = tokens.front();
                while (front != ")") {
                    arguments.push_back(front);
                    POP(tokens);
                    front = tokens.front();
                }
                POP(tokens); 
            }
            else {
                while (front != "(") {
                    arguments.push_back(front);
                    POP(tokens);
                    front = tokens.front();
                }
            }

            std::list<ObjectPtr> body = std::move(readTail(tokens, env));
            //ObjectPtr first = body.front();
            //std::list<ObjectPtr> args = std::move(unwrapPairs(first));
            //POP(body);
            return ObjectPtr(new Closure(std::move(arguments), std::move(body), env));
        }
        else { // function call
            std::list<ObjectPtr> lst = std::move(readTail(tokens, env));
            Environment scope;
            scope.setParent(&env);
            return evaluateList(lst, scope);
        }
    }
    else if (token[0] == ')') {
        throw std::runtime_error("Unmatched closing paren!");
    }
    else {
        auto found = env.find(token);
        if (found == std::end(env)) {
            throw std::runtime_error("Invalid symbol: '" + token + "'");
        }
        return found->second;
    }    
}

std::list<ObjectPtr> readTail(std::list<Token>& tokens, Environment& env)
{
    Token token = tokens.front();
    std::list<ObjectPtr> objs;
    while (token != ")") {
        PUSH(objs, std::move(evaluate(tokens, env)));
        token = tokens.front();
    } 
    POP(tokens); // remove final ')'
    return objs;
}

std::list<ObjectPtr> unwrapPairs(ObjectPtr pair)
{
    std::list<ObjectPtr> ret;
    if (Pair* head = dynamic_cast<Pair*>(pair.get())) {
        if (CAR(head) == nullptr) return ret;

        ret.push_back(CAR(head));
        while ((head = dynamic_cast<Pair*>(CDR(head).get()))) {
            ret.push_back(CAR(head));        
        }
        return ret;
    }
    else {
        throw std::runtime_error("Object is not a pair!");
    }
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
        "(*)",
        "(/)",
        "(/ 2)",
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
        "(begin (define add1 (lambda (x) (+ x 1))) (add1 23))" // => 24
        "(if (string? 123) 1 2)"                // => 2

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
