#pragma once
#include "Natural.h"
#include <string>

class Integer
{
public:
    Integer();                         // new 0
    Integer(int value);                // new from int
    Integer(const std::string &value); // new from string
    Integer(const char *value);        // new from char array
    Integer(const Integer &another);   // copy constructor
    Integer(Integer &&another);        // move constructor

    // comparison operators overload
    bool operator <  (const Integer &another) const;
    bool operator >  (const Integer &another) const;
    bool operator == (const Integer &another) const;
    bool operator <= (const Integer &another) const;
    bool operator >= (const Integer &another) const;

    // binary operators overload
    Integer operator + (const Integer &another) const;
    Integer operator - (const Integer &another) const;
    Integer operator * (const Integer &another) const;
    Integer operator / (const Integer &another) const;
    Integer operator % (const Integer &another) const;

    // shift operator overload
    Integer operator << (std::size_t k) const; // equal to *10^k

    // assignment operators overload
    Integer &operator =  (const Integer &another); // copy assignment
    Integer &operator =  (Integer &&another);      // move assignment
    Integer &operator += (const Integer &another);
    Integer &operator -= (const Integer &another);
    Integer &operator *= (const Integer &another);
    Integer &operator /= (const Integer &another);
    Integer &operator %= (const Integer &another);
    Integer &operator <<= (std::size_t k);

    // increment & decrement
    Integer &operator ++ ();
    Integer &operator -- ();
    Integer  operator ++ (int);
    Integer  operator -- (int);

    // visualization
    operator std::string() const;
    
private:
    Natural _nat;
    bool    _neg = false;

    // return -1 if a < b, 0 if a == b and 1 if a > b
    int _cmp(const Integer &a, const Integer &b) const;
};

std::ostream& operator<<(std::ostream& stream, const Integer &value);