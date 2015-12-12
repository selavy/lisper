#include "closure.h"
#include <sstream>
#include "eval.h"
//DEBUG
#include <iostream>
//GUBED

Closure::Closure(std::list<std::string> args, std::list<std::string> body, Environment& env)
    : args_(std::move(args))
    , nArgs_(args_.size())
    , body_(std::move(body))
    , env_(env)
{
    //DEBUG
    std::cout << "Creating closure with args: ";
    {
        std::stringstream ss;
        for (const auto& it: args_) ss << it << ", ";
        std::cout << ss.str();
    }
    std::cout << "\nBody: ";
    {
        std::stringstream ss;
        for (const auto& it: body_) ss << it << " ";
        std::cout << ss.str();
    }
    std::cout << std::endl;
    //GUBED
}

ObjectPtr Closure::evaluate(Arguments& args, Environment& env)
{
    if (args.size() != nArgs_) {
        std::stringstream ss;
        ss << "Expected " << nArgs_ << " arguments, received: " << args.size();
        throw std::runtime_error(ss.str());
    }

    //DEBUG
    std::cout << "Evaluating closure!" << std::endl;
    //GUBED
    auto param = std::begin(args_);
    auto arg = std::begin(args);
    for (; arg != std::end(args); ++arg, ++param) {
        //DEBUG
        std::cout << "inserting " << *param << " -> " << (*arg)->toString() << std::endl;
        //GUBED
        env.emplace(std::move(*param), std::move(*arg));
    }
    env.setParent(&env_);
    return ::evaluate(body_, env);
}

std::string Closure::typeToString() const
{
    return "Closure";
}

std::string Closure::toString() const
{
    return "Closure";
}
