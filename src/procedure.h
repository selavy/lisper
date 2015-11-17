#ifndef PROCEDURE__H_
#define PROCEDURE__H_

#include "object.h"
#include <memory>
#include <functional>
#include <vector>

class Procedure : public Object
{
public:
    typedef std::reference_wrapper<Object> RObject;
    typedef std::vector<RObject> Arguments;
public:
    virtual ~Procedure();
    virtual std::unique_ptr<Object> execute(Arguments args)=0;
};

#endif // PROCEDURE__H_
