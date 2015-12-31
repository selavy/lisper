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
    , spacing_(0)
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

    Environment scope;
    auto param = std::begin(args_);
    auto arg = std::begin(args);
    for (; arg != std::end(args); ++arg, ++param) {
        std::string paramCopy = *param;
        scope.emplace(std::move(paramCopy), std::move(*arg));
    }
    env.setParent(&env_);
    scope.setParent(&env);

    std::list<std::string> body(body_); // make a copy so it won't be modified by ::evaluate()
    ObjectPtr ret = std::move(::evaluate(body, scope));
    return ret;
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
#if 0
    std::cout << "CLOSURE BODY: ";
    for (const auto& it : body_) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
#endif
}

