#include "vec.h"
#include "infix_iterator.h" 
Vector::Vector()
    : data_()
{
}

Vector::Vector(Objects objs)
    : data_(std::move(objs))
{
}

void Vector::push_back(const Object& obj)
{
    data_.push_back(obj);
}

void Vector::print(std::ostream& os) const
{
    os << "( '";
    std::copy(std::begin(data_), std::end(data_),
              infix_ostream_iterator<Objects::value_type>(os, "', '"));
    os << "' )";
}
