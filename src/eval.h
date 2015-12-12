#ifndef EVAL__H_
#define EVAL__H_

#include "object.h"
#include <list>
#include "tokenize.h"

class Environment;

#define POP(x) x.pop_front()
#define PUSH(x, v) x.push_back(v)
#define FIRST(x) (*(std::begin(x)))
#define SECOND(x) (*std::next(std::begin(x), 1))
#define THIRD(x) (*std::next(std::begin(x), 2))

//\! Evaluates a std::list<> into a single ObjectPtr
ObjectPtr evaluateList(std::list<ObjectPtr>& tokens, Environment& env);

ObjectPtr evaluate(std::list<Token>& tokens, Environment& env);

ObjectPtr createList(ObjectPtr curr, std::list<ObjectPtr>& objs);

std::list<ObjectPtr> readTail(std::list<Token>& tokens, Environment& env);

std::list<ObjectPtr> unwrapPairs(ObjectPtr pair);

#endif // EVAL__H_
