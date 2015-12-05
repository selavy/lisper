#include "procedure.h"

std::string Procedure::typeToString() const
{
    return "Procedure";
}

bool Procedure::isBoolean() const
{
    return false;
}

bool Procedure::isSymbol() const
{
    return false;
}

bool Procedure::isChar() const
{
    return false;
}

bool Procedure::isVector() const
{
    return false;
}

bool Procedure::isPair() const
{
    return false;
}

bool Procedure::isNumber() const
{
    return false;
}

bool Procedure::isString() const
{
    return false;
}

bool Procedure::isProcedure() const
{
    return true;
}

