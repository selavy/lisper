#include "eval.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
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
                POP(tokens);
                front = tokens.front();
                while (front != ")") {
                    std::cout << "Pushing back " << front << std::endl;
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
            std::cout << "EVAL::arguments: " << ss.str() << "\n";

            int cnt = 0;
            front = tokens.front();
            std::list<Token> body;
            while (!tokens.empty()){
                std::cout << "BODY PUSHING BACK: " << front << std::endl;
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

            //TODO(plesslie): don't evaluate body
            //std::list<ObjectPtr> body = std::move(readTail(tokens, env));
            POP(tokens);
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

