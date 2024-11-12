#pragma once
#include <cstddef>
#include <string>
#include <vector>

/*
 * a ++      - 4 - nat, int
 * a --      - 4 - nat, int
 * a '       - 4 - pol
 *
 * a + b     - 2 - nat, int, rat, pol
 * a - b     - 2 - nat, int, rat, pol
 * a * b     - 3 - nat, int, rat, pol, [pol * rat]
 * a << b    - 1 - nat, int, pol
 * a / b     - 3 - nat, int, rat, pol
 * a % b     - 3 - nat, int, pol
 *
 * [is_zero] a - 4 - nat, int, rat, pol
 * [abs] a     - 4 - int, rat
 * [is_pos] a  - 4 - int, rat
 * [neg] a     - 4 - int, rat
 * [Nat] a     - 4 - int, rat
 * [Int] a     - 4 - nat, rat
 * [Rat] a     - 4 - nat, int
 * [Pol] a     - 4 - int, nat, rat
 * [is_int] a  - 4 - rat, pol
 * [msc] a     - 4 - pol
 * [deg] a     - 4 - pol
 * [fac] a     - 4 - pol
 * [simple_roots] a - 4 - pol
 *
 * [cmp] a,b   - 4 - 2*nat, 2*int, 2*rat
 * [gcd] a,b   - 4 - nat, int, pol
 * [lcm] a,b   - 4 - nat, int
 *
 * 123 - deftype
 * 123n - natural
 * 123i - integer
 * 123r - rational
 * 123p - polynomial
 * {3^1;4^5}p - to define polynomial in the natural mode, etc.
 */

enum class el_type {
    VALUE_NATURAL,
    VALUE_INTEGER,
    VALUE_RATIONAL,
    VALUE_POLYNOMIAL,
    BINARY_OP,
    UNARY_OP,
    FUNC_OP1,
    FUNC_OP2,
    FUNC_OP3
};

enum class default_vartype {
    VARTYPE_NATURAL    = 0,
    VARTYPE_INTEGER    = 1,
    VARTYPE_RATIONAL   = 2,
    VARTYPE_POLYNOMIAL = 3
};

struct parsed_el {
    el_type type;
    std::string s;
    std::size_t group_priority;
    std::size_t el_priority;
};

class Parser {
public:
    std::string calc(default_vartype dflt, std::string input_str);
private:
    std::vector<parsed_el> _parse(default_vartype dflt, std::string input_str);
    void _calc_op(std::vector<parsed_el> &el_vec, std::size_t index);
};
