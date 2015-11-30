#include "empty.h"

Empty::Empty()
{
}
    
std::string Empty::toString() const
{
    return "()";
}

std::string Empty::typeToString() const
{
    return "Empty";
}

bool Empty::isBoolean() const
{
    return false;
}

bool Empty::isSymbol() const
{
    return false;
}

bool Empty::isChar() const
{
    return false;
}

bool Empty::isVector() const
{
    return false;
}

bool Empty::isPair() const
{
    return false;
}

bool Empty::isNumber() const
{
    return false;
}

bool Empty::isString() const
{
    return false;
}

bool Empty::isProcedure() const
{
    return false;
}

