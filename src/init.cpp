#include "init.h"
#include <list>
#include <iostream>
#include <stdexcept>
#include "eval.h"
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

template <class Func>
void addPrimitive(Environment& env, const char* symbol, Func&& func)
{
    env.emplace(symbol, ObjectPtr(new Primitive(symbol, std::forward<Func>(func))));
}

void initializeEnvironment(Environment& env)
{
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
