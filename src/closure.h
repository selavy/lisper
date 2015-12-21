#ifndef CLOSURE__H_
#define CLOSURE__H_

#include <cstddef>
#include <list>
#include <string>
#include "procedure.h"

class Closure : public Procedure
{
public:
    Closure(std::list<std::string> args, std::list<std::string> body, Environment& env);

    virtual ObjectPtr evaluate(Arguments& args, Environment& env) override;

    virtual std::string typeToString() const override;

    virtual std::string toString() const override;

    void setName(const char* name);

    void printBody() const;

private:
    std::string name_;

    std::list<std::string> args_; // symbols for names of arguments

    std::size_t nArgs_;

    const std::list<std::string> body_;

    Environment& env_;
};

#endif  // CLOSURE__H_
