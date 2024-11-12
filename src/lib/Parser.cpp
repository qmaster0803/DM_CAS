#include "../include/Parser.h"
#include <algorithm>
#include <stdexcept>
#include "../include/Natural.h"
#include "../include/Integer.h"
#include "../include/Rational.h"
#include "../include/Polynomial.h"
#include "../include/backend.h"

std::string Parser::calc(default_vartype dflt, std::string input_str)
{
    auto parsed = _parse(dflt, input_str);

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

        if(max_el_pr == 0 && max_gr_pr == 0)
            throw std::invalid_argument("Unable to parse - too much operands");
        _calc_op(parsed, max_index);
    }

    std::string result = parsed[0].s;
    switch(parsed[0].type) {
        case el_type::VALUE_NATURAL:
            result += "n";
            break;
        case el_type::VALUE_INTEGER:
            result += "i";
            break;
        case el_type::VALUE_RATIONAL:
            result += "r";
            break;
        case el_type::VALUE_POLYNOMIAL:
            result += "p";
            break;
        default:
            break;
    }

    return result;
}

std::vector<parsed_el> Parser::_parse(default_vartype dflt, std::string input_str)
{
    std::vector<parsed_el> parsed_input;
    std::map<std::size_t, std::size_t> el_priorities;
    std::size_t brace_level = 0;
    
    std::size_t prev_delim = input_str.length();
    std::size_t next_delim = prev_delim;

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
                    part == "[SGN_Z_D]"  || part == "[MUL_ZM_Z]" || part == "[TRANS_N_Z]" ||
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
                    Natural test(part.substr(0, part.length() - 1));
                    new_element.s = part.substr(0, part.length() - 1);
                    new_element.type = el_type::VALUE_NATURAL;
                }
                else if(last_c == 'i') {
                    Integer test(part.substr(0, part.length() - 1));
                    new_element.s = part.substr(0, part.length() - 1);
                    new_element.type = el_type::VALUE_INTEGER;
                }
                else if(last_c == 'r') {
                    Rational test(part.substr(0, part.length() - 1));
                    new_element.s = part.substr(0, part.length() - 1);
                    new_element.type = el_type::VALUE_RATIONAL;
                }
                else if(last_c == 'p') {
                    Polynomial test(part.substr(0, part.length() - 1));
                    new_element.s = part.substr(0, part.length() - 1);
                    new_element.type = el_type::VALUE_POLYNOMIAL;
                }
                else if(dflt == default_vartype::VARTYPE_NATURAL) {
                    Natural test(part);
                    new_element.type = el_type::VALUE_NATURAL;
                }
                else if(dflt == default_vartype::VARTYPE_INTEGER) {
                    Integer test(part);
                    new_element.type = el_type::VALUE_INTEGER;
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
        
        auto a = el_vec[index-1], b = el_vec[index+1], op = el_vec[index];
        std::string result;

        if(op.s == "+") {
            if(a.type != b.type)
                throw std::invalid_argument("Unable to calculate - wrong operand types");

            if(a.type == el_type::VALUE_NATURAL)
                result = static_cast<std::string>(backend::ADD_NN_N(Natural(a.s), Natural(b.s)));
            else if(a.type == el_type::VALUE_INTEGER)
                result = static_cast<std::string>(backend::ADD_ZZ_Z(Integer(a.s), Integer(b.s)));
            else if(a.type == el_type::VALUE_RATIONAL)
                result = static_cast<std::string>(backend::ADD_QQ_Q(Rational(a.s), Rational(b.s)));
            else if(a.type == el_type::VALUE_POLYNOMIAL)
                result = static_cast<std::string>(backend::ADD_PP_P(Polynomial(a.s), Polynomial(b.s)));
        }
        else if(op.s == "-") {
            if(a.type != b.type)
                throw std::invalid_argument("Unable to calculate - wrong operand types");

            if(a.type == el_type::VALUE_NATURAL)
                result = static_cast<std::string>(backend::SUB_NN_N(Natural(a.s), Natural(b.s)));
            else if(a.type == el_type::VALUE_INTEGER)
                result = static_cast<std::string>(backend::SUB_ZZ_Z(Integer(a.s), Integer(b.s)));
            else if(a.type == el_type::VALUE_RATIONAL)
                result = static_cast<std::string>(backend::SUB_QQ_Q(Rational(a.s), Rational(b.s)));
            else if(a.type == el_type::VALUE_POLYNOMIAL)
                result = static_cast<std::string>(backend::SUB_PP_P(Polynomial(a.s), Polynomial(b.s)));
        }
        else if(op.s == "*") {
            if(a.type != b.type && !(a.type == el_type::VALUE_POLYNOMIAL && b.type == el_type::VALUE_RATIONAL))
                throw std::invalid_argument("Unable to calculate - wrong operand types");

            if(a.type == el_type::VALUE_NATURAL)
                result = static_cast<std::string>(backend::MUL_NN_N(Natural(a.s), Natural(b.s)));
            else if(a.type == el_type::VALUE_INTEGER)
                result = static_cast<std::string>(backend::MUL_ZZ_Z(Integer(a.s), Integer(b.s)));
            else if(a.type == el_type::VALUE_RATIONAL)
                result = static_cast<std::string>(backend::MUL_QQ_Q(Rational(a.s), Rational(b.s)));
            else if(a.type == el_type::VALUE_POLYNOMIAL && b.type == el_type::VALUE_POLYNOMIAL)
                result = static_cast<std::string>(backend::MUL_PP_P(Polynomial(a.s), Polynomial(b.s)));
            else if(a.type == el_type::VALUE_POLYNOMIAL && b.type == el_type::VALUE_RATIONAL)
                result = static_cast<std::string>(backend::MUL_PQ_P(Polynomial(a.s), Rational(b.s)));
        }
        else if(op.s == "/") {
            if(a.type != b.type)
                throw std::invalid_argument("Unable to calculate - wrong operand types");

            if(a.type == el_type::VALUE_NATURAL)
                result = static_cast<std::string>(backend::DIV_NN_N(Natural(a.s), Natural(b.s)));
            else if(a.type == el_type::VALUE_INTEGER)
                result = static_cast<std::string>(backend::DIV_ZZ_Z(Integer(a.s), Integer(b.s)));
            else if(a.type == el_type::VALUE_RATIONAL)
                result = static_cast<std::string>(backend::DIV_QQ_Q(Rational(a.s), Rational(b.s)));
            else if(a.type == el_type::VALUE_POLYNOMIAL)
                result = static_cast<std::string>(backend::DIV_PP_P(Polynomial(a.s), Polynomial(b.s)));
        }
        else if(op.s == "<<") {
            if(a.type == el_type::VALUE_RATIONAL || b.type != el_type::VALUE_NATURAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");

            if(a.type == el_type::VALUE_NATURAL)
                result = static_cast<std::string>(backend::MUL_Nk_N(Natural(a.s), Natural(b.s)));
            else if(a.type == el_type::VALUE_INTEGER)
                result = static_cast<std::string>(backend::MUL_Zk_Z(Integer(a.s), Natural(b.s)));
            else if(a.type == el_type::VALUE_POLYNOMIAL)
                result = static_cast<std::string>(backend::MUL_Pxk_P(Polynomial(a.s), Natural(b.s)));
        }
        else if(op.s == "%") {
            if(a.type != b.type || a.type == el_type::VALUE_RATIONAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");

            if(a.type == el_type::VALUE_NATURAL)
                result = static_cast<std::string>(backend::MOD_NN_N(Natural(a.s), Natural(b.s)));
            else if(a.type == el_type::VALUE_INTEGER)
                result = static_cast<std::string>(backend::MOD_ZZ_Z(Integer(a.s), Integer(b.s)));
            else if(a.type == el_type::VALUE_POLYNOMIAL)
                result = static_cast<std::string>(backend::MOD_PP_P(Polynomial(a.s), Polynomial(b.s)));
        }
        
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
        
        auto a = el_vec[index-1], op = el_vec[index];
        std::string result;

        if(op.s == "++") {

            if(a.type == el_type::VALUE_NATURAL)
                result = static_cast<std::string>(backend::ADD_1N_N(Natural(a.s)));
            else if(a.type == el_type::VALUE_INTEGER)
                result = static_cast<std::string>(backend::ADD_1Z_Z(Integer(a.s)));
            else
                throw std::invalid_argument("Unable to calculate - wrong operand types");
        }
        else if(op.s == "--") {

            if(a.type == el_type::VALUE_NATURAL)
                result = static_cast<std::string>(backend::SUB_1N_N(Natural(a.s)));
            else if(a.type == el_type::VALUE_INTEGER)
                result = static_cast<std::string>(backend::SUB_1Z_Z(Integer(a.s)));
            else
                throw std::invalid_argument("Unable to calculate - wrong operand types");
        }
        else if(op.s == "'") {

            if(a.type == el_type::VALUE_POLYNOMIAL)
                result = static_cast<std::string>(backend::DER_P_P(Polynomial(a.s)));
            else
                throw std::invalid_argument("Unable to calculate - wrong operand types");
        }
        
        el_vec[index].s = result;
        el_vec[index].el_priority = 0;
        el_vec[index].group_priority = 0;
        el_vec[index].type = a.type;
        el_vec.erase(el_vec.begin() + index - 1);
    }
    else if(el_vec[index].type == el_type::FUNC_OP1) {
        if((index + 1) >= el_vec.size())
            throw std::invalid_argument("Unable to calculate - check operators");
        
        auto a = el_vec[index+1], op = el_vec[index];
        std::string result;
        
        el_vec[index].el_priority = 0;
        el_vec[index].group_priority = 0;
        el_vec[index].type = a.type;

        if(op.s == "[NZER_N_B]") {
            if(a.type != el_type::VALUE_NATURAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = std::to_string(static_cast<int>(backend::NZER_N_B(Natural(a.s))));
        }
        else if(op.s == "[ADD_1N_N]") {
            if(a.type != el_type::VALUE_NATURAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::ADD_1N_N(Natural(a.s)));
        }
        else if(op.s == "[SUB_1N_N]") {
            if(a.type != el_type::VALUE_NATURAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::SUB_1N_N(Natural(a.s)));
        }
        else if(op.s == "[ABS_Z_Z]") {
            if(a.type != el_type::VALUE_INTEGER)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::ABS_Z_Z(Integer(a.s)));
        }
        else if(op.s == "[SGN_Z_D]") {
            if(a.type != el_type::VALUE_INTEGER)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = std::to_string(backend::SGN_Z_D(Integer(a.s)));
        }
        else if(op.s == "[TRANS_N_Z]") {
            if(a.type != el_type::VALUE_NATURAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::TRANS_N_Z(Natural(a.s)));
            el_vec[index].type = el_type::VALUE_INTEGER;
        }
        else if(op.s == "[TRANS_Z_N]") {
            if(a.type != el_type::VALUE_INTEGER)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::TRANS_Z_N(Integer(a.s)));
            el_vec[index].type = el_type::VALUE_NATURAL;
        }
        else if(op.s == "[ADD_1Z_Z]") {
            if(a.type != el_type::VALUE_INTEGER)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::ADD_1Z_Z(Integer(a.s)));
        }
        else if(op.s == "[SUB_1Z_Z]") {
            if(a.type != el_type::VALUE_INTEGER)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::SUB_1Z_Z(Integer(a.s)));
        }
        else if(op.s == "[RED_Q_Q]") {
            if(a.type != el_type::VALUE_RATIONAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::RED_Q_Q(Rational(a.s)));
        }
        else if(op.s == "[INT_Q_B]") {
            if(a.type != el_type::VALUE_RATIONAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = std::to_string(static_cast<int>(backend::INT_Q_B(Rational(a.s))));
        }
        else if(op.s == "[TRANS_Z_Q]") {
            if(a.type != el_type::VALUE_INTEGER)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::TRANS_Z_Q(Integer(a.s)));
            el_vec[index].type = el_type::VALUE_RATIONAL;
        }
        else if(op.s == "[TRANS_Q_Z]") {
            if(a.type != el_type::VALUE_RATIONAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::TRANS_Q_Z(Rational(a.s)));
            el_vec[index].type = el_type::VALUE_INTEGER;
        }
        else if(op.s == "[LED_P_Q]" || op.s == "[msc]") {
            if(a.type != el_type::VALUE_POLYNOMIAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::LED_P_Q(Polynomial(a.s)));
            el_vec[index].type = el_type::VALUE_RATIONAL;
        }
        else if(op.s == "[DEG_P_N]" || op.s == "[deg]") {
            if(a.type != el_type::VALUE_POLYNOMIAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::DEG_P_N(Polynomial(a.s)));
            el_vec[index].type = el_type::VALUE_NATURAL;
        }
        else if(op.s == "[FAC_P_Q]" || op.s == "[fac]") {
            if(a.type != el_type::VALUE_POLYNOMIAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::FAC_P_Q(Polynomial(a.s)));
            el_vec[index].type = el_type::VALUE_RATIONAL;
        }
        else if(op.s == "[DER_P_P]") {
            if(a.type != el_type::VALUE_POLYNOMIAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::DER_P_P(Polynomial(a.s)));
        }
        else if(op.s == "[NMR_P_P]" || op.s == "[simple_roots]") {
            if(a.type != el_type::VALUE_POLYNOMIAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::NMR_P_P(Polynomial(a.s)));
        }
        else if(op.s == "[MUL_ZM_Z]") {
            if(a.type != el_type::VALUE_INTEGER)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::MUL_ZM_Z(Integer(a.s)));
        }
        else if(op.s == "[is_zero]") {
            if(a.type == el_type::VALUE_NATURAL)
                result = std::to_string(static_cast<int>(backend::NZER_N_B(Natural(a.s))));
            else if(a.type == el_type::VALUE_INTEGER)
                result = std::to_string(static_cast<int>(backend::NZER_Z_B(Integer(a.s))));
            else if(a.type == el_type::VALUE_RATIONAL)
                result = std::to_string(static_cast<int>(backend::NZER_Q_B(Rational(a.s))));
            else if(a.type == el_type::VALUE_POLYNOMIAL)
                result = std::to_string(static_cast<int>(backend::NZER_P_B(Polynomial(a.s))));
            el_vec[index].type = el_type::VALUE_NATURAL;
        }
        else if(op.s == "[abs]") {
            if(a.type != el_type::VALUE_INTEGER && a.type != el_type::VALUE_RATIONAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");

            if(a.type == el_type::VALUE_INTEGER)
                result = static_cast<std::string>(backend::ABS_Z_Z(Integer(a.s)));
            else if(a.type == el_type::VALUE_RATIONAL)
                result = static_cast<std::string>(backend::ABS_Q_Q(Rational(a.s)));
        }
        else if(op.s == "[is_pos]") {
            if(a.type != el_type::VALUE_INTEGER && a.type != el_type::VALUE_RATIONAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");

            if(a.type == el_type::VALUE_INTEGER)
                result = std::to_string(backend::SGN_Z_D(Integer(a.s)));
            else if(a.type == el_type::VALUE_RATIONAL)
                result = std::to_string(backend::SGN_Q_D(Rational(a.s)));
            el_vec[index].type = el_type::VALUE_NATURAL;
        }
        else if(op.s == "[neg]") {
            if(a.type != el_type::VALUE_INTEGER && a.type != el_type::VALUE_RATIONAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");

            if(a.type == el_type::VALUE_INTEGER)
                result = static_cast<std::string>(backend::MUL_ZM_Z(Integer(a.s)));
            else if(a.type == el_type::VALUE_RATIONAL)
                result = static_cast<std::string>(backend::MUL_QM_Q(Rational(a.s)));
        }
        else if(op.s == "[Nat]") {
            if(a.type != el_type::VALUE_INTEGER && a.type != el_type::VALUE_RATIONAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");

            if(a.type == el_type::VALUE_INTEGER)
                result = static_cast<std::string>(backend::TRANS_Z_N(Integer(a.s)));
            else if(a.type == el_type::VALUE_RATIONAL)
                result = static_cast<std::string>(backend::TRANS_Q_N(Rational(a.s)));
            el_vec[index].type = el_type::VALUE_NATURAL;
        }
        else if(op.s == "[Int]") {
            if(a.type != el_type::VALUE_NATURAL && a.type != el_type::VALUE_RATIONAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");

            if(a.type == el_type::VALUE_NATURAL)
                result = static_cast<std::string>(backend::TRANS_N_Z(Natural(a.s)));
            else if(a.type == el_type::VALUE_RATIONAL)
                result = static_cast<std::string>(backend::TRANS_Q_Z(Rational(a.s)));
            el_vec[index].type = el_type::VALUE_INTEGER;
        }
        else if(op.s == "[Rat]") {
            if(a.type != el_type::VALUE_NATURAL && a.type != el_type::VALUE_INTEGER)
                throw std::invalid_argument("Unable to calculate - wrong operand types");

            if(a.type == el_type::VALUE_NATURAL)
                result = static_cast<std::string>(backend::TRANS_N_Q(Natural(a.s)));
            else if(a.type == el_type::VALUE_INTEGER)
                result = static_cast<std::string>(backend::TRANS_Z_Q(Rational(a.s)));
            el_vec[index].type = el_type::VALUE_RATIONAL;
        }
        else if(op.s == "[Pol]") {
            if(a.type == el_type::VALUE_POLYNOMIAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");

            if(a.type == el_type::VALUE_NATURAL)
                result = static_cast<std::string>(backend::TRANS_N_P(Natural(a.s)));
            else if(a.type == el_type::VALUE_INTEGER)
                result = static_cast<std::string>(backend::TRANS_Z_P(Integer(a.s)));
            else if(a.type == el_type::VALUE_RATIONAL)
                result = static_cast<std::string>(backend::TRANS_Q_P(Rational(a.s)));
            el_vec[index].type = el_type::VALUE_POLYNOMIAL;
        }
        else if(op.s == "[is_int]") {
            if(a.type != el_type::VALUE_RATIONAL && a.type != el_type::VALUE_POLYNOMIAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");

            if(a.type == el_type::VALUE_RATIONAL)
                result = std::to_string(static_cast<int>(backend::INT_Q_B(Rational(a.s))));
            else if(a.type == el_type::VALUE_POLYNOMIAL)
                result = std::to_string(static_cast<int>(backend::INT_P_B(Polynomial(a.s))));
            el_vec[index].type = el_type::VALUE_NATURAL;
        }
        
        el_vec[index].s = result;
        el_vec.erase(el_vec.begin() + index + 1);
    }
    else if(el_vec[index].type == el_type::FUNC_OP2) {
        if((index + 2) >= el_vec.size())
            throw std::invalid_argument("Unable to calculate - check operators");
        
        auto a = el_vec[index+1], b = el_vec[index+2], op = el_vec[index];
        std::string result;

        el_vec[index].el_priority = 0;
        el_vec[index].group_priority = 0;
        el_vec[index].type = a.type;

        if(op.s == "[COM_NN_D]") {
            if(a.type != b.type || a.type != el_type::VALUE_NATURAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = std::to_string(static_cast<int>(backend::COM_NN_D(Natural(a.s), Natural(b.s))));
        }
        else if(op.s == "[ADD_NN_N]") {
            if(a.type != b.type || a.type != el_type::VALUE_NATURAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::ADD_NN_N(Natural(a.s), Natural(b.s)));
        }
        else if(op.s == "[SUB_NN_N]") {
            if(a.type != b.type || a.type != el_type::VALUE_NATURAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::SUB_NN_N(Natural(a.s), Natural(b.s)));
        }
        else if(op.s == "[MUL_ND_N]") {
            if(a.type != b.type || a.type != el_type::VALUE_NATURAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::MUL_ND_N(Natural(a.s), std::stoi(b.s)));
        }
        else if(op.s == "[MUL_NK_N]") {
            if(a.type != b.type || a.type != el_type::VALUE_NATURAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::MUL_Nk_N(Natural(a.s), Natural(b.s)));
        }
        else if(op.s == "[MUL_NN_N]") {
            if(a.type != b.type || a.type != el_type::VALUE_NATURAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::MUL_NN_N(Natural(a.s), Natural(b.s)));
        }
        else if(op.s == "[DIV_NN_N]") {
            if(a.type != b.type || a.type != el_type::VALUE_NATURAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::DIV_NN_N(Natural(a.s), Natural(b.s)));
        }
        else if(op.s == "[MOD_NN_N]") {
            if(a.type != b.type || a.type != el_type::VALUE_NATURAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::MOD_NN_N(Natural(a.s), Natural(b.s)));
        }
        else if(op.s == "[GCF_NN_N]") {
            if(a.type != b.type || a.type != el_type::VALUE_NATURAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::GCF_NN_N(Natural(a.s), Natural(b.s)));
        }
        else if(op.s == "[LCM_NN_N]") {
            if(a.type != b.type || a.type != el_type::VALUE_NATURAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::LCM_NN_N(Natural(a.s), Natural(b.s)));
        }
        else if(op.s == "[ADD_ZZ_Z]") {
            if(a.type != b.type || a.type != el_type::VALUE_INTEGER)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::ADD_ZZ_Z(Integer(a.s), Integer(b.s)));
        }
        else if(op.s == "[SUB_ZZ_Z]") {
            if(a.type != b.type || a.type != el_type::VALUE_INTEGER)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::SUB_ZZ_Z(Integer(a.s), Integer(b.s)));
        }
        else if(op.s == "[MUL_ZZ_Z]") {
            if(a.type != b.type || a.type != el_type::VALUE_INTEGER)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::MUL_ZZ_Z(Integer(a.s), Integer(b.s)));
        }
        else if(op.s == "[DIV_ZZ_Z]") {
            if(a.type != b.type || a.type != el_type::VALUE_INTEGER)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::DIV_ZZ_Z(Integer(a.s), Integer(b.s)));
        }
        else if(op.s == "[MOD_ZZ_Z]") {
            if(a.type != b.type || a.type != el_type::VALUE_INTEGER)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::MOD_ZZ_Z(Integer(a.s), Integer(b.s)));
        }
        else if(op.s == "[MUL_Zk_Z]") {
            if(a.type != el_type::VALUE_INTEGER || b.type != el_type::VALUE_NATURAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::MUL_Zk_Z(Integer(a.s), Natural(b.s)));
        }
        else if(op.s == "[ADD_QQ_Q]") {
            if(a.type != b.type || a.type != el_type::VALUE_RATIONAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::ADD_QQ_Q(Rational(a.s), Rational(b.s)));
        }
        else if(op.s == "[SUB_QQ_Q]") {
            if(a.type != b.type || a.type != el_type::VALUE_RATIONAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::SUB_QQ_Q(Rational(a.s), Rational(b.s)));
        }
        else if(op.s == "[MUL_QQ_Q]") {
            if(a.type != b.type || a.type != el_type::VALUE_RATIONAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::MUL_QQ_Q(Rational(a.s), Rational(b.s)));
        }
        else if(op.s == "[DIV_QQ_Q]") {
            if(a.type != b.type || a.type != el_type::VALUE_RATIONAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::DIV_QQ_Q(Rational(a.s), Rational(b.s)));
        }
        else if(op.s == "[ADD_PP_P]") {
            if(a.type != b.type || a.type != el_type::VALUE_POLYNOMIAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::ADD_PP_P(Polynomial(a.s), Polynomial(b.s)));
        }
        else if(op.s == "[SUB_PP_P]") {
            if(a.type != b.type || a.type != el_type::VALUE_POLYNOMIAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::SUB_PP_P(Polynomial(a.s), Polynomial(b.s)));
        }
        else if(op.s == "[MUL_PQ_P]") {
            if(a.type != el_type::VALUE_POLYNOMIAL || b.type != el_type::VALUE_RATIONAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::MUL_PQ_P(Polynomial(a.s), Rational(b.s)));
        }
        else if(op.s == "[MUL_Pxk_P]") {
            if(a.type != el_type::VALUE_POLYNOMIAL || b.type != el_type::VALUE_NATURAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::MUL_Pxk_P(Polynomial(a.s), Natural(b.s)));
        }
        else if(op.s == "[MUL_PP_P]") {
            if(a.type != b.type || a.type != el_type::VALUE_POLYNOMIAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::MUL_PP_P(Polynomial(a.s), Polynomial(b.s)));
        }
        else if(op.s == "[DIV_PP_P]") {
            if(a.type != b.type || a.type != el_type::VALUE_POLYNOMIAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::DIV_PP_P(Polynomial(a.s), Polynomial(b.s)));
        }
        else if(op.s == "[MOD_PP_P]") {
            if(a.type != b.type || a.type != el_type::VALUE_POLYNOMIAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::MOD_PP_P(Polynomial(a.s), Polynomial(b.s)));
        }
        else if(op.s == "[GCF_PP_P]") {
            if(a.type != b.type || a.type != el_type::VALUE_POLYNOMIAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");
            result = static_cast<std::string>(backend::GCF_PP_P(Polynomial(a.s), Polynomial(b.s)));
        }
        else if(op.s == "[cmp]") {
            if(a.type != b.type || a.type == el_type::VALUE_POLYNOMIAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");

            if(a.type == el_type::VALUE_NATURAL)
                result = std::to_string(backend::COM_NN_D(Natural(a.s), Natural(b.s)));
            else if(a.type == el_type::VALUE_INTEGER)
                result = std::to_string(backend::COM_ZZ_D(Integer(a.s), Integer(b.s)));
            else if(a.type == el_type::VALUE_RATIONAL)
                result = std::to_string(backend::COM_QQ_D(Rational(a.s), Rational(b.s)));
            el_vec[index].type = el_type::VALUE_NATURAL;
        }
        else if(op.s == "[gcd]") {
            if(a.type != b.type || a.type == el_type::VALUE_RATIONAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");

            if(a.type == el_type::VALUE_NATURAL)
                result = static_cast<std::string>(backend::GCF_NN_N(Natural(a.s), Natural(b.s)));
            else if(a.type == el_type::VALUE_INTEGER)
                result = static_cast<std::string>(backend::GCF_ZZ_Z(Integer(a.s), Integer(b.s)));
            else if(a.type == el_type::VALUE_POLYNOMIAL)
                result = static_cast<std::string>(backend::GCF_PP_P(Polynomial(a.s), Polynomial(b.s)));
        }
        else if(op.s == "[lcm]") {
            if(a.type != b.type || a.type == el_type::VALUE_POLYNOMIAL || a.type == el_type::VALUE_RATIONAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");

            if(a.type == el_type::VALUE_NATURAL)
                result = static_cast<std::string>(backend::LCM_NN_N(Natural(a.s), Natural(b.s)));
            else if(a.type == el_type::VALUE_INTEGER)
                result = static_cast<std::string>(backend::LCM_ZZ_Z(Integer(a.s), Integer(b.s)));
        }
        
        el_vec[index].s = result;
        el_vec.erase(el_vec.begin() + index + 2);
        el_vec.erase(el_vec.begin() + index + 1);
    }
    else if(el_vec[index].type == el_type::FUNC_OP3) {
        if((index + 3) >= el_vec.size())
            throw std::invalid_argument("Unable to calculate - check operators");
        
        auto a = el_vec[index+1], b = el_vec[index+2], c = el_vec[index+3], op = el_vec[index];
        std::string result;
        
        if(op.s == "[SUB_NDN_N]") {
            if(a.type != el_type::VALUE_NATURAL || b.type != el_type::VALUE_NATURAL || c.type != el_type::VALUE_NATURAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");

            result = static_cast<std::string>(backend::SUB_NDN_N(Natural(a.s), std::stoi(b.s), Natural(c.s)));
        }
        else if(op.s == "[DIV_NN_Dk]") {
            if(a.type != el_type::VALUE_NATURAL || b.type != el_type::VALUE_NATURAL || c.type != el_type::VALUE_NATURAL)
                throw std::invalid_argument("Unable to calculate - wrong operand types");

            result = std::to_string(backend::DIV_NN_Dk(Natural(a.s), Natural(b.s), Natural(c.s)));
        }
            
        el_vec[index].s = result;
        el_vec[index].el_priority = 0;
        el_vec[index].group_priority = 0;
        el_vec[index].type = a.type;
        el_vec.erase(el_vec.begin() + index + 2);
        el_vec.erase(el_vec.begin() + index + 1);
    }
}
