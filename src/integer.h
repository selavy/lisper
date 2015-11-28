#ifndef INTEGER__H_
#define INTEGER__H_

#include "number.h"
#include <cstdint>

bool isInteger(const char* buf);

class Integer : public Number
{
public:
    typedef int64_t value_type;
public:
    Integer();

    Integer(const char* val);

    Integer(value_type val);

    std::string toString() const;

    std::string typeToString() const;

    value_type getValue() const;

private:
    value_type val_;
};

#endif // INTEGER__H_
