#ifndef EMPTY__H_
#define EMTPY__H_

#include "object.h"

class Empty : public Object
{
    virtual ~Empty();
    virtual void print(std::ostream& os) const override;
};

#endif // EMPTY__H_
