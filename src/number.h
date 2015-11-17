#ifndef NUMBER__H_
#define NUMBER__H_

#include "object.h"

class Number : public Object
{
public:
    typedef int64_t value_type;
public:
    Number();
    Number(value_type val);
    Number(const char* str);
    value_type value() const;
    void print(std::ostream& os) const override;
    Number& operator+(const Number& number);

private:
    int64_t val_;
};

#endif // NUMBER__H_
