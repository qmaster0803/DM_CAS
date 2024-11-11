#include "../include/Parser.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "../include/Natural.h"
#include "../include/Integer.h"
#include "../include/Rational.h"
#include "../include/Polynomial.h"

std::string Parser::calc(default_vartype dflt, std::string input_str)
{
    auto parsed = _parse(dflt, input_str);
    auto pred_prior_is_zero = [](parsed_el a) { return a.el_priority == 0 && a.group_priority == 0; };

    while(parsed.size() != 1) {
        std::size_t max_index = 0;
        std::size_t max_el_pr = 0;
        std::size_t max_gr_pr = 0;

        for(std::size_t i = 0; i < parsed.size(); i++) {            
            if(max_gr_pr < parsed[i].group_priority) {
                max_index = i;
                max_gr_pr = parsed[i].group_priority;
                max_el_pr = parsed[i].el_priority;
            }
            else if(max_gr_pr == parsed[i].group_priority &&
                    max_el_pr <  parsed[i].el_priority) {
                max_index = i;
                max_gr_pr = parsed[i].group_priority;
                max_el_pr = parsed[i].el_priority;
            }
        }

        _calc_op(parsed, max_index);
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Applied op " << max_index << std::endl;
        for(auto i : parsed) {
            std::cout << "|" << i.s << "| type:" << static_cast<int>(i.type) << ", priority:("<< i.group_priority << ";" << i.el_priority << ")" << std::endl;
        }
        std::cout << "--------------------------------------------------" << std::endl;
    }

    return parsed[0].s;
}

std::vector<parsed_el> Parser::_parse(default_vartype dflt, std::string input_str)
{
    std::vector<parsed_el> parsed_input;
    std::map<std::size_t, std::size_t> el_priorities;
    std::size_t brace_level = 0;
    
    std::size_t prev_delim = input_str.length();
    std::size_t next_delim = prev_delim;
    std::cout << "In s " << input_str << std::endl;

    while(next_delim != input_str.npos) {
        next_delim = input_str.rfind(' ', next_delim-1);
        std::string part_with_braces = input_str.substr(next_delim + 1, prev_delim - next_delim - 1);
        prev_delim = next_delim;

        // Check for braces ')'
        bool braces_checked = false;
        for(auto it_a = part_with_braces.rbegin(), it_b = part_with_braces.rend(); it_a != it_b; it_a++) {
            if(*it_a == ')')
                brace_level++;
            else if(*it_a != ')' && !braces_checked)
                braces_checked = true;
            else if(*it_a == ')' && braces_checked)
                throw std::invalid_argument("Unable to parse - check braces");
        }

        // cut braces away temporarily
        std::string part = part_with_braces;
        part.erase(std::remove(part.begin(), part.end(), ')'), part.end());
        part.erase(std::remove(part.begin(), part.end(), '('), part.end());

        parsed_el new_element;
        new_element.s = part;
        bool ok = true;
        bool is_value = false;
        if(part == "++" || part == "--" || part == "'") {
            new_element.type = el_type::UNARY_OP;
            new_element.group_priority = 4;
        }
        else if(part == "*" || part == "/" || part == "%") {
            new_element.type = el_type::BINARY_OP;
            new_element.group_priority = 3;
        }
        else if(part == "+" || part == "-") {
            new_element.type = el_type::BINARY_OP;
            new_element.group_priority = 2;
        }
        else if(part == "<<") {
            new_element.type = el_type::BINARY_OP;
            new_element.group_priority = 1;
        }
        else if(part.find('[') != part.npos || part.find(']') != part.npos) {
            if(part == "[SUB_NDN_N]")
                new_element.type = el_type::FUNC_OP3;
            else if(part == "[cmp]" || part == "[gcd]" || part == "[lcm]" ||
                    part == "[COM_NN_D]" || part == "[ADD_NN_N]" || part == "[SUB_NN_N]" ||
                    part == "[MUL_ND_N]" || part == "[MUL_Nk_N]" || part == "[MUL_NN_N]" ||
                    part == "[DIV_NN_Dk]"|| part == "[DIV_NN_N]" || part == "[MOD_NN_N]" ||
                    part == "[GCF_NN_N]" || part == "[LCM_NN_N]" || part == "[ADD_ZZ_Z]" ||
                    part == "[SUB_ZZ_Z]" || part == "[MUL_ZZ_Z]" || part == "[DIV_ZZ_Z]" ||
                    part == "[MOD_ZZ_Z]" || part == "[ADD_QQ_Q]" || part == "[SUB_QQ_Q]" ||
                    part == "[MUL_QQ_Q]" || part == "[DIV_QQ_Q]" || part == "[ADD_PP_P]" ||
                    part == "[SUB_PP_P]" || part == "[MUL_PQ_P]" || part == "[MUL_Pxk_P]"||
                    part == "[MUL_PP_P]" || part == "[DIV_PP_P]" || part == "[MOD_PP_P]" ||
                    part == "[GCF_PP_P]")
                new_element.type = el_type::FUNC_OP2;
            else if(part == "[is_zero]" || part == "[abs]" || part == "[is_pos]" ||
                    part == "[neg]"     || part == "[Nat]" || part == "[Int]"    ||
                    part == "[Rat]"     || part == "[Pol]" || part == "[is_int]" ||
                    part == "[msc]"     || part == "[deg]" || part == "[fac]"    ||
                    part == "[simple_roots]" ||
                    part == "[NZER_N_B]" || part == "[ADD_1N_N]" || part == "[ABS_Z_N]"   ||
                    part == "[POZ_Z_D]"  || part == "[MUL_ZM_Z]" || part == "[TRANS_N_Z]" ||
                    part == "[TRANS_Z_N]"|| part == "[RED_Q_Q]"  || part == "[INT_Q_B]"   ||
                    part == "[TRANS_Z_Q]"|| part == "[TRANS_Q_Z]"|| part == "[LED_P_Q]"   ||
                    part == "[DEG_P_N]"  || part == "[FAC_P_Q]"  || part == "[DER_P_P]"   ||
                    part == "[NMR_P_P]")
                new_element.type = el_type::FUNC_OP1;
            else
                ok = false;
            new_element.group_priority = 4;
        }
        else {
            is_value = true;
            try {
                char last_c = part[part.length() - 1];
                if(last_c == 'n') {
                    Natural test(part);
                    new_element.type = el_type::VALUE_NATURAL;
                }
                else if(last_c == 'i') {
                    Integer test(part);
                    new_element.type = el_type::VALUE_NATURAL;
                }
                else if(last_c == 'r') {
                    Rational test(part);
                    new_element.type = el_type::VALUE_RATIONAL;
                }
                else if(last_c == 'p') {
                    Polynomial test(part);
                    new_element.type = el_type::VALUE_POLYNOMIAL;
                }
                else if(dflt == default_vartype::VARTYPE_NATURAL) {
                    Natural test(part);
                    new_element.type = el_type::VALUE_NATURAL;
                }
                else if(dflt == default_vartype::VARTYPE_INTEGER) {
                    Integer test(part);
                    new_element.type = el_type::VALUE_NATURAL;
                }
                else if(dflt == default_vartype::VARTYPE_RATIONAL) {
                    Rational test(part);
                    new_element.type = el_type::VALUE_RATIONAL;
                }
                else {
                    Polynomial test(part);
                    new_element.type = el_type::VALUE_POLYNOMIAL;
                }
            }
            catch (std::invalid_argument e) {
                throw std::invalid_argument("Cannot parse \"" + part + "\": " + static_cast<std::string>(e.what()));
            }
        }

        if(!ok) {
            throw std::invalid_argument("Cannot parse \"" + part + "\": unknown value");
        }

        new_element.group_priority += (10 * brace_level);

        if(!is_value) {
            // set group priority
            if(el_priorities.count(new_element.group_priority) == 1) {
                el_priorities[new_element.group_priority]++;
                new_element.el_priority = el_priorities[new_element.group_priority];
            }
            else {
                new_element.el_priority = 0;
                el_priorities[new_element.group_priority] = 0;
            }
        }
        else {
            new_element.group_priority = 0;
            new_element.el_priority = 0;
        }

        parsed_input.insert(parsed_input.begin(), std::move(new_element));
        
        // Check for braces '('
        braces_checked = false;
        for(auto it_a = part_with_braces.begin(), it_b = part_with_braces.end(); it_a != it_b; it_a++) {
            if(*it_a == '(') {
                if(brace_level == 0)
                    throw std::invalid_argument("Unable to parse - check braces");
                brace_level--;
            }
            else if(*it_a != '(' && !braces_checked)
                braces_checked = true;
            else if(*it_a == '(' && braces_checked)
                throw std::invalid_argument("Unable to parse - check braces");
        }
    }

    if(brace_level != 0)
        throw std::invalid_argument("Unable to parse - check braces");

    return parsed_input;
}

void Parser::_calc_op(std::vector<parsed_el> &el_vec, std::size_t index)
{
    if(el_vec[index].type == el_type::BINARY_OP) {
        if(index == 0 || (index + 1) >= el_vec.size())
            throw std::invalid_argument("Unable to calculate - check operators");
        
        auto a = el_vec[index-1], b = el_vec[index+1];
        std::cout << "Operation: " << a.s << " " << el_vec[index].s << " " << b.s << std::endl;
        std::cout << "Result: ";
        std::string result;
        std::cin >> result;
        el_vec.erase(el_vec.begin() + index + 1);
        el_vec[index].s = result;
        el_vec[index].el_priority = 0;
        el_vec[index].group_priority = 0;
        el_vec[index].type = a.type;
        el_vec.erase(el_vec.begin() + index - 1);
    }
    else if(el_vec[index].type == el_type::UNARY_OP) {
        if(index == 0)
            throw std::invalid_argument("Unable to calculate - check operators");
        
        auto a = el_vec[index-1];
        std::cout << "Operation: " << a.s << " " << el_vec[index].s << std::endl;
        std::cout << "Result: ";
        std::string result;
        std::cin >> result;
        el_vec[index].s = result;
        el_vec[index].el_priority = 0;
        el_vec[index].group_priority = 0;
        el_vec[index].type = a.type;
        el_vec.erase(el_vec.begin() + index - 1);
    }
    else if(el_vec[index].type == el_type::FUNC_OP1) {
        if((index + 1) >= el_vec.size())
            throw std::invalid_argument("Unable to calculate - check operators");
        
        auto a = el_vec[index+1];
        std::cout << "Operation: " << a.s << " " << el_vec[index].s << std::endl;
        std::cout << "Result: ";
        std::string result;
        std::cin >> result;
        el_vec[index].s = result;
        el_vec[index].el_priority = 0;
        el_vec[index].group_priority = 0;
        el_vec[index].type = a.type;
        el_vec.erase(el_vec.begin() + index + 1);
    }
    else if(el_vec[index].type == el_type::FUNC_OP2) {
        if((index + 2) >= el_vec.size())
            throw std::invalid_argument("Unable to calculate - check operators");
        
        auto a = el_vec[index+1], b = el_vec[index+2];
        std::cout << "Operation: " << a.s << " " << el_vec[index].s << " " << b.s << std::endl;
        std::cout << "Result: ";
        std::string result;
        std::cin >> result;
        el_vec[index].s = result;
        el_vec[index].el_priority = 0;
        el_vec[index].group_priority = 0;
        el_vec[index].type = a.type;
        el_vec.erase(el_vec.begin() + index + 2);
        el_vec.erase(el_vec.begin() + index + 1);
    }
    else if(el_vec[index].type == el_type::FUNC_OP3) {
        if((index + 3) >= el_vec.size())
            throw std::invalid_argument("Unable to calculate - check operators");
        
        auto a = el_vec[index+1], b = el_vec[index+2], c = el_vec[index+3];
        std::cout << "Operation: " << a.s << " " << el_vec[index].s << " " << b.s << std::endl;
        std::cout << "Result: ";
        std::string result;
        std::cin >> result;
        el_vec[index].s = result;
        el_vec[index].el_priority = 0;
        el_vec[index].group_priority = 0;
        el_vec[index].type = a.type;
        el_vec.erase(el_vec.begin() + index + 2);
        el_vec.erase(el_vec.begin() + index + 1);
    }
}
