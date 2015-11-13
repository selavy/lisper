#include "parse_number.h"
#include <algorithm>
//------------------------------------------------------------------------------
bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}
//------------------------------------------------------------------------------
bool is_number(const std::string& num)
{
    return std::find_if_not(
        std::begin(num), std::end(num), is_digit) == std::end(num);
}
//------------------------------------------------------------------------------
