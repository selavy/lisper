#ifndef STR__H_
#define STR__H_

#include "object.h"
#include <string>
#include <ostream>

class String : public Object
{
public:
    String();

    String(const char* str);

    virtual ~String();

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
    std::string str_;
};

String* toString(const ObjectPtr& p);

#endif // STR__H_
