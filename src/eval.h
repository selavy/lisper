#ifndef EVAL__H_
#define EVAL__H_

#include "object.h"
#include <list>

class Environment;

#define POP(x) x.pop_front()
#define PUSH(x, v) x.push_back(v)
#define FIRST(x) (*(std::begin(x)))
#define SECOND(x) (*std::next(std::begin(x), 1))
#define THIRD(x) (*std::next(std::begin(x), 2))

//\! Evaluates a std::list<> into a single ObjectPtr
ObjectPtr evaluateList(std::list<ObjectPtr>& tokens, Environment& env);

#endif // EVAL__H_
