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
        //TODO(plesslie): Procedure class with Object* evaluate(std::list<ObjectPtr> args), register
        //                in an unordered_map<std::string, Procedure>
        Symbol* symbol = dynamic_cast<Symbol*>(head.get());
        if (!symbol) {
            throw std::runtime_error("Invalid token (not symbol): " + head->toString());
        }
        if (symbol->name() == "+") { // unboxed version
            //TEMP(plesslie): change this to a Number() and overload + operator
            //that way can handle more than integers
            Integer::value_type ret = 0;
            for (const auto& elem: tokens) {
               const Integer* i = dynamic_cast<Integer const*>(elem.get());
               if (!i) throw std::runtime_error("Argument type invalid for operator+: " + elem->toString());
               ret += i->value();
            }
            return ObjectPtr(new Integer(ret));
        }
        else if (symbol->name() == "-") { // unboxed version
            Integer::value_type ret = 0;

            if (tokens.empty()) {
                ret = 0;
            }
            else if (tokens.size() == 1) {
                ObjectPtr elem = tokens.front();
                tokens.pop_front();
                const Integer* i = dynamic_cast<Integer const*>(elem.get());
                if (!i) throw std::runtime_error("Argument type invalid for operator-:" + elem->toString());
                ret -= i->value();
            }
            else {
                // initialize with first element, subtract rest from that
                ObjectPtr car = tokens.front();
                const Integer* cari = dynamic_cast<Integer const*>(car.get());
                if (!cari) throw std::runtime_error("Argument type invalid for operator-: " + car->toString());
                ret = cari->value();

                // pop front and process cdr
                tokens.pop_front();
                for (const auto& elem: tokens) {
                    const Integer* i = dynamic_cast<Integer const*>(elem.get());
                    if (!i) throw std::runtime_error("Argument type invalid for operator-: " + elem->toString());
                    ret -= i->value();
                }
            }
            
            return ObjectPtr(new Integer(ret));
        }
        else {
            throw std::runtime_error("CAR of list is not an operator: " + head->toString());
        }
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
    env.emplace("+", ObjectPtr(new Symbol("+")));
    env.emplace("-", ObjectPtr(new Symbol("-")));

    gPrimitives.emplace("+", ObjectPtr(new Primitive("+", [](std::list<ObjectPtr>& args)
                    {
                        Integer::value_type ret = 0;
                        for (const auto& elem: args) {
                           const Integer* i = dynamic_cast<Integer const*>(elem.get());
                           if (!i) throw std::runtime_error("Argument type invalid for operator+: " + elem->toString());
                           ret += i->value();
                        }
                        return ObjectPtr(new Integer(ret));
                    })));

//    gPrimitives.emplace("-", ObjectPtr())
}

int main(int argc, char** argv)
{
    if (argc > 1 && (strcmp(argv[1], "--live") == 0)) {
        std::cout << ">";
        auto tokens = toList(tokenize(std::cin));
        Environment env;
        initializeEnvironment(env);
        try {
            auto res = evaluate(tokens, env);
            if (res) {
                std::cout << *res << std::endl;
            }
            else {
                std::cout << std::endl;
            }
        }
        catch (std::runtime_error& ex) {
            std::cout << "Exception: " << ex.what() << "\n";
        }
    }
    else {
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
            "(- (+ 1 2) 3)"

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
                else {
                    std::cout << "(null)" << std::endl;
                }
            }
            catch (std::runtime_error& ex) {
                std::cout << "Exception: " << ex.what() << "\n";                
            }
        }
    }
    
    return 0;
}
