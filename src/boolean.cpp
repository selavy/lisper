#include "boolean.h"
#include <cstring>

const char* const Boolean::FALSE_STR = "#f";
const char* const Boolean::TRUE_STR = "#t";

Boolean::Boolean()
    : val_(false)
{
}

Boolean::Boolean(bool val)
    : val_(val)
{
}

Boolean::Boolean(const char* val)
    : val_(strncmp(val, FALSE_STR, strlen(FALSE_STR)) != 0)
{
    // only false value is "#f"
}

std::string Boolean::toString() const
{
    return val_ ? TRUE_STR : FALSE_STR;
}

std::string Boolean::typeToString() const
{
    return "Boolean";
}
    
bool Boolean::isBoolean() const
{
    return true;
}

bool Boolean::isSymbol() const
{
    return false;
}

bool Boolean::isChar() const
{
    return false;
}

bool Boolean::isVector() const
{
    return false;
}

bool Boolean::isPair() const
{
    return false;
}

bool Boolean::isNumber() const
{
    return false;
}

bool Boolean::isString() const
{
    return false;
}

bool Boolean::isProcedure() const
{
    return false;
}

bool Boolean::value() const
{
    return val_;
}

bool Boolean::isBoolean(const char* val)
{
    return (strncmp(val, TRUE_STR, strlen(TRUE_STR)) == 0)
        || (strncmp(val, FALSE_STR, strlen(FALSE_STR)) == 0)
        ;
}
