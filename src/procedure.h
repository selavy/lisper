#ifndef PROCEDURE__H_
#define PROCEDURE__H_

#include "object.h"
#include <list>

class Procedure : public Object
{
public:
    virtual ObjectPtr evaluate(std::list<ObjectPtr>& args)=0;

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

#endif // PROCEDURE__H_
