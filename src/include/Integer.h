#pragma once
#include <cstddef>
#include <string>
#include <vector>

class Integer
{
public:
    Integer();
    Integer(const std::string &value);

    // operators reloading
    Integer operator + (const Integer &another) const;
    Integer operator - (const Integer &another) const;
    Integer operator * (const Integer &another) const;
    Integer operator / (const Integer &another) const;
    Integer operator % (const Integer &another) const;
private:
    bool _negative = false;

    // This vector is little-endian
    std::vector<uint8_t> _digits;
};
