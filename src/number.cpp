#include "number.h"

bool Number::isBoolean() const
{
    return false;
}

bool Number::isSymbol() const
{
    return false;
}

bool Number::isChar() const
{
    return false;    
}

bool Number::isVector() const
{
    return false;
}

bool Number::isPair() const
{
    return false;    
}

bool Number::isNumber() const
{
    return true;
}

bool Number::isString() const
{
    return false;    
}

bool Number::isProcedure() const
{
    return false;    
}
