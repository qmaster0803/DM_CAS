// Author: Ivanov Artyom 3381 except 1 function

#include "../include/algo.h"
#include <cstddef>
#include <algorithm>

namespace algo
{
    void truncate_leading_zeros(std::vector<uint8_t> &vec)
    {
        // truncate leading zeros
        auto last_digit = vec.end() - 1;
        while(*last_digit == 0 && vec.size() > 1)
            last_digit = vec.erase(last_digit) - 1;
    }
    
    std::vector<uint8_t> basic_add(const std::vector<uint8_t> &a, const std::vector<uint8_t> &b)
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

    std::vector<uint8_t> basic_sub(const std::vector<uint8_t> &a, const std::vector<uint8_t> &b)
    {
        std::vector<uint8_t> result_vec;

        uint8_t carry = 0;
        for(std::size_t i = 0; i < a.size(); ++i) {
            uint8_t digit_b = (i < b.size()) ? b[i] : 0;

            int8_t digit_result = a[i] - digit_b - carry;
            // check for borrow
            if(digit_result < 0) {
                carry = 1;
                digit_result += 10;
            }
            else
                carry = 0;
                
            result_vec.emplace_back(digit_result);
        }

        truncate_leading_zeros(result_vec);
        return result_vec;
    }
    
    std::vector<uint8_t> basic_mul(const std::vector<uint8_t> &a, uint8_t b)
    {
        // if a == 0 or b == 0 -> return 0
        std::vector<uint8_t> result_vec;
        if(b == 0 || (a.size() == 1 && a[0] == 0)) {
            result_vec.emplace_back(0);
            return result_vec;
        }

        // basic case
        uint8_t carry = 0;
        for(std::size_t i = 0; i < a.size(); ++i) {
            uint8_t digit_result = a[i] * b + carry;
            carry = digit_result / 10;
            result_vec.emplace_back(digit_result % 10);
        }

        if(carry != 0)
            result_vec.emplace_back(carry % 10);

        return result_vec;
    }

    // Author: Komarov Daniil 3381
    std::vector<uint8_t> basic_div(const std::vector<uint8_t> &a, const std::vector<uint8_t> &b,
                                   std::optional<std::reference_wrapper<std::vector<uint8_t>>> remainder,
                                   bool first_digit_only)
    {
        // using the long division algorithm
        std::vector<uint8_t> result;
        auto it = a.rbegin();
    
        // select first part (from most significant side get at least another.len digits to match div_part >= another)
        std::vector<uint8_t> div_part = {*(it++)};
        while(algo::basic_cmp(div_part, b) == -1)
            div_part.insert(div_part.begin(), *(it++));

        // Enter the main loop
        while(1) {
            // Divide directly by subtracting another from div_part
            uint8_t result_digit = 0;
            while(algo::basic_cmp(div_part, b) != -1) {
                div_part = algo::basic_sub(div_part, b);
                result_digit++;
            }
            // Save result digit (first digit is MS), but let's just reverse the vector
            // before returning instead of moving values in the insert()
            result.emplace_back(result_digit);

            // stop execution if in first_digit_only mode
            if (first_digit_only)
                return result;
            
            // Exit loop if end of a reached
            if(it == a.rend())
                break;
            
            // Transfer next digit of divident to div_part
            div_part.insert(div_part.begin(), *(it++));
            truncate_leading_zeros(div_part);
        }

        // Get remainder        
        if(remainder.has_value())
            (*remainder).get() = std::move(div_part);
        
        std::reverse(result.begin(), result.end());
        return result;
    }
    
    int basic_cmp(const std::vector<uint8_t> &a, const std::vector<uint8_t> &b)
    {
        if(a.size() != b.size())
            return (a.size() > b.size()) ? 1 : -1;

        auto it_a = a.rbegin();
        auto it_b = b.rbegin();
        while(it_a != a.rend()) {
            if(*it_a != *it_b)
                return (*it_a > *it_b) ? 1 : -1;

            it_a++;
            it_b++;
        }

        return 0;
    }
}
