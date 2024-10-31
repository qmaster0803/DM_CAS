#pragma once
#include <functional>
#include <optional>
#include <stdint.h>
#include <vector>

namespace algo
{
    void truncate_leading_zeros(std::vector<uint8_t> &vec);
    std::vector<uint8_t> basic_add(const std::vector<uint8_t> &a, const std::vector<uint8_t> &b);
    std::vector<uint8_t> basic_sub(const std::vector<uint8_t> &a, const std::vector<uint8_t> &b);
    std::vector<uint8_t> basic_mul(const std::vector<uint8_t> &a, uint8_t b);
    std::vector<uint8_t> basic_div(const std::vector<uint8_t> &a, const std::vector<uint8_t> &b,
                                   std::optional<std::reference_wrapper<std::vector<uint8_t>>> remainder = std::nullopt);
    int basic_cmp(const std::vector<uint8_t> &a, const std::vector<uint8_t> &b);
}
