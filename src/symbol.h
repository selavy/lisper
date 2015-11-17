#ifndef SYMBOL__H_
#define SYMBOL__H_

#include "object.h"
#include <string>

class Symbol : public Object
{
public:
    Symbol();
    Symbol(std::string symbol);
    void print(std::ostream& os) const override;
    
private:
    std::string symbol_;
};
    
#endif // SYMBOL__H_
