#ifndef BOOLEAN__H_
#define BOOLEAN__H_

#include "object.h"
#include <string>

class Boolean : public Object
{
public:
    Boolean();

    Boolean(bool val);
    
    Boolean(const char* val);

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

    bool value() const;    

    static bool isBoolean(const char* val);
    
private:
    bool val_;

private:
    static const char * const FALSE_STR;
    static const char * const TRUE_STR;
};

#endif // BOOLEAN__H_
