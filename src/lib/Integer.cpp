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

bool Integer::operator != (const Integer &another) const
{
    return _cmp(*this, another) != 0;
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
    
    if(this->_neg == another._neg) { // two numbers with the same sign
        if(this->_nat >= another._nat) {
            result._nat = (this->_nat - another._nat);
            result._neg = another._neg;
        }
        else {
            result._nat = (another._nat - this->_nat);
            result._neg = !another._neg;
        }
    }
    else {
         result._nat = (this->_nat + another._nat);
         result._neg = this->_neg;
    }

    return result;
}

Integer Integer::operator * (const Integer &another) const
{
    Integer result;
    
    result._nat = (this->_nat * another._nat);
    result._neg = (this->_neg != another._neg);
    
    return result;
}

Integer Integer::operator / (const Integer &another) const
{
    if(another == 0)
        throw std::domain_error("Division be zero");

    Integer result;
    result._neg = (this->_neg != another._neg);
    result._nat = (this->_nat / another._nat);
    if(result._neg && (this->_nat % another._nat != Natural(0)))
        ++result._nat;

    return result;
}

// 15 % 4 => ( 3 * 4) + 3 = ([ 15//4] * 4) + 3 = 15  => 3 =  15 - ([ 15//4] * 4)
//-15 % 4 => (-4 * 4) + 1 = ([-15//4] * 4) + 1 = -15 => 1 = -15 - ([-15//4] * 4)
Integer Integer::operator % (const Integer &another) const
{
    if(another == 0)
        throw std::domain_error("Division be zero");

    return Integer(*this - ((*this / another) * another));
}

// ----------------------------------------------------------------------------
// SHIFT OPERATORS
// ----------------------------------------------------------------------------

Integer Integer::operator << (std::size_t k) const
{
    Integer result(*this);
    result._nat <<= k;
    return k;
}

// ----------------------------------------------------------------------------
// ASSIGNMENT OPERATORS
// ----------------------------------------------------------------------------

// copy
Integer &Integer::operator = (const Integer &another)
{
    if(&another != this) {
        this->_nat = another._nat;
        this->_neg = another._neg;
    }
    return *this;
}

// move
Integer &Integer::operator = (Integer &&another)
{
    if(&another != this) {
        this->_nat = std::move(another._nat);
        this->_neg = another._neg;
    }
    return *this;
}

Integer &Integer::operator += (const Integer &another)
{
    auto n = (*this) + another;
    this->_nat = std::move(n._nat);  
    this->_neg = n._neg;
    return *this;
}

Integer &Integer::operator -= (const Integer &another)
{
    auto n = (*this) - another;
    this->_nat = std::move(n._nat);  
    this->_neg = n._neg;
    return *this;
}

Integer &Integer::operator *= (const Integer &another)
{
    auto n = (*this) * another;
    this->_nat = std::move(n._nat);  
    this->_neg = n._neg;
    return *this;
}

Integer &Integer::operator %= (const Integer &another)
{
    auto n = (*this) % another;
    this->_nat = std::move(n._nat);  
    this->_neg = n._neg;
    return *this;
}

Integer &Integer::operator <<= (std::size_t k)
{
    auto n = (*this) << k;
    this->_nat = std::move(n._nat);  
    this->_neg = n._neg;
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
    if(this->_neg)
        output += '-';
    output += (std::string)this->_nat;
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
int Integer::_cmp(const Integer &a, const Integer &b) const
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
