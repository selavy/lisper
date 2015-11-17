#ifndef STR__H_
#define STR__H_

#include "object.h"
#include <string>
#include <ostream>

class String : public Object
{
public:
    String();
    String(const char* str);
    const std::string& value() const;
    void print(std::ostream& os) const;

private:
    std::string str_;
};

#endif // STR__H_
