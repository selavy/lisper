#include "parse_number.h"
#include <algorithm>
#include <stdexcept>
//------------------------------------------------------------------------------
bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}
//------------------------------------------------------------------------------
bool is_number(std::string::const_iterator begin, std::string::const_iterator end)
{
    return begin != end && std::find_if_not(begin, end, is_digit) == end;
}
//------------------------------------------------------------------------------
bool is_number(const std::string& num)
{
    return is_number(std::begin(num), std::end(num));
}
//------------------------------------------------------------------------------
bool is_signed_number(const std::string& num)
{
    if (num.empty()) return false;
    if (num[0] == '+' || num[0] == '-' || is_digit(num[0])) {
        return is_number(std::begin(num) + 1, std::end(num));
    }
    return false;
}
//------------------------------------------------------------------------------
MaybeNumber parse_digit(char c)
{
    if (!is_digit(c)) return MaybeNumber();
    return c - '0';
}
//------------------------------------------------------------------------------
