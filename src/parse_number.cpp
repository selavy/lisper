#include "parse_number.h"
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <iostream> //TEMP
//------------------------------------------------------------------------------
bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}
//------------------------------------------------------------------------------
bool is_number(std::string::const_iterator begin,
               std::string::const_iterator end)
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
MaybeNumber parse_number(std::string::const_reverse_iterator rbegin,
                         std::string::const_reverse_iterator rend)
{
    if (rbegin == rend) return MaybeNumber();
    
    BigNumber ret = 0;
    BigNumber multiplier = 1;

    for (; rbegin != rend; ++rbegin) {
        MaybeNumber digit = parse_digit(*rbegin);
        if (!digit) return MaybeNumber();
        ret += *digit * multiplier;
        multiplier *= 10;
    }
    
    return ret;
}
//------------------------------------------------------------------------------
MaybeNumber parse_number(const std::string& num)
{
    return parse_number(num.crbegin(), num.crend());
}
//------------------------------------------------------------------------------
MaybeNumber parse_signed_number(std::string::const_reverse_iterator rbegin,
                                std::string::const_reverse_iterator rend)
{
    if (rbegin == rend) return MaybeNumber();
    char sign = *std::prev(rend);
    if (sign == '-') {
        MaybeNumber ret = parse_number(rbegin, std::prev(rend));
        if (!ret) return MaybeNumber();
        return *ret * -1;
    }
    else if (sign == '+') {
        return parse_number(rbegin, std::prev(rend));
    }
    else {
        return parse_number(rbegin, rend);
    }
    
    return MaybeNumber();
}
//------------------------------------------------------------------------------
MaybeNumber parse_signed_number(const std::string& num)
{
    return parse_signed_number(num.crbegin(), num.crend());
}
//------------------------------------------------------------------------------
