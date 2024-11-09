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
    explicit Polynomial(const std::vector<Rational> &values); // from Rational vector
    Polynomial(const Polynomial &another);                    // copy constructor
    Polynomial(Polynomial &&another);                         // move constructor

    // this function modifies the object
    void mul_by_rational(const Rational &value);
    void mul_by_xk(const Natural &k);

    bool is_zero()    const;
    bool is_integer() const;
    // most significant coefficient
    Rational   msc()  const;
    Natural    deg()  const;
    Polynomial gcd()  const;
    Polynomial derivative() const;

    // comparison operators overload
    bool operator <  (const Rational &another) const;
    bool operator >  (const Rational &another) const;
    bool operator == (const Rational &another) const;
    bool operator <= (const Rational &another) const;
    bool operator >= (const Rational &another) const;
    bool operator != (const Rational &another) const;

    // binary operators overload
    Rational operator + (const Rational &another) const;
    Rational operator - (const Rational &another) const;
    Rational operator * (const Rational &another) const;
    Rational operator / (const Rational &another) const;
    Rational operator % (const Rational &another) const;

    // assignment operators overload
    Rational &operator =  (const Rational &another); // copy assignment
    Rational &operator =  (Rational &&another);      // move assignment
    Rational &operator += (const Rational &another);
    Rational &operator -= (const Rational &another);
    Rational &operator *= (const Rational &another);
    Rational &operator /= (const Rational &another);

    // visualization
    operator std::string() const;
    
private:
  std::map<Natural, Rational> _coeffs;
};

std::ostream& operator<<(std::ostream& stream, const Rational &value);



