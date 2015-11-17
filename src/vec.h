#ifndef VEC__H_
#define VEC__H_

#include "object.h"
#include <vector>
#include <functional>

class Vector : public Object
{
public:
    typedef std::reference_wrapper<const Object> CRObject;
    typedef std::vector<CRObject> Objects;
public:
    Vector();

    Vector(Objects objs);

    void push_back(const Object& obj);

    void print(std::ostream& os) const;
    
private:
    Objects data_;
};

#endif // VEC__H_
