// Author: Ivanov Artyom 3381

#ifndef RATIONAL_H
#define RATIONAL_H

#include <string>

#include "Natural.h"
#include "Integer.h"

class Rational
{
public:
    Rational();                                  // new 0
    explicit Rational(int value);                // new from int
    explicit Rational(const std::string &value); // new from string
    explicit Rational(const char *value);        // new from char array
    explicit Rational(const Natural &value);     // from Natural
    explicit Rational(const Integer &value);     // from Integer
    Rational(const Integer &numerator, const Natural &denominator);
    Rational(const Rational &another);           // copy constructor
    Rational(Rational &&another);                // move constructor

    // this function modifies the object
    void reduct();

    bool is_zero()     const;
    bool is_neg()      const;
    bool is_reducted() const;
    bool is_integer()  const;
    Integer get_numerator()   const;
    Natural get_denominator() const;
    Rational get_neg() const;
    Rational get_inversed() const;

    Rational abs() const;

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

    // assignment operators overload
    Rational &operator =  (const Rational &another); // copy assignment
    Rational &operator =  (Rational &&another);      // move assignment
    Rational &operator += (const Rational &another);
    Rational &operator -= (const Rational &another);
    Rational &operator *= (const Rational &another);
    Rational &operator /= (const Rational &another);

    // visualization
    operator std::string() const;
    operator Integer()     const;
    
private:
    Integer _num;
    Natural _denom;

    // this function modifies BOTH objects
    void _to_common_denom(Rational &another);
};

std::ostream& operator<<(std::ostream& stream, const Rational &value);

#endif // end of RATIONAL_H
