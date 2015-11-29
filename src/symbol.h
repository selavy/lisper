#ifndef SYMBOL__H_
#define SYMBOL__H_

#include "object.h"
#include <string>

class Symbol : public Object
{
public:
    Symbol();

    Symbol(const char* symbol);
    
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
    std::string symbol_;
};

#endif // SYMBOL__H_
