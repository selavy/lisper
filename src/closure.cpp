#include "closure.h"
#include <sstream>
#include "eval.h"
//DEBUG
#include <iostream>
//GUBED

Closure::Closure(std::list<std::string> args, std::list<std::string> body, Environment& env)
    : name_("CLOSURE")
    , args_(std::move(args))
    , nArgs_(args_.size())
    , body_(std::move(body))
    , env_(env)
{
    //DEBUG
    //std::cout << "CREATING CLOSURE: ";
    //for (const auto& it: body_) std::cout << it << " ";
    //std::cout << std::endl;
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
    //std::cout << "EVALUATING CLOSURE!" << std::endl;
    //GUBED
    auto param = std::begin(args_);
    auto arg = std::begin(args);
    //DEBUG
    //std::cout << "Arguments: ( ";
    //GUBED
    for (; arg != std::end(args); ++arg, ++param) {
        //DEBUG
        //std::cout << (*arg)->toString() << " ";
        //GUBED

        auto found = env.find(*param);
        if (found != std::end(env)) {
            found->second = std::move(*arg);
        }
        else {
            throw std::runtime_error("Failed to insert symbol!");
        }
    }
    //DEBUG
    //std::cout << ")\n";
    //GUBED
    env.setParent(&env_);

    //DEBUG
    //std::cout << "CLOSURE BODY: ";
    //for (const auto& tok: body_) std::cout << tok << " ";
    //std::cout << std::endl;
    //GUBED

    std::list<std::string> body(body_);
    return ::evaluate(body, env);
}

std::string Closure::typeToString() const
{
    return "Closure";
}

std::string Closure::toString() const
{
    return name_;
}

void Closure::setName(const char* name)
{
    name_ = name;
}

void Closure::printBody() const
{
    std::cout << "CLOSURE BODY: ";
    for (const auto& it : body_) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

