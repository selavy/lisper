#include "environment.h"
#include <iostream>

Environment::Environment()
    : env_()
    , parent_(0)
    , p_(false)
    , name_(NameGenerator::instance().getName())
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

void Environment::print() const
{
#if 0
    if (p_) return;
    p_ = true;

    std::cout << "ENVIRONMENT(" << name_ << ")\n-----------------\n";
    for (const auto& p: env_) {
        std::cout << p.first << " -> " << p.second->toString() << "\n";
    }
    std::cout << "--------------------\n";
    if (parent_) parent_->print();
#endif
}

void Environment::clearP()
{
#if 0
    if (!p_) return;
    p_ = false;
    if (parent_) parent_->clearP();
#endif
}

int Environment::getName() const
{
    return name_;
}

NameGenerator& NameGenerator::instance()
{
    static NameGenerator instance;
    return instance;
}

NameGenerator::NameGenerator()
    : curr_(0)
{
}

NameGenerator::~NameGenerator()
{
}

int NameGenerator::getName() const
{
    return curr_++;
}
