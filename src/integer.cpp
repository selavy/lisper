#include "integer.h"
#include <boost/optional.hpp>
#include <locale>
#include <cstdlib>

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

char parseDigit(char c)
{
    return c - '0';
}

int64_t parseNumber(const char* buf)
{
    if (!isInteger(buf)) {
        throw std::runtime_error(std::string("Invalid number: ") + buf);
    }
    
    return std::atoll(buf);
}

bool isInteger(const char* buf) {
    std::string str(buf);
    auto found = std::find_if_not(std::begin(str), std::end(str),
                                  [](char c) { return std::isdigit(c); });
    return found == std::end(str);
}

Integer::Integer()
    : Number()
    , val_(0)
{
}

Integer::Integer(const char* val)
    : Number()
    , val_(0)
{
    val_ = parseNumber(val);
}

Integer::Integer(value_type val)
    : Number()
    , val_(val)
{
}

std::string Integer::toString() const
{
    return std::to_string(val_);
}

std::string Integer::typeToString() const
{
    return "Integer";
}

Integer::value_type Integer::getValue() const
{
    return val_;
}
