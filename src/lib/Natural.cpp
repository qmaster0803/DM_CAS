#include "../include/Natural.h"
#include <stdexcept>

Natural::Natural()
{
    _digits.emplace_back(0);
}

Natural::Natural(std::vector<uint8_t> &digits)
{
    _digits = digits;
}

Natural::Natural(const std::string &value)
{
    if(value.length() == 0)
        throw std::invalid_argument("Empty string passed");
    
    for(ssize_t i = value.length() - 1; i >= 0; i--) {
        // just copy digit into the vector with some checks
        int intval = value[i] - '0';
        if(intval > 9 || intval < 0)
            throw std::invalid_argument("Non-digit character in the input string");
        
        _digits.emplace_back(intval);
    }
}

void Natural::mul_by_digit(uint8_t digit)
{
    auto new_digits = algo::basic_mul(this->_digits, digit);
    this->_digits = new_digits;
}

Natural Natural::operator << (std::size_t k) const
{
    auto new_digits = this->_digits;
    for(std::size_t i = 0; i < k; i++)
        new_digits.insert(new_digits.begin(), 0);
    return new_digits;
}

Natural Natural::operator + (const Natural &another) const
{
    auto new_digits = algo::basic_add(this->_digits, another._digits);
    Natural result(new_digits);
    return result;
}

Natural &Natural::operator += (const Natural &another)
{
    auto new_digits = algo::basic_add(this->_digits, another._digits);
    this->_digits = new_digits;
    return *this;
}


Natural Natural::operator - (const Natural &another) const
{
    auto new_digits = algo::basic_sub(this->_digits, another._digits);
    Natural result(new_digits);
    return result;
}

Natural Natural::operator * (const Natural &another) const
{
    Natural result;
    
    for(std::size_t i = 0; i < another._digits.size(); i++) {
        Natural new_n = *this;
        new_n.mul_by_digit(another._digits[i]);
        new_n = new_n << i;

        result += new_n;
    }

    return result;
}

Natural operator / (const Natural &another) const;
Natural operator % (const Natural &another) const;
