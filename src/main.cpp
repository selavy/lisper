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

typedef std::unordered_map<std::string, ObjectPtr> Primitives;

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
    //TODO(plesslie): this is tail recursive, change to a while loop
    if (objs.empty()) return curr;
    ObjectPtr front = objs.front();
    POP(objs);
    return createList(std::move(ObjectPtr(new Pair(front, curr))), objs);
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
            token = tokens.front();
            POP(tokens);
            if (token == ")") {
                return ObjectPtr(new Empty);
            }
            else {
                std::list<ObjectPtr> objs;
                while (token != ")") {
                    PUSH(objs, std::move(evaluate(tokens, env)));
                    token = tokens.front();
                } 
                POP(tokens); // remove final ')'
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

        if (front == "quote") {
            tokens.front() = "'";
            return evaluate(tokens, env);
        }
        else if (front == "begin") {
            throw std::runtime_error("Unimplemented!");
        }
        else if (front == "if") {
            std::list<ObjectPtr> lst;
            POP(tokens);
            front = tokens.front();
            while (front != ")") {
                PUSH(lst, std::move(evaluate(tokens, env)));
                front = tokens.front();
            }
            POP(tokens); // remove final ')' character

            if (lst.size() != 3) {
                throw std::runtime_error("if statement expects 3 arguments, given " + std::to_string(lst.size()));
            }
            auto first = std::begin(lst);
            if (toBoolean(*first)->value()) {
                ++first;
                return *first;
            }
            else {
                ++first; ++first;
                return *first;
            }
        }
        else if (front == "lambda") {
            throw std::runtime_error("Unimplemented!");
        }
        else { // function call
            std::list<ObjectPtr> lst;
            while (front != ")") {
                PUSH(lst, std::move(evaluate(tokens, env)));
                front = tokens.front();
            }
            POP(tokens); // remove final ')' character

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

//\! Take a string read in and evaluate it.
ObjectPtr process(const char* str, Environment& env)
{
    std::cout << "> " << str << std::endl;
    std::stringstream ss;
    ss << str;
    std::list<Token> tokens = toList(tokenize(ss));
    return evaluate(tokens, env);
}

template <class Func>
void addPrimitive(Environment& env, const char* symbol, Func&& func)
{
    env.emplace(symbol, ObjectPtr(new Primitive(symbol, std::forward<Func>(func))));
}

void initializeEnvironment(Environment& env)
{
    //TODO(plesslie): remove these from symbol map and add case to evaluate()
    //
    
//    addPrimitive(env, "if",
//            [](Arguments& args, Environment& env)
//            {
//                if (args.size() != 3) {
//                    throw std::runtime_error("Expected 2 arguments, received: " + std::to_string(args.size()));
//                }
//
//                auto arg = std::begin(args);
//                // toBoolean() always succeeds
//                if (toBoolean(*arg)->value()) {
//                    ++arg;
//                    return *arg;
//                }
//                else {
//                    ++arg;
//                    ++arg;
//                    return *arg;
//                }
//            }); 
    
    addPrimitive(env, "+",
            [](Arguments& args, Environment& env)
            {
                Integer::value_type ret = 0;
                for (const auto& arg: args) {
                    ret += toInteger(arg)->value();
                }
                return ObjectPtr(new Integer(ret));
            });

    addPrimitive(env, "-",
            [](Arguments& args, Environment& env)
            {
                Integer::value_type ret = 0;
                if (args.empty()) {
                    ret = 0;
                }
                else if (args.size() == 1) {
                    ObjectPtr elem = args.front();
                    POP(args);
                    ret -= toInteger(elem)->value();
                }
                else {
                    // initialize with first element, subtract rest from that
                    ret = toInteger(args.front())->value();

                    // pop front and process cdr
                    POP(args);
                    for (const auto& elem: args) {
                        ret -= toInteger(elem)->value();
                    }
                }
                return ObjectPtr(new Integer(ret));
            });

    addPrimitive(env, "*",
            [](Arguments& args, Environment& env)
            {
                Integer::value_type ret = 1;
                for (const auto& arg: args) {
                    ret *= toInteger(arg)->value();
                }
                return ObjectPtr(new Integer(ret));
            });

    addPrimitive(env, "/",
            [](Arguments& args, Environment& env)
            {
                Integer::value_type ret = 1;
                if (args.empty()) {
                    ret = 1;
                }
                else if (args.size() == 1) {
                    ObjectPtr elem = args.front();
                    Integer::value_type val = toInteger(elem)->value();
                    //TODO(plesslie): exception for divide by zero?
                    ret = 1 / val;
                }
                else {
                    ret = toInteger(args.front())->value();
                    POP(args);
                    for (const auto& arg: args) {
                        ret /= toInteger(arg)->value();
                    }
                }
                return ObjectPtr(new Integer(ret));
            });

    addPrimitive(env, "write",
            [](Arguments& args, Environment& env)
            {
                if (args.empty()) {
                    throw std::runtime_error("Expected 1 argument, none given");
                }
                else if (args.size() == 1) {
                //FIXME(plesslie): won't print control character (e.g. '\n') correctly
                    std::cout << args.front()->toString() << std::endl;
                }
                else {
                    throw std::runtime_error("Expected 1 argument, given: "
                            + std::to_string(args.size()));
                }
                return ObjectPtr(0);
            });

    addPrimitive(env, "boolean?", 
            [](Arguments& args, Environment& env)
            {
                if (args.empty() || args.size() != 1) {
                    throw std::runtime_error("Expected 1 argument, given " + std::to_string(args.size()) + " arguments");
                }
                return ObjectPtr(new Boolean(args.front()->isBoolean()));
            });

    addPrimitive(env, "symbol?",
            [](Arguments& args, Environment& env)
            {
                if (args.empty() || args.size() != 1) {
                    throw std::runtime_error("Expected 1 argument, given " + std::to_string(args.size()) + " arguments");
                }
                return ObjectPtr(new Boolean(args.front()->isSymbol()));
            });

    addPrimitive(env, "char?",
            [](Arguments& args, Environment& env)
            {
                if (args.empty() || args.size() != 1) {
                    throw std::runtime_error("Expected 1 argument, given " + std::to_string(args.size()) + " arguments");
                }
                return ObjectPtr(new Boolean(args.front()->isChar()));
            });

    addPrimitive(env, "vector?",
            [](Arguments& args, Environment& env)
            {
                if (args.empty() || args.size() != 1) {
                    throw std::runtime_error("Expected 1 argument, given " + std::to_string(args.size()) + " arguments");
                }
                return ObjectPtr(new Boolean(args.front()->isVector()));
            });

    addPrimitive(env, "null?",
            [](Arguments& args, Environment& env)
            {
                if (args.empty() || args.size() != 1) {
                    throw std::runtime_error("Expected 1 argument, given " + std::to_string(args.size()) + " arguments");
                }
                const bool res = dynamic_cast<Empty*>(args.front().get()) != 0;
                return ObjectPtr(new Boolean(res));
            });

    addPrimitive(env, "pair?",
            [](Arguments& args, Environment& env)
            {
                if (args.empty() || args.size() != 1) {
                    throw std::runtime_error("Expected 1 argument, given " + std::to_string(args.size()) + " arguments");
                }
                return ObjectPtr(new Boolean(args.front()->isPair()));
            });

    addPrimitive(env, "number?",
            [](Arguments& args, Environment& env)
            {
                if (args.empty() || args.size() != 1) {
                    throw std::runtime_error("Expected 1 argument, given " + std::to_string(args.size()) + " arguments");
                }
                return ObjectPtr(new Boolean(args.front()->isNumber()));
            });

    addPrimitive(env, "string?",
            [](Arguments& args, Environment& env)
            {
                if (args.empty() || args.size() != 1) {
                    throw std::runtime_error("Expected 1 argument, given " + std::to_string(args.size()) + " arguments");
                }
                return ObjectPtr(new Boolean(args.front()->isString()));
            });

    addPrimitive(env, "procedure?",
            [](Arguments& args, Environment& env)
            {
                if (args.empty() || args.size() != 1) {
                    throw std::runtime_error("Expected 1 argument, given " + std::to_string(args.size()) + " arguments");
                }
                return ObjectPtr(new Boolean(args.front()->isProcedure()));
            });

    addPrimitive(env, "vector-length",
            [](Arguments& args, Environment& env)
            {
                if (args.empty() || args.size() != 1) {
                    throw std::runtime_error("Expected 1 argument, given " + std::to_string(args.size()) + " arguments");
                }
                return ObjectPtr(new Integer(toVector(args.front())->size()));
            });

    addPrimitive(env, "vector-ref",
            [](Arguments& args, Environment& env)
            {
                if (args.empty() || args.size() != 2) {
                    throw std::runtime_error("Expected 2 arguments, given " + std::to_string(args.size()) + " arguments");
                }
                ObjectPtr vec = args.front();
                POP(args);
                ObjectPtr index = args.front();
                POP(args);
                return toVector(vec)->operator[](toInteger(index)->value());
            });

    addPrimitive(env, "vector-set!",
            [](Arguments& args, Environment& env)
            {
                if (args.empty() || args.size() != 3) {
                    throw std::runtime_error("Expected 3 arguments, given " + std::to_string(args.size()) + " arguments");
                }
                ObjectPtr vec = args.front();
                POP(args);
                ObjectPtr index = args.front();
                POP(args);
                ObjectPtr obj = args.front();
                POP(args);

                using std::swap;
                swap(toVector(vec)->operator[](toInteger(index)->value()), obj);
                //TEMP(plesslie): should return Empty
                return vec;
            });
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
        "(boolean? #t)",
        "(boolean? #f)",
        "(boolean? \"hello\")",
        "(number? 1234)",
        "(string? \"hello\")",
        "(number? \"1234\")",
        "'()",
        "(null? '())",
        "(pair? '(1 2))",
        "(pair? '(1 2 3 4 5 6))",
        "#(1 2 3 4 5)",
        "(vector-length '#(1 2 3 4 5))",
        "(vector-ref '#(1 1 2 3 5 8 13 21) 5)",
        "(vector-set! '#(0 1 2 3 4 5) 3 27)", // this should raise &assertion exception for trying to set in constant vector
        "(if #t 1 2)",
        "(if #f 1 2)",
        "(if #t (+ 1 3) (+ 1 5))",
        "(if #f (+ 1 3) (+ 1 5))",
        "(if 1 1 2)",
        "(if #t (if #f 1 2) (if #f 3 4))",
        "(quote (1 2 3))"
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
