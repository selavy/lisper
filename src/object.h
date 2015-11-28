#ifndef OBJECT__H_
#define OBJECT__H_

#include <ostream>
#include <string>
#include <memory>

struct Object
{
    virtual ~Object();
    virtual void print(std::ostream& os) const;
    virtual std::string toString() const=0;
    virtual std::string typeToString() const=0;
    virtual bool isBoolean() const=0;
    virtual bool isSymbol() const=0;
    virtual bool isChar() const=0;
    virtual bool isVector() const=0;
    virtual bool isPair() const=0;
    virtual bool isNumber() const=0;
    virtual bool isString() const=0;
    virtual bool isProcedure() const=0;
};

std::ostream& operator<<(std::ostream& os, const Object& obj);

typedef std::unique_ptr<Object> ObjectPtr;

#endif // OBJECT__H_
