#include "object.h"

Object::~Object()
{
}

void Object::print(std::ostream& os) const
{
    os << typeToString() << "::" << toString();
}

std::ostream& operator<<(std::ostream& os, const Object& obj)
{
    obj.print(os);
    return os;
}
