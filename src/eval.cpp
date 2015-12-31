#include "eval.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <ios>
#include "environment.h"
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

//\! Evaluates a std::list<> into a single ObjectPtr
ObjectPtr evaluateList(std::list<ObjectPtr>& tokens, Environment& env)
{
    ObjectPtr head = tokens.front();
    POP(tokens);

    const std::string& name = head->toString();

    Environment* scope = &env;
    while (scope) {
        auto found = scope->find(name);
        if (found != std::end(*scope)) {
            ObjectPtr& obj = found->second;
            if (obj->isProcedure()) {
                Procedure* proc = dynamic_cast<Procedure*>(obj.get());
                return proc->evaluate(tokens, *scope);
            }
            else {
                throw std::runtime_error("Did not find a procedure where it was expected: " + name);
            }
        }
        else {
            scope = scope->getParent();
        }
    }

    throw std::runtime_error("Not a valid procedure: " + name);
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

std::list<Token> lazyEval(std::list<Token>& tokens)
{
    std::list<Token> ret;
    if (tokens.empty()) {
        return ret;
    }

    Token token = tokens.front();
    PUSH(ret, token);
    POP(tokens);

    if (token == "(") {
        int parens = 1;
        while (parens) {
            if (tokens.empty()) {
                throw std::runtime_error("Unmatched parens!");
            }
            token = tokens.front();
            POP(tokens);
            if (token == ")") --parens;
            else if (token == "(") ++parens;
            PUSH(ret, token);
        }
    }

    return ret;
}

//\! evaluate a list of tokens into an object.
ObjectPtr evaluate(std::list<Token>& tokens, Environment& env)
{
    //DEBUG
    //std::cout << "Entering evaluate: ";
    //for (const auto& tok: tokens) std::cout << tok << " ";
    //std::cout << std::endl;
    //GUBED

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
        //DEBUG
        //std::cout << "Returning Empty";
        //GUBED
        return ObjectPtr(new Empty);
    }

    Token token = tokens.front();
    POP(tokens);
    ObjectPtr ret;

    if (std::isdigit(token[0])) {
        ret.reset(new Integer(token.c_str()));
    }
    else if (token[0] == '"') {
         ret.reset(new String(token.c_str()));
    }
    else if (token == "'") {
        token = tokens.front();
        POP(tokens);
        if (token == "(") { // quoted list
            std::list<ObjectPtr> objs = std::move(readTail(tokens, env));
            if (objs.empty()) {
                ret.reset(new Empty);
            }
            else {
                ret = std::move(createList(ObjectPtr(new Empty), objs));
            }
        }
        else {
            throw std::runtime_error("Invalid token: " + token);
        }
    }
    else if (Boolean::isBoolean(token.c_str())) {
        ret.reset(new Boolean(token.c_str()));
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
            ret = std::move(vec);
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
            ret = std::move(evaluate(tokens, env));
        }
        else if (front == "begin") {
            POP(tokens);
            std::list<ObjectPtr> lst = std::move(readTail(tokens, env));
            ret = std::move(lst.back());
        }
        else if (front == "define") {
            POP(tokens);
            Token symbol = tokens.front();
            POP(tokens);
            std::list<ObjectPtr> lst = std::move(readTail(tokens, env));
            if (lst.size() != 1) {
                throw std::runtime_error("Expected 2 arguments, given " + std::to_string(lst.size() + 1));
            }
            ObjectPtr& obj = FIRST(lst);
            if (obj->isProcedure()) {
                if (Closure* closure = dynamic_cast<Closure*>(obj.get())) {
                    closure->setName(symbol.c_str());
                }
            }
            env.emplace(std::move(symbol), std::move(obj));
            ret.reset(new Empty);
        }
        else if (front == "if") {
            POP(tokens);
            std::list<Token> cond = lazyEval(tokens);
            ObjectPtr condObj = ::evaluate(cond, env);
            bool res = false;
            if (!condObj->isBoolean()) {
                res = true; // everything except for #f is true
            }
            else {
                res = toBoolean(condObj)->value();
            }
            std::list<Token> first = lazyEval(tokens);
            std::list<Token> second = lazyEval(tokens);
            ret = std::move(evaluate(res ? first : second, env));
        }
        else if (front == "lambda") {
            std::list<std::string> arguments;
            POP(tokens);
            front = tokens.front();
            if (front == "(") {
                POP(tokens);
                front = tokens.front();
                while (front != ")") {
                    arguments.push_back(front);
                    env.emplace(std::move(front), std::move(ObjectPtr(new Symbol(front.c_str()))));
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

            std::stringstream ss;
            for (const auto& it: arguments) ss << it << ", ";
            int cnt = 0;
            front = tokens.front();
            std::list<Token> body;
            while (!tokens.empty()){
                body.push_back(front);
                if (front == ")") {
                    --cnt;
                }
                else if (front == "(") {
                    ++cnt;
                }
                POP(tokens);
                if (cnt == 0) break;
                front = tokens.front();
            }
            POP(tokens);
            Environment* scope = new Environment;
            scope->setParent(&env);
            ret.reset(new Closure(std::move(arguments), std::move(body), *scope));
        }
        else { // function call
            std::list<ObjectPtr> lst = std::move(readTail(tokens, env));
            Environment* scope = new Environment;
            scope->setParent(&env);
            scope->print();
            scope->clearP();
            ret = std::move(evaluateList(lst, *scope));
        }
    }
    else if (token[0] == ')') {
        for (const auto& tkn: tokens) {
            std::cout << tkn << "\n";
        }
        throw std::runtime_error("Unmatched closing paren!");
    }
    else {
        Environment* curr = &env;
        for (; curr; curr = curr->getParent()) {
            auto found = curr->find(token);
            if (found != std::end(*curr)) {
                ret = found->second;
                break;
            }
        }
        if (!curr) throw std::runtime_error("Invalid symbol: '" + token + "'");
    }    
    return ret;
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

