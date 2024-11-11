// Author: Komarov Daniil 3381

#pragma once
#include "Rational.h"
#include "Natural.h"
#include <string>
#include <map>

class Polynomial
{
public:
    Polynomial();                                             // new 0
    explicit Polynomial(int value);                           // new from int
    explicit Polynomial(const std::string &value);            // new from string
    explicit Polynomial(const char *value);                   // new from char array
    explicit Polynomial(const Rational &value);
    explicit Polynomial(const std::vector<Rational> &values); // from Rational vector
    Polynomial(const Polynomial &another);                    // copy constructor
    Polynomial(Polynomial &&another);                         // move constructor

    bool is_zero()    const;
    bool is_integer() const;
    // most significant coefficient
    Rational   msc()  const;
    Natural    deg()  const;
    Rational   fac()  const;
    Polynomial derivative() const;
    Polynomial to_simple_roots() const;
    Polynomial gcd(const Polynomial &another) const;

    // comparison operators overload
    bool operator == (const Polynomial &another) const;
    bool operator != (const Polynomial &another) const;

    // binary operators overload
    Polynomial operator  + (const Polynomial &another) const;
    Polynomial operator  - (const Polynomial &another) const;
    Polynomial operator  * (const Polynomial &another) const;
    Polynomial operator  * (const Rational   &another) const;
    Polynomial operator  / (const Polynomial &another) const;
    Polynomial operator  % (const Polynomial &another) const;
    Polynomial operator << (Natural k)                 const;

    // assignment operators overload
    Polynomial &operator =   (const Polynomial &another); // copy assignment
    Polynomial &operator =   (Polynomial &&another);      // move assignment
    Polynomial &operator +=  (const Polynomial &another);
    Polynomial &operator -=  (const Polynomial &another);
    Polynomial &operator *=  (const Polynomial &another);
    Polynomial &operator *=  (const Rational   &another);
    Polynomial &operator /=  (const Polynomial &another);
    Polynomial &operator %=  (const Polynomial &another);
    Polynomial &operator <<= (Natural k);

    // visualization
    operator std::string() const;
    
private:
    std::map<Natural, Rational> _coeffs;
    void _clear_empty();
};

std::ostream& operator<<(std::ostream& stream, const Rational &value);



