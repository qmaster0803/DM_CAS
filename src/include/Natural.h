#pragma once
#include "algo.h"
#include <cstddef>
#include <string>
#include <vector>

class Natural
{
public:
    Natural();
    Natural(const std::string &value);
    Natural(const Natural &another);

    void mul_by_digit(uint8_t digit);

    // operators reloading
    Natural operator << (std::size_t k) const; // equal to *10^k
    Natural operator + (const Natural &another) const;
    Natural &operator += (const Natural &another);
    Natural operator - (const Natural &another) const;
    Natural operator * (const Natural &another) const;
    Natural operator / (const Natural &another) const;
    Natural operator % (const Natural &another) const;
private:
    Natural(std::vector<uint8_t> &digits);
    // This vector is little-endian
    std::vector<uint8_t> _digits;
};
