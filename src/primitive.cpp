#include "primitive.h"
#include <algorithm>
#include <sstream>
#include "number.h"

const std::vector<std::string> PRIMITIVES = {
    "+"
};

Primitive::Primitive(std::string name)
    : name_(std::move(name))
{
    const auto found = std::find(std::begin(PRIMITIVES), std::end(PRIMITIVES), name_);
    if (found == std::end(PRIMITIVES)) {
        throw std::runtime_error("Invalid primitive: " + name_);
    }
}

std::unique_ptr<Object> Primitive::execute(Arguments args)
{
    if (name_ == "+") {
        return handlePlus(std::move(args));
    }
    
    return std::unique_ptr<Object>();
}

void Primitive::print(std::ostream& os) const
{
    os << "(" << name_ << ")";
}

std::unique_ptr<Object> Primitive::handlePlus(Arguments args)
{
    Number ret;
    for (auto arg: args) {
        if (Number* num = dynamic_cast<Number*>(&(arg.get()))) {
            ret = ret + *num;
        }
        else {
            std::ostringstream oss;
            oss << "Invalid argument to '+: " << arg;
            throw std::runtime_error(oss.str().c_str());
        }
    }
    return std::unique_ptr<Object>(new Number(ret));
}
