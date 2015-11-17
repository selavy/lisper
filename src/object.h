#ifndef OBJECT__H_
#define OBJECT__H_

#include <ostream>

struct Object
{
    virtual ~Object();
    virtual void print(std::ostream& os) const=0;
};

std::ostream& operator<<(std::ostream& os, const Object& obj);

#endif // OBJECT__H_
