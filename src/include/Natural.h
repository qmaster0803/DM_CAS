#pragma once
#include "algo.h"
#include <cstddef>
#include <string>
#include <vector>

class Natural
{
public:
    Natural();                         // new 0
    Natural(int value);                // new from int
    Natural(const std::string &value); // new from string
    Natural(const char *value);        // new from char array
    Natural(const Natural &another);   // copy constructor
    Natural(Natural &&another);        // move constructor

    // this functions alter the class object itself
    void mul_by_digit(uint8_t digit);

    // comparison operators overload
    bool operator <  (const Natural &another) const;
    bool operator >  (const Natural &another) const;
    bool operator == (const Natural &another) const;
    bool operator <= (const Natural &another) const;
    bool operator >= (const Natural &another) const;
    bool operator != (const Natural &another) const;

    // binary operators overload
    Natural operator + (const Natural &another) const;
    Natural operator - (const Natural &another) const;
    Natural operator * (const Natural &another) const;
    Natural operator / (const Natural &another) const;
    Natural operator % (const Natural &another) const;

    // shift operator overload
    Natural operator << (std::size_t k) const; // equal to *10^k

    // assignment operators overload
    Natural &operator =  (const Natural &another); // copy assignment
    Natural &operator =  (Natural &&another);      // move assignment
    Natural &operator += (const Natural &another);
    Natural &operator -= (const Natural &another);
    Natural &operator *= (const Natural &another);
    Natural &operator /= (const Natural &another);
    Natural &operator %= (const Natural &another);
    Natural &operator <<= (std::size_t k);

    // increment & decrement
    Natural &operator ++ ();
    Natural &operator -- ();
    Natural  operator ++ (int);
    Natural  operator -- (int);

    // visualization
    operator std::string() const;
    
private:
    // constructor to create new object directly from the digits
    // array, mostly used in operators
    Natural(std::vector<uint8_t> &digits);
    
    // This vector is little-endian
    std::vector<uint8_t> _digits;
};

std::ostream& operator<<(std::ostream& stream, const Natural &value);
