#include "vec.h"
#include <sstream>

Vector::Vector()
    : objs_()
{
}

Vector::Vector(std::list<ObjectPtr> objs)
    : objs_()
{
    for (auto& o: objs)
        objs_.push_back(std::move(o));
}

Vector::Vector(std::vector<ObjectPtr> objs)
    : objs_(std::move(objs))
{
}

void Vector::append(ObjectPtr obj)
{
    objs_.push_back(std::move(obj));
}

std::string Vector::toString() const 
{
    std::stringstream ss;
    ss << "[";
    bool first = true;
    for (const auto& o: objs_) {
        if (first) {
            ss << o->toString();
            first = false;
        }
        else {
            ss << " " << o->toString();
        }
    }
    ss << "]";
    return ss.str();
}

std::string Vector::typeToString() const 
{
    return "Vector";
}

bool Vector::isBoolean() const 
{
    return false;
}

bool Vector::isSymbol() const 
{
    return false;
}

bool Vector::isChar() const 
{
    return false;
}

bool Vector::isVector() const 
{
    return true;
}

bool Vector::isPair() const 
{
    return false;
}

bool Vector::isNumber() const 
{
    return false;
}

bool Vector::isString() const 
{
    return false;
}

bool Vector::isProcedure() const 
{
    return false;
}
