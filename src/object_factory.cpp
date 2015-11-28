#include "object_factory.h"
#include "integer.h"

ObjectFactory::ObjectFactory()
{
}

ObjectPtr ObjectFactory::create(std::string token)
{
    if (isInteger(token.c_str())) {
        return ObjectPtr(new Integer(token.c_str()));
    }
    else {
        return ObjectPtr();
    }
}
