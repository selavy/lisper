#include "environment.h"

Environment::Environment()
    : env_()
    , parent_(0)
{
}

Environment::iterator Environment::find(const std::string& key)
{
    return env_.find(key);
}

Environment::const_iterator Environment::find(const std::string& key) const
{
    return env_.find(key);
}

std::pair<Environment::iterator, bool> Environment::emplace(std::string&& key, ObjectPtr&& obj)
{
    return env_.emplace(std::forward<std::string>(key), std::forward<ObjectPtr>(obj));
}

Environment::iterator Environment::begin()
{
    return std::begin(env_); 
}

Environment::iterator Environment::end()
{
    return std::end(env_);
}

Environment::const_iterator Environment::begin() const
{
    return std::begin(env_);
}

Environment::const_iterator Environment::end() const
{
    return std::end(env_);
}

void Environment::setParent(Environment* env)
{
    parent_ = env;
}

Environment* Environment::getParent()
{
    return parent_;
}
