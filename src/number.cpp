#include "number.h"
#include "parse_number.h"

Number::Number()
    : val_(0)
{
}

Number::Number(value_type val)
    : val_(val)
{
}

Number::Number(const char* str)
    : val_(0)
{
    const auto n = parse_number(str);
    if (!n) throw std::runtime_error(std::string("Invalid number: ") + str);
    val_ = *n;
}

Number::value_type Number::value() const
{
    return val_;
}

void Number::print(std::ostream& os) const
{
    os << val_;
}
