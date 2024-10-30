#include "../include/algo.h"
#include <cstddef>

namespace algo
{
    std::vector<uint8_t> basic_add(std::vector<uint8_t> a, std::vector<uint8_t> b)
    {
        std::vector<uint8_t> result_vec;
        
        std::size_t maxlen = std::max(a.size(), b.size());
        uint8_t carry = 0;
        for(std::size_t i = 0; i < maxlen; ++i) {
            uint8_t digit_a = (i < a.size()) ? a[i] : 0;
            uint8_t digit_b = (i < b.size()) ? b[i] : 0;

            uint8_t digit_result = digit_a + digit_b + carry;
            carry = digit_result / 10;
            result_vec.emplace_back(digit_result % 10);
        }
        if(carry != 0)
            result_vec.emplace_back(carry);

        return result_vec;
    }

    std::vector<uint8_t> basic_sub(std::vector<uint8_t> a, std::vector<uint8_t> b)
    {
        std::vector<uint8_t> result_vec;

        uint8_t carry = 0;
        for(std::size_t i = 0; i < a.size(); ++i) {
            uint8_t digit_b = (i < b.size()) ? b[i] : 0;

            int8_t digit_result = a[i] - digit_b - carry;
            if(digit_result < 0) {
                carry = 1;
                digit_result += 10;
            }
            else
                carry = 0;
                
            result_vec.emplace_back(digit_result);
        }

        return result_vec;
    }
    
    std::vector<uint8_t> basic_mul(std::vector<uint8_t> a, uint8_t b)
    {
        std::vector<uint8_t> result_vec;
        
        uint8_t carry = 0;
        for(std::size_t i = 0; i < a.size(); ++i) {
            uint8_t digit_result = a[i] + b + carry;
            carry = digit_result / 10;
            result_vec.emplace_back(digit_result % 10);
        }

        while(carry != 0) {
            result_vec.emplace_back(carry % 10);
            carry /= 10;
        }

        return result_vec;
    }
}
