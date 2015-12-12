#include "eval.h"
#include <stdexcept>
#include <string>
#include "environment.h"
#include "procedure.h"

//\! Evaluates a std::list<> into a single ObjectPtr
ObjectPtr evaluateList(std::list<ObjectPtr>& tokens, Environment& env)
{
    ObjectPtr head = tokens.front();
    POP(tokens);

    const std::string& name = head->toString();

    Environment* scope = &env;
    while (scope) {
        auto found = scope->find(name);
        if (found != std::end(*scope)) {
            ObjectPtr& obj = found->second;
            if (obj->isProcedure()) {
                Procedure* proc = dynamic_cast<Procedure*>(obj.get());
                return proc->evaluate(tokens, *scope);
            }
            else {
                throw std::runtime_error("Did not find a procedure where it was expected: " + name);
            }
        }
        else {
            scope = scope->getParent();
        }
    }

    throw std::runtime_error("Not a valid procedure: " + name);
}
