#include "str.h"

String::String()
    : str_()
{
}

String::String(const char* str)
    : str_(str)
{
    if (str_.empty()) {
        return;
    }
    else if (str_.size() < 2) {
        throw std::runtime_error("Invalid string literal: " + str_);
    }
    else if (str_.front() != '"') {
        throw std::runtime_error("Invalid string literal: " + str_);
    }
    else if (str_.back() != '"') {
        throw std::runtime_error("Invalid string literal: " + str_);
    }
    else {
        str_ = str_.substr(1, str_.size() - 2); // pop front and back '"' character
    }
}

const std::string& String::value() const
{
    return str_;
}

void String::print(std::ostream& os) const
{
    os << str_;
}

String& String::operator+(const String& str)
{
    str_ += str.str_;
    return *this;
}
