#pragma once
#include <stdint.h>
#include <vector>

namespace algo
{
    std::vector<uint8_t> basic_add(std::vector<uint8_t> a, std::vector<uint8_t> b);
    std::vector<uint8_t> basic_sub(std::vector<uint8_t> a, std::vector<uint8_t> b);
    std::vector<uint8_t> basic_mul(std::vector<uint8_t> a, uint8_t b);
}
