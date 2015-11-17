#include "symbol.h"

Symbol::Symbol()
    : symbol_()
{
    throw std::runtime_error("Empty symbol!");
}

Symbol::Symbol(std::string symbol)
    : symbol_(std::move(symbol))
{
    if (symbol_.empty()) throw std::runtime_error("Empty symbol!");
    if (symbol_[0] != '\'') throw std::runtime_error("Invalid symbol: " + symbol_);
    symbol_ = symbol_.substr(1);
    if (symbol_.empty()) throw std::runtime_error("Empty symbol!");
}

void Symbol::print(std::ostream& os) const
{
    os << symbol_;
}
