#include "symbol.h"

Symbol::Symbol()
    : symbol_()
{
}

Symbol::Symbol(const char* symbol)
    : symbol_(symbol)
{
}
    
std::string Symbol::toString() const
{
    return symbol_;
}

std::string Symbol::typeToString() const
{
    return "Symbol";
}

bool Symbol::isBoolean() const
{
    return false;
}

bool Symbol::isSymbol() const
{
    return true;
}

bool Symbol::isChar() const
{
    return false;
}

bool Symbol::isVector() const
{
    return false;
}

bool Symbol::isPair() const
{
    return false;
}

bool Symbol::isNumber() const
{
    return false;
}

bool Symbol::isString() const
{
    return false;
}

bool Symbol::isProcedure() const
{
    return false;
}
