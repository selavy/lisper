#include "object.h"

Object::~Object()
{
}

std::ostream& operator<<(std::ostream& os, const Object& obj)
{
    obj.print(os);
    return os;
}
