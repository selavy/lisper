#include "empty.h"

Empty::~Empty()
{
}

void Empty::print(std::ostream& os) const
{
    os << "()";
}
