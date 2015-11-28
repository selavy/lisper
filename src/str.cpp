#include "str.h"

String::String()
    : str_()
{
}

String::String(const char* str)
    : str_(str)
{
    if (str_.empty()) {
        return;
    }
    else if (str_.size() < 2) {
        throw std::runtime_error("Invalid string literal: " + str_);
    }
    else if (str_.front() != '"') {
        throw std::runtime_error("Invalid string literal: " + str_);
    }
    else if (str_.back() != '"') {
        throw std::runtime_error("Invalid string literal: " + str_);
    }
    else {
        str_ = str_.substr(1, str_.size() - 2); // pop front and back '"' character
    }
}

String::~String()
{
}

std::string String::toString() const
{
    return '"' + str_ + '"';
}

std::string String::typeToString() const
{
    return "String";
}

bool String::isBoolean() const
{
    return false;
}

bool String::isSymbol() const
{
    return false;
}

bool String::isChar() const
{
    return false;
}

bool String::isVector() const
{
    return false;
}

bool String::isPair() const
{
    return false;
}

bool String::isNumber() const
{
    return false;
}

bool String::isString() const
{
    return true;
}

bool String::isProcedure() const
{
    return false;
}

