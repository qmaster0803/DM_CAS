// Author: Ivanov Artyom 3381

#include "../include/Rational.h"
#include <stdexcept>
#include <iostream>

// ----------------------------------------------------------------------------
// CONSTRUCTORS
// ----------------------------------------------------------------------------

Rational::Rational() : _num(0), _denom(1) {}
Rational::Rational(int value) : _num(value), _denom(1) {}
Rational::Rational(const Natural &value) : _num(value), _denom(1) {}
Rational::Rational(const Integer &value) : _num(value), _denom(1) {}
Rational::Rational(const char *value) : Rational(std::string(value)) {}
Rational::Rational(const Integer &numerator, const Natural &denominator) : _num(numerator), _denom(denominator)
{
    if(this->_denom.is_zero())
        throw std::invalid_argument("Rational number denominator is zero");
    this->reduct();
}

Rational::Rational(const Rational &another) : _num(another._num), _denom(another._denom) {}
Rational::Rational(Rational &&another)      : _num(std::move(another._num)), _denom(std::move(another._denom)) {}

Rational::Rational(const std::string &value)
{
    if(value.size() == 0)
        throw std::invalid_argument("Empty string passed");
    
    // check string for characters
    std::size_t slash_count = std::count(value.begin(), value.end(), '/');
    std::size_t point_count = std::count(value.begin(), value.end(), '.');

    // check for counts of / and . characters
    if(slash_count != 0 && point_count != 0) {
        // create Rational from Integer
        this->_num   = Integer(value);
        this->_denom = Natural(1);
    }

    const char delim = (slash_count) ? '/' : '.';
    std::size_t delim_pos = value.find(delim);
    std::string left_part = value.substr(0, delim_pos);
    std::string right_part = (delim_pos != -1) ? (value.substr(delim_pos + 1)) : ("");

    if(slash_count) {
        // format is "numerator/denominator"
        Integer _num_tmp   = Integer(left_part);
        Integer _denom_tmp = Integer(right_part);
        // they both are integers to correctly handle values like "123/-123"
        this->_num   = _num_tmp.abs();
        this->_denom = Natural(_denom_tmp.abs());
        // set correct sign
        if(!_num.is_zero() && (_num_tmp.is_neg() ^ _denom_tmp.is_neg()))
            this->_num.neg();
        
    } else {
        _num = Integer(left_part + right_part);
        _denom = Natural(1);
        _denom <<= Natural(right_part.size());
    }

    if (_denom == Natural(0))
        throw std::invalid_argument("Denominator must be non zero value!\n");

    this->reduct();
}

// ----------------------------------------------------------------------------
// MODIFIERS
// ----------------------------------------------------------------------------

void Rational::reduct()
{
    // get the GCD of numerator and denomiator, then divide them
    Natural gcd = _num.gcd(Integer(_denom));
    _num   /= Integer(gcd);
    _denom /= gcd;
}

// ----------------------------------------------------------------------------
// NON-MODIFIERS
// ----------------------------------------------------------------------------

bool Rational::is_zero() const { return _num.is_zero(); }

bool Rational::is_neg() const { return _num.is_neg(); }

bool Rational::is_reducted() const
{
    return _num.gcd(Integer(_denom)) == Integer(1);
}

bool Rational::is_integer() const
{
    return (this->is_reducted() && this->_denom == Natural(1));
}

Integer Rational::get_numerator()   const
{
    return Integer(this->_num);
}

Natural Rational::get_denominator() const
{
    return Natural(this->_denom);
}

Rational Rational::get_neg() const
{
    Rational result = *this;
    result._num.neg();
    return result;
}

Rational Rational::abs() const
{
    Rational result(_num.abs(), _denom);
    return result;
}

// ----------------------------------------------------------------------------
// COMPARISON OPERATORS
// ----------------------------------------------------------------------------

// All of the operators reduce fractions to the common denomiator,
// then compare numerators
bool Rational::operator < (const Rational &another) const
{
    Rational a(*this);
    Rational b(another);
    a._to_common_denom(b);
    return a._num < b._num;
}

bool Rational::operator > (const Rational &another) const
{
    Rational a(*this);
    Rational b(another);
    a._to_common_denom(b);
    return a._num > b._num;
}

bool Rational::operator == (const Rational &another) const
{
    Rational a(*this);
    Rational b(another);
    a._to_common_denom(b);
    return a._num == b._num;
}

bool Rational::operator <= (const Rational &another) const
{
    Rational a(*this);
    Rational b(another);
    a._to_common_denom(b);
    return a._num <= b._num;
}

bool Rational::operator >= (const Rational &another) const
{
    Rational a(*this);
    Rational b(another);
    a._to_common_denom(b);
    return a._num >= b._num;
}

bool Rational::operator != (const Rational &another) const
{
    Rational a(*this);
    Rational b(another);
    a._to_common_denom(b);
    return a._num != b._num;
}

// ----------------------------------------------------------------------------
// BINARY OPERATORS
// ----------------------------------------------------------------------------

Rational Rational::operator + (const Rational &another) const
{
    Rational result(*this);
    Rational tmp(another);
    result._to_common_denom(tmp);
    result._num += tmp._num;
    result.reduct();
    return result;
}

Rational Rational::operator - (const Rational &another) const
{
    Rational result(*this);
    Rational tmp(another);
    result._to_common_denom(tmp);
    result._num -= tmp._num;
    result.reduct();
    return result;
}

Rational Rational::operator * (const Rational &another) const
{
    Rational result;
    result._num = this->_num.abs() * another._num.abs();
    result._denom = this->_denom * another._denom;
    result.reduct();
    if((this->_num.is_neg() ^ another._num.is_neg()) && !result._num.is_zero())
        result._num.neg();
    
    return result;
}

Rational Rational::operator / (const Rational &another) const
{
    if(another.is_zero())
        throw std::domain_error("Division be zero");

    Rational result;
    result._num = this->_num.abs() * Integer(another._denom);
    result._denom = this->_denom * static_cast<Natural>(another._num.abs());
    result.reduct();
    if((this->_num.is_neg() ^ another._num.is_neg()) && !result._num.is_zero())
        result._num.neg();

    return result;
}

// ----------------------------------------------------------------------------
// ASSIGNMENT OPERATORS
// ----------------------------------------------------------------------------

// copy
Rational &Rational::operator = (const Rational &another)
{
    if(&another != this) {
        this->_num   = another._num;
        this->_denom = another._denom;
    }
    return *this;
}

// move
Rational &Rational::operator = (Rational &&another)
{
    if(&another != this) {
        this->_num   = std::move(another._num);
        this->_denom = std::move(another._denom);
    }
    return *this;
}
Rational &Rational::operator += (const Rational &another)
{
    auto n = (*this) + another;
    this->_num   = std::move(n._num);
    this->_denom = std::move(n._denom);
    return *this;
}

Rational &Rational::operator -= (const Rational &another)
{
    auto n = (*this) - another;
    this->_num   = std::move(n._num);
    this->_denom = std::move(n._denom);
    return *this;
}

Rational &Rational::operator *= (const Rational &another)
{
    auto n = (*this) * another;
    this->_num   = std::move(n._num);
    this->_denom = std::move(n._denom);
    return *this;
}

Rational &Rational::operator /= (const Rational &another)
{
    auto n = (*this) / another;
    this->_num   = std::move(n._num);
    this->_denom = std::move(n._denom);
    return *this;
}

// ----------------------------------------------------------------------------
// VISUALIZATION
// ----------------------------------------------------------------------------

Rational::operator std::string() const
{
    if(this->is_integer())
        return static_cast<std::string>(this->_num);
    
    std::string output;
    output += static_cast<std::string>(this->_num);
    output += '/';
    output += static_cast<std::string>(this->_denom);
    return output;
}

Rational::operator Integer() const
{
    if(!this->is_integer())
        throw std::runtime_error("Casting non-integer Rational(" + static_cast<std::string>(*this) + ") to Integer.");

    return Integer(this->_num);
}

std::ostream& operator<<(std::ostream& stream, const Rational &value)
{
    stream << static_cast<std::string>(value);
    return stream;
}

// ----------------------------------------------------------------------------
// PRIVATE METHODS
// ----------------------------------------------------------------------------

void Rational::_to_common_denom(Rational &another)
{
    Natural common_denom = this->_denom.lcm(another._denom);
    this->_num   *= Integer(common_denom / this->_denom);
    another._num *= Integer(common_denom / another._denom);
    this->_denom = common_denom;
    another._denom = std::move(common_denom);
}
