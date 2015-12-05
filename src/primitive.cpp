#include "primitive.h"
#include <cassert>

Primitive::Primitive(const char* name, FuncDef&& def)
    : name_(name)
    , def_(std::forward<FuncDef>(def))
{
    assert(def_);
}

ObjectPtr Primitive::evaluate(Arguments& args) 
{
    return def_(args);
}

std::string Primitive::typeToString() const
{
    return "Primitive";
}

std::string Primitive::toString() const
{
    return name_;
}
