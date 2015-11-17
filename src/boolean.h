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

private:
    bool val_;
};

#endif // BOOLEAN__H_
