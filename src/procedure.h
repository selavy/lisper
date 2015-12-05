#ifndef PROCEDURE__H_
#define PROCEDURE__H_

#include "object.h"
#include <list>

class Procedure : public Object
{
public:
    virtual ObjectPtr evaluate(std::list<ObjectPtr>& args)=0;

    virtual std::string typeToString() const override;

    virtual bool isBoolean() const=0;

    virtual bool isSymbol() const=0;

    virtual bool isChar() const=0;

    virtual bool isVector() const=0;

    virtual bool isPair() const=0;

    virtual bool isNumber() const=0;

    virtual bool isString() const=0;

    virtual bool isProcedure() const override;
};

#endif // PROCEDURE__H_
