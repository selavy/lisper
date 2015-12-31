#ifndef ENVIRONMENT__H_
#define ENVIRONMENT__H_

#include <unordered_map>
#include "object.h"

//typedef std::unordered_map<std::string, ObjectPtr> Environment;

class Environment
{
public:
    typedef std::unordered_map<std::string, ObjectPtr> SymbolTable;
    typedef SymbolTable::iterator iterator;
    typedef SymbolTable::const_iterator const_iterator;

public:
    Environment();

    iterator find(const std::string& key);

    const_iterator find(const std::string& key) const;

    std::pair<iterator, bool> emplace(std::string&& key, ObjectPtr&& obj);

    iterator begin();

    iterator end();

    const_iterator begin() const;

    const_iterator end() const;

    void setParent(Environment* env);

    Environment* getParent();

    void print() const;

    void clearP();

    int getName() const;

private:
     SymbolTable env_;

     Environment* parent_;

     mutable bool p_;

     int name_;
};

struct NameGenerator
{
    static NameGenerator& instance();

    int getName() const;

private:
    NameGenerator();

    ~NameGenerator();

    mutable int curr_; 
};

#endif // ENVIRONMENT__H_
