#include <gtest/gtest.h>

#include "../include/Parser.h"

TEST(Parser_test, base)
{
    Parser parser;
    const std::string line1 = "(5654646464 - 123213123) + ([is_zero] 3 + 790 - [lcm] 56 8 * (5 ++ - 3 --)) -- << 2";
    const std::string res1  = "553143390600";

    // parser.calc(default_vartype::VARTYPE_NATURAL, "5 + 5124 + 7 * 8 / 3");
    // parser.calc(default_vartype::VARTYPE_NATURAL, "5");
    // parser.calc(default_vartype::VARTYPE_NATURAL, "5 + 5 % 002 + 7151 * 8");
    // parser.calc(default_vartype::VARTYPE_NATURAL, "5 % 0 + [is_zero] 5 + 7 * [gcd] 8 2");
    EXPECT_EQ(parser.calc(default_vartype::VARTYPE_NATURAL, line1), res1);
    
    // EXPECT_EQ();
}
