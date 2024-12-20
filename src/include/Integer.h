#pragma once
#include "Natural.h"
#include <string>

class Integer
{
public:
    Integer();                                  // new 0
    explicit Integer(int value);                // new from int
    explicit Integer(const std::string &value); // new from string
    explicit Integer(const char *value);        // new from char array
    explicit Integer(const Natural &value);     // from Natural
    Integer(const Integer &another);            // copy constructor
    Integer(Integer &&another);                 // move constructor

    // this functions is the fastest way to do checks
    bool is_zero() const;
    bool is_neg()  const;

    Integer abs() const;

    // fast equivalent to mutiplication by -1
    void neg();

    // find GCD or MCL with another Integer
    Integer gcd(const Integer &another) const;
    Integer lcm(const Integer &another) const;

    // comparison operators overload
    bool operator <  (const Integer &another) const;
    bool operator >  (const Integer &another) const;
    bool operator == (const Integer &another) const;
    bool operator <= (const Integer &another) const;
    bool operator >= (const Integer &another) const;
    bool operator != (const Integer &another) const;

    // binary operators overload
    Integer operator + (const Integer &another) const;
    Integer operator - (const Integer &another) const;
    Integer operator * (const Integer &another) const;
    Integer operator / (const Integer &another) const;
    Integer operator % (const Integer &another) const;

    // shift operator overload
    Integer operator << (Natural k) const; // equal to *10^k

    // assignment operators overload
    Integer &operator =  (const Integer &another); // copy assignment
    Integer &operator =  (Integer &&another);      // move assignment
    Integer &operator += (const Integer &another);
    Integer &operator -= (const Integer &another);
    Integer &operator *= (const Integer &another);
    Integer &operator /= (const Integer &another);
    Integer &operator %= (const Integer &another);
    Integer &operator <<= (Natural k);

    // increment & decrement
    Integer &operator ++ ();
    Integer &operator -- ();
    Integer  operator ++ (int);
    Integer  operator -- (int);

    // visualization
    operator std::string() const;
    operator Natural()     const;
    
private:
    Natural _nat;
    bool    _neg = false;

    // return -1 if a < b, 0 if a == b and 1 if a > b
    int _cmp(const Integer &a, const Integer &b) const;
};

std::ostream& operator<<(std::ostream& stream, const Integer &value);
