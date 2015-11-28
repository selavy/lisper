#ifndef OBJECT_FACTORY__H_
#define OBJECT_FACTORY__H_

#include "object.h"
#include <string>

class ObjectFactory
{
public:
    ObjectFactory();

    ObjectPtr create(std::string token);
};

#endif // OBJECT_FACTORY__H_
