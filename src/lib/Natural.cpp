#include "../include/Natural.h"
#include <stdexcept>
#include <iostream>

// ----------------------------------------------------------------------------
// CONSTRUCTORS
// ----------------------------------------------------------------------------

Natural::Natural()
{
    _digits.emplace_back(0);
}

Natural::Natural(int value)         : Natural(std::to_string(value)) {}
Natural::Natural(const char* value) : Natural(std::string(value))    {}
Natural::Natural(std::vector<uint8_t> &digits) : _digits(digits) {}
Natural::Natural(const Natural &another)       : _digits(another._digits) {}
Natural::Natural(Natural &&another)            : _digits(std::move(another._digits)) {}

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

// ----------------------------------------------------------------------------
// MODIFIERS
// ----------------------------------------------------------------------------

void Natural::mul_by_digit(uint8_t digit)
{
    auto new_digits = algo::basic_mul(this->_digits, digit);
    this->_digits = new_digits;
}

// ----------------------------------------------------------------------------
// NON-MODIFIERS
// ----------------------------------------------------------------------------

bool Natural::is_zero() const
{
    return (this->_digits.size() == 1 && this->_digits[0] == 0);
}

Natural Natural::gcd(const Natural &another) const
{
    // Modification of the Euclidean algorithm:
    // A = greater operand (copy)
    // B = lesser  operand (copy)
    // On every step save the remainder of the division of the greater by lesser
    // into the variable where the greater operand was stored
    bool a_is_greater = true;
    Natural a = (*this >= another) ? *this : another; // greater one goes into A
    Natural b = (a == *this) ? another : *this;       // the other one goes into B

    while(!a.is_zero() && !b.is_zero()) {
        if(a_is_greater)
            a %= b;
        else
            b %= a;
        a_is_greater = !a_is_greater;
    }

    return (a+b);
}

Natural Natural::lcm(const Natural &another) const
{
    if(this->is_zero() || another.is_zero())
        return Natural(0);
    
    Natural result(*this * another);
    result /= this->gcd(another);
    return result;
}

// ----------------------------------------------------------------------------
// COMPARISON OPERATORS
// ----------------------------------------------------------------------------

bool Natural::operator < (const Natural &another) const
{
    return algo::basic_cmp(this->_digits, another._digits) == -1;
}

bool Natural::operator > (const Natural &another) const
{
    return algo::basic_cmp(this->_digits, another._digits) == 1;
}

bool Natural::operator == (const Natural &another) const
{
    return algo::basic_cmp(this->_digits, another._digits) == 0;
}

bool Natural::operator <= (const Natural &another) const
{
    return algo::basic_cmp(this->_digits, another._digits) != 1;
}

bool Natural::operator >= (const Natural &another) const
{
    return algo::basic_cmp(this->_digits, another._digits) != -1;
}

bool Natural::operator != (const Natural &another) const
{
    return algo::basic_cmp(this->_digits, another._digits) != 0;
}

// ----------------------------------------------------------------------------
// BINARY OPERATORS
// ----------------------------------------------------------------------------

Natural Natural::operator + (const Natural &another) const
{
    auto new_digits = algo::basic_add(this->_digits, another._digits);
    Natural result(new_digits);
    return result;
}

Natural Natural::operator - (const Natural &another) const
{
    if(*this < another)
        throw std::out_of_range("Subtraction of natural numbers results in a negative number");
    
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

Natural Natural::operator / (const Natural &another) const
{
    if(another.is_zero())
        throw std::domain_error("Division be zero");
    else if(*this < another)
        return Natural(0);
    else if(*this == another)
        return Natural(1);

    auto result_vec = algo::basic_div(this->_digits, another._digits);
    return Natural(result_vec);
}

Natural Natural::operator % (const Natural &another) const
{
    if(another.is_zero())
        throw std::domain_error("Division be zero");
    else if(another == Natural(1))
        return Natural(0);
    else if(*this < another)
        return Natural(*this);

    std::vector<uint8_t> remainder;
    algo::basic_div(this->_digits, another._digits, remainder);
    return Natural(remainder);
}

// ----------------------------------------------------------------------------
// SHIFT OPERATORS
// ----------------------------------------------------------------------------

Natural Natural::operator << (std::size_t k) const
{
    Natural result(*this);
    if(result.is_zero())
        return result;
    for(std::size_t i = 0; i < k; i++)
        result._digits.insert(result._digits.begin(), 0);
    return result;
}

// ----------------------------------------------------------------------------
// ASSIGNMENT OPERATORS
// ----------------------------------------------------------------------------

Natural &Natural::operator = (const Natural &another)
{
    if(&another != this) {
        this->_digits = another._digits; // copy digits array
    }
    return *this;
}

Natural &Natural::operator = (Natural &&another)
{
    if(&another != this) {
        this->_digits = std::move(another._digits);
    }
    return *this;
}

Natural &Natural::operator += (const Natural &another)
{
    auto new_natural = (*this) + another;
    this->_digits = std::move(new_natural._digits);  
    return *this;
}

Natural &Natural::operator -= (const Natural &another)
{
    auto new_natural = (*this) - another;
    this->_digits = std::move(new_natural._digits);  
    return *this;
}

Natural &Natural::operator *= (const Natural &another)
{
    auto new_natural = (*this) * another;
    this->_digits = std::move(new_natural._digits);  
    return *this;
}

Natural &Natural::operator /= (const Natural &another)
{
    auto new_natural = (*this) / another;
    this->_digits = std::move(new_natural._digits);  
    return *this;
}

Natural &Natural::operator %= (const Natural &another)
{
    auto new_natural = (*this) % another;
    this->_digits = std::move(new_natural._digits);  
    return *this;
}

Natural &Natural::operator <<= (std::size_t k)
{
    auto new_natural = (*this) << k;
    this->_digits = std::move(new_natural._digits);  
    return *this;
}

// ----------------------------------------------------------------------------
// INCREMENTS & DECREMENTS
// ----------------------------------------------------------------------------

Natural &Natural::operator ++ () // prefix
{
    (*this) += Natural(1);
    return *this;
}

Natural &Natural::operator -- () // prefix
{
    (*this) -= Natural(1);
    return *this;
}

Natural Natural::operator ++ (int) // postfix
{
    Natural copy = *this;
    ++(*this);
    return copy;
}

Natural Natural::operator -- (int) // postfix
{
    Natural copy = *this;
    --(*this);
    return copy;
}

// ----------------------------------------------------------------------------
// VISUALIZATION
// ----------------------------------------------------------------------------

Natural::operator std::string() const
{
    std::string output;
    auto it = _digits.rbegin();
    while(it != _digits.rend()) {
        output += std::to_string(*(it++));
    }
    return output;
}

std::ostream& operator<<(std::ostream& stream, const Natural &value)
{
    stream << (std::string)value;
    return stream;
}
