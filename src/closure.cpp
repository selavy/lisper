#include "closure.h"
#include <sstream>
#include "eval.h"

Closure::Closure(Arguments args, std::list<ObjectPtr> body, Environment& env)
    : args_(std::move(args))
    , nArgs_(args_.size())
    , body_(std::move(body))
    , env_(env)
{
}

ObjectPtr Closure::evaluate(Arguments& args, Environment& env)
{
    if (args.size() != nArgs_) {
        std::stringstream ss;
        ss << "Expected " << nArgs_ << " arguments, received: " << args.size();
        throw std::runtime_error(ss.str());
    }

    auto param = std::begin(args_);
    auto arg = std::begin(args);
    for (; arg != std::end(args); ++arg, ++param) {
        env.emplace(std::move((*param)->toString()), std::move(*arg));
    }
    env.setParent(&env_);
    return evaluateList(body_, env);
}

std::string Closure::typeToString() const
{
    return "Closure";
}

std::string Closure::toString() const
{
    return "Closure";
}
