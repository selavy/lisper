#include "pair.h"
#include <sstream>

Pair::Pair(ObjectPtr first, ObjectPtr second)
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
    return ObjectPtr(new Pair(first, second));
}

std::size_t length(ObjectPtr pair)
{
    if (Pair* head = dynamic_cast<Pair*>(pair.get())) {
        if (CAR(head) == nullptr) return 0;
        std::size_t ret = 1;
        while ((head = dynamic_cast<Pair*>(CDR(head).get()))) ++ret;
        return ret;
    }
    else {
        throw std::runtime_error("Object is not a pair!");
    }
}

    
