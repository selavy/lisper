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

typedef std::unordered_map<std::string, ObjectPtr> Environment;
typedef std::unordered_map<std::string, ObjectPtr> Primitives;
static Primitives gPrimitives;

//\! Converts container of iterables to std::list.
template <class CONT>
std::list<typename CONT::value_type> toList(const CONT& container)
{
    std::list<typename CONT::value_type> ret;
    for (const auto& it: container)
        ret.push_back(it);
    return ret;
}

ObjectPtr evaluateList(std::list<ObjectPtr>& tokens, Environment& env)
{
    ObjectPtr head = tokens.front();
    tokens.pop_front();

    const std::string& name = head->toString();
    auto found = gPrimitives.find(name);
    if (found != std::end(gPrimitives)) {
        ObjectPtr prim = found->second;
        Primitive* primPtr = dynamic_cast<Primitive*>(prim.get());
        return primPtr->evaluate(tokens);
    }
    else {
        throw std::runtime_error("Not a valid primitive: " + head->toString());
    }
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
        Token front = tokens.front();
        std::list<ObjectPtr> lst;
        while (front != ")") {
            lst.push_back(std::move(evaluate(tokens, env)));
            front = tokens.front();
        }
        
        tokens.pop_front(); // remove final ')' character
        return evaluateList(lst, env);
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

void initializeEnvironment(Environment& env)
{
    //TODO(plesslie): remove these from symbol map and add case to evaluate()
    env.emplace("+", ObjectPtr(new Symbol("+")));
    env.emplace("-", ObjectPtr(new Symbol("-")));
    env.emplace("*", ObjectPtr(new Symbol("*")));
    env.emplace("/", ObjectPtr(new Symbol("/")));
    env.emplace("write", ObjectPtr(new Symbol("write")));
    env.emplace("boolean?", ObjectPtr(new Symbol("boolean?")));

    gPrimitives.emplace("+", ObjectPtr(new Primitive("+", [](Arguments& args)
                    {
                        Integer::value_type ret = 0;
                        for (const auto& arg: args) {
                            ret += toInteger(arg)->value();
                        }
                        return ObjectPtr(new Integer(ret));
                    })));

    gPrimitives.emplace("-", ObjectPtr(new Primitive("-", [](Arguments& args)
                    {
                        Integer::value_type ret = 0;
                        if (args.empty()) {
                            ret = 0;
                        }
                        else if (args.size() == 1) {
                            ObjectPtr elem = args.front();
                            args.pop_front();
                            ret -= toInteger(elem)->value();
                        }
                        else {
                            // initialize with first element, subtract rest from that
                            ret = toInteger(args.front())->value();

                            // pop front and process cdr
                            args.pop_front();
                            for (const auto& elem: args) {
                                ret -= toInteger(elem)->value();
                            }
                        }
                        return ObjectPtr(new Integer(ret));
                    })));

    gPrimitives.emplace("*", ObjectPtr(new Primitive("*", [](Arguments& args)
                    {
                        Integer::value_type ret = 1;
                        for (const auto& arg: args) {
                            ret *= toInteger(arg)->value();
                        }
                        return ObjectPtr(new Integer(ret));
                    })));

    gPrimitives.emplace("/", ObjectPtr(new Primitive("/", [](Arguments& args)
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
                            args.pop_front();
                            for (const auto& arg: args) {
                                ret /= toInteger(arg)->value();
                            }
                        }
                        return ObjectPtr(new Integer(ret));
                    })));

    gPrimitives.emplace("write", ObjectPtr(new Primitive("write", [](Arguments& args)
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
                    })));

    gPrimitives.emplace("boolean?", ObjectPtr(new Primitive("boolean?", [](Arguments& args)
                    {
                        if (args.empty() || args.size() != 1) {
                            throw std::runtime_error("Expected 1 argument, given " + std::to_string(args.size()) + " arguments");
                        }
                        return ObjectPtr(new Boolean(args.front()->isBoolean()));
                    })));
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
        "(boolean? \"hello\")"
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
