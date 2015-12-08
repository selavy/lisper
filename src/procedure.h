#ifndef PROCEDURE__H_
#define PROCEDURE__H_

#include "environment.h"
#include "object.h"
#include <list>

typedef std::list<ObjectPtr> Arguments;

class Procedure : public Object
{
public:
    virtual ObjectPtr evaluate(Arguments& args, Environment& env)=0;

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
