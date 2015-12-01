#include <iostream>
#include <sstream>
#include <locale>
#include <cstdlib>
#include <deque>
#include <vector>
#include <list>
#include <cstring>
#include <unordered_map>
#include "tokenize.h"
#include "number.h"
#include "integer.h"
#include "str.h"
#include "boolean.h"
#include "pair.h"
#include "symbol.h"
#include "empty.h"

typedef std::unordered_map<std::string, ObjectPtr> Environment;

//\! Converts container of iterables to std::list.
template <class CONT>
std::list<typename CONT::value_type> toList(const CONT& container)
{
    std::list<typename CONT::value_type> ret;
    for (const auto& it: container)
        ret.push_back(it);
    return ret;
}

//\! Recursively moves objects from std::list<> into a linked list of pairs.
ObjectPtr createList(ObjectPtr curr, std::list<ObjectPtr>& tokens)
{
    if (tokens.empty()) {
        return curr;
    }
    else {
        ObjectPtr front = tokens.front();
        tokens.pop_front();
        return createList(std::move(ObjectPtr(new Pair(front, curr))), tokens);
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
            lst.push_front(std::move(evaluate(tokens, env)));
            front = tokens.front();
        }
        return createList(ObjectPtr(new Empty), lst);
    }
    else if (token[0] == ')') {
        return ObjectPtr(new Empty);
    }
    else {
        //TODO: look up symbol in environment
        // return ObjectPtr(new Symbol(token.c_str()));
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

int main(int argc, char** argv)
{
    if (argc > 1 && (strcmp(argv[1], "--live") == 0)) {
        std::cout << ">";
        auto tokens = toList(tokenize(std::cin));
        Environment env;
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
            "(+ (+ 1 2) 2)",
            "(writeln \"hello world\n\")"
        };

        for (const auto& c : cases)
        {
            try {
                Environment env;
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
