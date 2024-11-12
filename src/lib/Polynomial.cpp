// Author: Komarov Daniil 3381

#include "../include/Polynomial.h"
#include <stdexcept>
#include <iostream>
#include <utility>

// ----------------------------------------------------------------------------
// CONSTRUCTORS
// ----------------------------------------------------------------------------

Polynomial::Polynomial() {}

Polynomial::Polynomial(int value)
{
    Rational denom(value);
    if(!denom.is_zero())
        _coeffs.emplace(Natural(0), Rational(value));
}

Polynomial::Polynomial(const Rational &value)
{
    if(!value.is_zero())
        _coeffs.emplace(Natural(0), value);
}

Polynomial::Polynomial(const std::vector<Rational> &values)
{
    for(std::size_t i = 0; i < values.size(); i++) {
        Rational denom(values[i]);
        if(!denom.is_zero())
            _coeffs.emplace(Natural(i), values[i]);
    }
}

Polynomial::Polynomial(const char *value) : Polynomial(std::string(value)) {}
Polynomial::Polynomial(const Polynomial &another) : _coeffs(another._coeffs) {}
Polynomial::Polynomial(Polynomial &&another) : _coeffs(std::move(another._coeffs)) {}

Polynomial::Polynomial(const std::string &value)
{
    // Equal to the zero constructor
    if(value.length() == 0)
        return;

    // Construct Polynomial from rational input value
    // it will have the free term only
    if(value[0] != '{' || value[value.length() - 1] != '}') {
        _coeffs.emplace(Natural(0), Rational(value));
    }
    // Full constructor
    // String must match this pattern "{k_1^deg_1;k_2^deg2}"
    // Also it may contain k without deg (like "{k_1^deg_1;k_2^deg_2;k_f}") -
    // this k_f will be interpreted as free term
    else {
        std::string actual_value = value.substr(0, value.length() - 1); // cut last '}' but not the first '{', because it's set as a delim
        std::size_t prev_delim = 0;
        std::size_t next_delim = actual_value.find(';');
        while(prev_delim != actual_value.npos) {
            std::string sub = actual_value.substr(prev_delim+1, next_delim-prev_delim-1);
            std::size_t second_delim = sub.find('^');
            if(second_delim == sub.npos) {
                auto ins_result = _coeffs.emplace(Natural(0), Rational(sub));
                if(!ins_result.second)
                    throw std::invalid_argument("Bad input string");
            }
            else {
                std::string left_part = sub.substr(0, second_delim);
                std::string right_part = sub.substr(second_delim+1);
                auto ins_result = _coeffs.emplace(Natural(right_part), Rational(left_part));
                if(!ins_result.second)
                    throw std::invalid_argument("Bad input string");
            }
            prev_delim = next_delim;
            next_delim = actual_value.find(';', prev_delim+1);
        }
    }

    this->_clear_empty();
}


// ----------------------------------------------------------------------------
// NON-MODIFIERS
// ----------------------------------------------------------------------------

bool Polynomial::is_zero() const
{
    return _coeffs.empty();
}

bool Polynomial::is_integer() const
{
    return (_coeffs.size() == 1 && _coeffs.count(Natural(0)) == 1);
}

Rational Polynomial::msc() const
{
    return (_coeffs.empty()) ? Rational(0) : _coeffs.rbegin()->second;
}

Natural Polynomial::deg() const
{
    return (_coeffs.empty()) ? Natural(0) : _coeffs.rbegin()->first;
}

Rational Polynomial::fac() const
{
    if(_coeffs.empty())
        throw std::domain_error("Trying to rationalize an empty polynomial");

    auto it = _coeffs.begin();
    const auto end = _coeffs.end();
    
    
    Integer cgcd = it->second.get_numerator();
    Natural clcm = it->second.get_denominator();
    while(++it != end) {
        cgcd = cgcd.gcd(it->second.get_numerator());
        clcm = clcm.lcm(it->second.get_denominator());
    }

    return Rational(cgcd, clcm);
}

Polynomial Polynomial::gcd(const Polynomial &another) const
{
    // Modification of the Euclidean algorithm:
    // A = greater operand (copy)
    // B = lesser  operand (copy)
    // On every step save the remainder of the division of the greater by lesser
    // into the variable where the greater operand was stored
    bool a_is_greater = true;
    Polynomial a = (this->deg() >= another.deg()) ? *this : another; // greater one goes into A
    Polynomial b = (a == *this) ? another : *this;       // the other one goes into B

    while(!a.is_zero() && !b.is_zero()) {
        if(a_is_greater)
            a %= b;
        else
            b %= a;
        a_is_greater = !a_is_greater;
    }

    Polynomial result = (a+b);
    result._clear_empty();
    return result;
}

Polynomial Polynomial::derivative() const
{
    if(_coeffs.empty())
        throw std::domain_error("Trying to get derivative from empty polynomial");

    Polynomial result;
    auto it = _coeffs.begin();
    const auto end = _coeffs.end();
    while(it != end) {
        auto k = *(it++);
        if(k.first > Natural(0)) {
            result._coeffs.emplace(k.first - Natural(1), k.second * Rational(k.first));
        }
    }

    return result;
}

Polynomial Polynomial::to_simple_roots() const
{
    // Algorithm description:
    // 1) Find the derivative of the polynomial
    // 2) Calculate GCD of the polynomial and it's derivative
    // 3) Divide the polynomial by the this GCD

    Polynomial derivative = this->derivative();
    Polynomial gcd = this->gcd(derivative);
    Polynomial result = *this / gcd;

    result._clear_empty();
    return result;
}

// ----------------------------------------------------------------------------
// COMPARISON OPERATORS
// ----------------------------------------------------------------------------

bool Polynomial::operator == (const Polynomial &another) const
{
    if(this->_coeffs.size() != another._coeffs.size() || this->deg() != another.deg())
        return false;

    auto it_a = this->_coeffs.begin();
    auto it_b = another._coeffs.begin();
    const auto end_a = this->_coeffs.end();
    while(it_a != end_a) {
        if(it_a->first != it_b->first || it_a->second != it_b->second)
            return false;
        it_a++;
        it_b++;
    }
    return true;
}

bool Polynomial::operator != (const Polynomial &another) const
{
    return !(*this == another);
}

// ----------------------------------------------------------------------------
// BINARY OPERATORS
// ----------------------------------------------------------------------------

Polynomial Polynomial::operator + (const Polynomial &another) const
{
    Polynomial result = *this;
    auto it = another._coeffs.begin();
    const auto end = another._coeffs.end();
    while(it != end) {
        if(result._coeffs.count(it->first) == 1)
            result._coeffs[it->first] = result._coeffs[it->first] + it->second;
        else
            result._coeffs.emplace(it->first, it->second);
        ++it;
    }

    result._clear_empty();
    return result;
}

Polynomial Polynomial::operator - (const Polynomial &another) const
{
    Polynomial result = *this;
    auto it = another._coeffs.begin();
    const auto end = another._coeffs.end();
    while(it != end) {
        if(result._coeffs.count(it->first))
            result._coeffs[it->first] = result._coeffs[it->first] - it->second;
        else
            result._coeffs.emplace(it->first, it->second.get_neg());
        ++it;
    }

    result._clear_empty();
    return result;
}

Polynomial Polynomial::operator * (const Polynomial &another) const
{
    Polynomial result;
    auto it = another._coeffs.begin();
    const auto end = another._coeffs.end();
    while(it != end) {
        Polynomial part = (*this) * it->second;
        part = part << it->first;
        result += part;
        ++it;
    }
    
    result._clear_empty();
    return result;
}

Polynomial Polynomial::operator * (const Rational &another) const
{
    Polynomial result;
    auto it = this->_coeffs.begin();
    const auto end = this->_coeffs.end();
    while(it != end) {
        result._coeffs.emplace(it->first, it->second * another);
        ++it;
    }

    result._clear_empty();
    return result;
}

Polynomial Polynomial::operator / (const Polynomial &another) const
{
    if (another.is_zero())
        throw std::domain_error("Division by zero!");

    // A = B * Q + R, we need to find Q

    Polynomial R(*this);
    Polynomial Q;

    Rational alpha(1);

    if (another.msc() != Rational(1))
        alpha /= another.msc();

    // std::cout << "Alpha is " << (std::string)alpha << std::endl;
    // std::cout << "R before is " << (std::string)R << std::endl;
    // std::cout << "Q before is " << (std::string)Q << std::endl;

    while (R.deg() >= another.deg() && !R.is_zero()) {
        Polynomial T;
        T._coeffs.emplace(R.deg() - another.deg(), R.msc() * alpha);
        Q += T;
        R = R - T * another;
        
        // std::cout << "T is " << (std::string)T << std::endl;
        // std::cout << "Q is " << (std::string)Q << std::endl;
        // std::cout << "R is " << (std::string)R << std::endl;
    }

    return Q;
}

Polynomial Polynomial::operator % (const Polynomial &another) const
{
    if (another.is_zero())
        throw std::domain_error("Division by zero!");

    // from a % b = a - b * (a / b)
    return Polynomial(*this - another * (*this / another));
}

Polynomial Polynomial::operator << (Natural k) const
{
    Polynomial result;
    
    // since there is no way to change keys in the map,
    // let's just recreate the map with new keys and replace the old one
    std::map<Natural, Rational> new_coeffs;

    auto it = _coeffs.begin();
    const auto end = _coeffs.end();
    while(it != end) {
        auto old_pair = *(it++);
        new_coeffs.emplace(old_pair.first + k, old_pair.second);
    }

    result._coeffs = new_coeffs;
    return result;
}

// ----------------------------------------------------------------------------
// ASSIGNMENT OPERATORS
// ----------------------------------------------------------------------------

Polynomial &Polynomial::operator = (const Polynomial &another)
{
    if(&another != this) {
        this->_coeffs = another._coeffs;
    }
    return *this;
}

Polynomial &Polynomial::operator = (Polynomial &&another)
{
    if(&another != this) {
        this->_coeffs = std::move(another._coeffs);
    }
    return *this;
}

Polynomial &Polynomial::operator += (const Polynomial &another)
{
    auto new_obj = (*this) + another;
    this->_coeffs = std::move(new_obj._coeffs);  
    return *this;
}

Polynomial &Polynomial::operator -= (const Polynomial &another)
{
    auto new_obj = (*this) - another;
    this->_coeffs = std::move(new_obj._coeffs);  
    return *this;
}

Polynomial &Polynomial::operator *= (const Rational &another)
{
    auto new_obj = (*this) * another;
    this->_coeffs = std::move(new_obj._coeffs);  
    return *this;
}

Polynomial &Polynomial::operator *= (const Polynomial &another)
{
    auto new_obj = (*this) * another;
    this->_coeffs = std::move(new_obj._coeffs);  
    return *this;
}

Polynomial &Polynomial::operator /= (const Polynomial &another)
{
    auto new_obj = (*this) / another;
    this->_coeffs = std::move(new_obj._coeffs);  
    return *this;
}

Polynomial &Polynomial::operator %= (const Polynomial &another)
{
    auto new_obj = (*this) % another;
    this->_coeffs = std::move(new_obj._coeffs);  
    return *this;
}

Polynomial &Polynomial::operator <<= (Natural k)
{
    auto new_polynomial = (*this) << k;
    this->_coeffs = std::move(new_polynomial._coeffs);  
    return *this;
}

// ----------------------------------------------------------------------------
// VISUALIZATION
// ----------------------------------------------------------------------------

Polynomial::operator std::string() const
{
    if(this->is_zero())
        return "0";
    
    if(this->is_integer())
        return static_cast<std::string>(this->_coeffs.at(Natural(0)));
    
    std::string output = "{";
    auto it = this->_coeffs.rbegin();
    const auto end = this->_coeffs.rend();
    while(true) {
        output += static_cast<std::string>(it->second);
        if(!it->first.is_zero()) {
            output += '^';
            output += static_cast<std::string>(it->first);
        }
        if(++it != end)
            output += ';';
        else
            break;
    }
    output += '}';
    return output;
}

std::ostream& operator<<(std::ostream& stream, const Polynomial &value)
{
    stream << (std::string)value;
    return stream;
}

// ----------------------------------------------------------------------------
// PRIVATE FUNCTIONS
// ----------------------------------------------------------------------------

// Delete all zero coeffs from the polynomial
void Polynomial::_clear_empty()
{
    auto it = this->_coeffs.begin();
    const auto end = this->_coeffs.end();
    while(it != end) {
        if(it->second.is_zero())
            it = this->_coeffs.erase(it);
        else
            ++it;
    }
}
