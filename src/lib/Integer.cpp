#include "../include/Integer.h"
#include <stdexcept>
#include <iostream>

// ----------------------------------------------------------------------------
// CONSTRUCTORS
// ----------------------------------------------------------------------------

Integer::Integer() {}

Integer::Integer(int value)         : Integer(std::to_string(value)) {}
Integer::Integer(const char* value) : Integer(std::string(value))    {}
Integer::Integer(const Integer &another)       : _nat(another._nat) {}
Integer::Integer(Integer &&another)            : _nat(std::move(another._nat)) {}

Integer::Integer(const std::string &value)
{
    if(value.length() == 0)
        throw std::invalid_argument("Empty string passed");
    
    _neg = (value[0] == '-');

    std::string nat_part = value.substr((unsigned)_neg);
    _nat = Natural(nat_part);
}

// ----------------------------------------------------------------------------
// COMPARISON OPERATORS
// ----------------------------------------------------------------------------

bool Integer::operator < (const Integer &another) const
{
    return _cmp(*this, another) == -1;
}

bool Integer::operator > (const Integer &another) const
{
    return _cmp(*this, another) == 1;
}

bool Integer::operator == (const Integer &another) const
{
    return _cmp(*this, another) == 0;
}

bool Integer::operator <= (const Integer &another) const
{
    return _cmp(*this, another) != 1;
}

bool Integer::operator >= (const Integer &another) const
{
    return _cmp(*this, another) != -1;
}

// ----------------------------------------------------------------------------
// BINARY OPERATORS
// ----------------------------------------------------------------------------

Integer Integer::operator + (const Integer &another) const
{
    Integer result;
    if(this->_neg == another._neg) {
        result._neg = this->_neg;
        result._nat = (this->_nat + another._nat);
    }
    else {
        if(this->_nat >  another._nat) {
            result._nat = (this->_nat - another._nat);
            result._neg = this->_neg;
        }
        else if(this->_nat < another._nat) {
            result._nat = (another._nat - this->_nat);
            result._neg = another._neg;
        }
        // if this->_nat == another._nat do nothing
        // because the result will be 0 and "result"
        // variable is already initialized with zero
    }
    return result;
}

Integer Integer::operator - (const Integer &another) const
{
    Integer result;
    
    if(!this->_neg && another._neg) {
        // two positive numbers
        if(this->_nat >= another._nat) {
            result._nat = (this->_nat - another._nat);
            result._neg = false;
        }
        
    }
}

Integer Integer::operator * (const Integer &another) const
{
    Integer result;
    
    for(std::size_t i = 0; i < another._digits.size(); i++) {
        Integer new_n = *this;
        new_n.mul_by_digit(another._digits[i]);
        new_n = new_n << i;

        result += new_n;
    }

    return result;
}

Integer Integer::operator / (const Integer &another) const
{
    if(another == 0)
        throw std::domain_error("Division be zero");
    else if(*this < another)
        return 0;
    else if(*this == another)
        return 1;

    auto result_vec = algo::basic_div(this->_digits, another._digits);
    return Integer(result_vec);
}

Integer Integer::operator % (const Integer &another) const
{
    if(another == 0)
        throw std::domain_error("Division be zero");
    else if(another == 1)
        return Integer(0);
    else if(*this < another)
        return Integer(*this);

    std::vector<uint8_t> remainder;
    algo::basic_div(this->_digits, another._digits, remainder);
    return Integer(remainder);
}

// ----------------------------------------------------------------------------
// SHIFT OPERATORS
// ----------------------------------------------------------------------------

Integer Integer::operator << (std::size_t k) const
{
    auto new_digits = this->_digits;
    for(std::size_t i = 0; i < k; i++)
        new_digits.insert(new_digits.begin(), 0);
    return new_digits;
}

// ----------------------------------------------------------------------------
// ASSIGNMENT OPERATORS
// ----------------------------------------------------------------------------

Integer &Integer::operator = (const Integer &another)
{
    if(&another != this) {
        this->_digits = another._digits; // copy digits array
    }
    return *this;
}

Integer &Integer::operator = (Integer &&another)
{
    if(&another != this) {
        this->_digits = std::move(another._digits);
    }
    return *this;
}

Integer &Integer::operator += (const Integer &another)
{
    auto new_natural = (*this) + another;
    this->_digits = std::move(new_natural._digits);  
    return *this;
}

Integer &Integer::operator -= (const Integer &another)
{
    auto new_natural = (*this) - another;
    this->_digits = std::move(new_natural._digits);  
    return *this;
}

Integer &Integer::operator *= (const Integer &another)
{
    auto new_natural = (*this) * another;
    this->_digits = std::move(new_natural._digits);  
    return *this;
}

Integer &Integer::operator %= (const Integer &another)
{
    auto new_natural = (*this) % another;
    this->_digits = std::move(new_natural._digits);  
    return *this;
}

Integer &Integer::operator <<= (std::size_t k)
{
    auto new_natural = (*this) << k;
    this->_digits = std::move(new_natural._digits);  
    return *this;
}

// ----------------------------------------------------------------------------
// INCREMENTS & DECREMENTS
// ----------------------------------------------------------------------------

Integer &Integer::operator ++ () // prefix
{
    (*this) += 1;
    return *this;
}

Integer &Integer::operator -- () // prefix
{
    (*this) -= 1;
    return *this;
}

Integer Integer::operator ++ (int) // postfix
{
    Integer copy = *this;
    ++(*this);
    return copy;
}

Integer Integer::operator -- (int) // postfix
{
    Integer copy = *this;
    --(*this);
    return copy;
}

// ----------------------------------------------------------------------------
// VISUALIZATION
// ----------------------------------------------------------------------------

Integer::operator std::string() const
{
    std::string output;
    auto it = _digits.rbegin();
    while(it != _digits.rend()) {
        output += std::to_string(*(it++));
    }
    return output;
}

std::ostream& operator<<(std::ostream& stream, const Integer &value)
{
    stream << (std::string)value;
    return stream;
}

// ----------------------------------------------------------------------------
// PRIVATE METHODS
// ----------------------------------------------------------------------------
int Integer::Integer _cmp(const Integer &a, const Integer &b) const
{
    if(a._neg && !b._neg)
        return -1;
    else if(!a._neg && b._neg)
        return 1;
    else if(a._nat == b._nat)
        return 0;
    else if(a._nat > b._nat) {
        if(a._neg && b._neg)
            return -1;
        else
            return 1;
    }
    else {
        if(a._neg && b._neg)
            return 1;
        else
            return -1;
    }
}
