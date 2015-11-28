#ifndef NUMBER__H_
#define NUMBER__H_

#include "object.h"

class Number : public Object
{
public:
    virtual bool isBoolean() const override;
    virtual bool isSymbol() const override;
    virtual bool isChar() const override;
    virtual bool isVector() const override;
    virtual bool isPair() const override;
    virtual bool isNumber() const override;
    virtual bool isString() const override;
    virtual bool isProcedure() const override;
};

#endif // NUMBER__H_
