#ifndef PAIR__H_
#define PAIR__H_

#include "object.h"

class Pair : public Object
{
public:
    Pair(Object* first=0, Object* second=0);

    const ObjectPtr& first() const;

    const ObjectPtr& second() const;

    void setFirst(Object* obj);
    
    void setSecond(Object* obj);

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

private:
    ObjectPtr first_;
    ObjectPtr second_;
};

ObjectPtr cons(ObjectPtr first, ObjectPtr second);

#define CONS(f, s) cons(std::move(f), std::move(s))

#endif // PAIR__H_
