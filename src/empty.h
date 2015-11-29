#ifndef EMPTY__H_
#define EMPTY__H_

#include "object.h"

class Empty : public Object
{
public:
    Empty();
    
    virtual std::string toString() const override;

    virtual std::string typeToString() const override;

    virtual bool isBoolean() const override;

    virtual bool isSymbol() const override;

    virtual bool isChar() const override;

    virtual bool isVector() const override;

    virtual bool isPair() const override;

    virtual bool isNumber() const override;

    virtual bool isString() const override;

    virtual bool isProcedure() const override;
};

#endif // EMPTY__H_
