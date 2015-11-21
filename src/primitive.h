#ifndef PRIMITIVE__H_
#define PRIMITIVE__H_

#include "procedure.h"

class Primitive : public Procedure
{
public:
    Primitive(std::string name);

    virtual std::unique_ptr<Object> execute(Arguments args);

    virtual void print(std::ostream& os) const override;

private:
    std::unique_ptr<Object> handlePlus(Arguments args);
    
private:
    std::string name_;
};

// returns NULL if not a primitive
std::unique_ptr<Object> createPrimitive(std::string val);

#endif // PRIMITIVE__H_
