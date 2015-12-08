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

ObjectPtr& Vector::operator[](std::size_t i)
{
    if (i > objs_.size() || i < 0) {
        throw std::runtime_error("Invalid access of element: " + std::to_string(i));
    }
    return objs_[i];
}

std::size_t Vector::size() const
{
    return objs_.size();
}

std::string Vector::toString() const 
{
    std::stringstream ss;
    ss << "#(";
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
    ss << ")";
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

Vector* toVector(const ObjectPtr& p)
{
    Vector* i = dynamic_cast<Vector*>(p.get());
    if (!i) throw std::runtime_error("Object not vector: " + p->toString());
    return i;
}
