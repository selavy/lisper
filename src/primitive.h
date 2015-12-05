#ifndef PRIMITIVE__H_
#define PRIMITIVE__H_

#include "procedure.h"
#include <string>
#include <list>

class Primitive : public Procedure
{
public:
    typedef ObjectPtr (*FuncDef)(Arguments&);

public:
    Primitive(const char* name, FuncDef&& def);

    virtual ObjectPtr evaluate(Arguments& args) override;

    virtual std::string typeToString() const override;

    virtual std::string toString() const override;

private:
    std::string name_;
    FuncDef def_;
};

#endif // PRIMITIVE__H_
