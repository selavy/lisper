#include "pair.h"
#include <sstream>

Pair::Pair(Object* first, Object* second)
    : first_(first)
    , second_(second)
{
}

const ObjectPtr& Pair::first() const
{
    return first_;
}

const ObjectPtr& Pair::second() const
{
    return second_;
}

void Pair::setFirst(Object* obj)
{
    first_.reset(obj);
}

void Pair::setSecond(Object* obj)
{
    second_.reset(obj);
}

std::string Pair::toString() const
{
    std::stringstream ret;
    if (!first_) {
        ret << "()";
    }
    else {
        ret << "(" << *first_ << " ";
        if (second_) {
            ret << *second_;
        }
        else {
            ret << "'()";
        }
        ret << ")";
    }
    return ret.str();
}

std::string Pair::typeToString() const
{
    return "Pair";
}

bool Pair::isBoolean() const
{
    return false;
}

bool Pair::isSymbol() const
{
    return false;    
}

bool Pair::isChar() const
{
    return false;
}

bool Pair::isVector() const
{
    return false;    
}

bool Pair::isPair() const
{
    return true;    
}

bool Pair::isNumber() const
{
    return false;    
}

bool Pair::isString() const
{
    return false;
}

bool Pair::isProcedure() const
{
    return false;
}

ObjectPtr cons(ObjectPtr first, ObjectPtr second)
{
    return ObjectPtr(new Pair(first.release(), second.release()));
}

    
