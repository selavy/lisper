#ifndef BOOLEAN__H_
#define BOOLEAN__H_

#include "object.h"
#include <string>

class Boolean : public Object
{
public:
    Boolean();
    Boolean(const char* val);
    virtual void print(std::ostream& os) const override;
    bool value() const;
    
    virtual bool isBoolean() const override;
    virtual bool isSymbol() const override;
    virtual bool isChar() const override;
    virtual bool isVector() const override;
    virtual bool isPair() const override;
    virtual bool isNumber() const override;
    virtual bool isString() const override;
    virtual bool isProcedure() const override;    

private:
    bool val_;
};

#endif // BOOLEAN__H_
