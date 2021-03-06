#ifndef VEC__H_
#define VEC__H_

#include <vector>
#include <list>
#include "object.h"

class Vector : public Object
{
public:
    Vector();

    Vector(std::list<ObjectPtr> objs);

    Vector(std::vector<ObjectPtr> objs);

    void append(ObjectPtr obj);

    ObjectPtr& operator[](std::size_t i);

    std::size_t size() const;

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
    std::vector<ObjectPtr> objs_;
};

Vector* toVector(const ObjectPtr& p);

#endif // VEC__H_
