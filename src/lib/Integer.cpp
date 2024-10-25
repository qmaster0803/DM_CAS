#include "../include/Integer.h"
#include <stdexcept>

Integer::Integer()
{
    _digits.emplace_back(0);
}

Integer::Integer(const std::string &value)
{
    if(value.length() == 0)
        throw std::invalid_argument("Empty string passed");
    
    if(value[0] == '-')
        _negative = true;

    for(std::size_t i = value.length() - 1; i > (_negative) ? 1 : 0; i--) {
        // just copy digit into the vector with some checks
        int intval = value[i] - '0';
        if(intval > 9 || intval < 0)
            throw std::invalid_argument("Non-digit character in the input string");
        
        _digits.emplace_back(intval);
    }
}

Integer Integer::operator + (const Integer &another) const
{
    Integer ()
}
Integer operator - (const Integer &another) const;
Integer operator * (const Integer &another) const;
Integer operator / (const Integer &another) const;
Integer operator % (const Integer &another) const;
