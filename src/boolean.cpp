#include "boolean.h"
#include <cstring>

#define FALSE_STR "#f"

Boolean::Boolean()
    : val_(false)
{
}

Boolean::Boolean(const char* val)
    : val_(true)
{
    // only false value is "#f"
    val_ = strncmp(val, FALSE_STR, strlen(FALSE_STR));
}

void Boolean::print(std::ostream& os) const
{
    if (val_) {
        os << "#t";
    }
    else {
        os << "#f";
    }
}

bool Boolean::value() const
{
    return val_;
}
