#include <gtest/gtest.h>

#include "../include/Parser.h"

TEST(Parser_test, base)
{
    Parser parser;
    
    const std::string line1 = "(5654646464 - 123213123) + ([is_zero] 3 + 790 - [lcm] 56 8 * (5 ++ - 3 --)) -- << 2";
    const std::string res1  = "553143390600";
    EXPECT_EQ(parser.calc(default_vartype::VARTYPE_NATURAL, line1), res1);
    
    const std::string line2 = "5 + 5124 + 7 * 8 / 3";
    const std::string res2  = "5147";
    EXPECT_EQ(parser.calc(default_vartype::VARTYPE_NATURAL, line2), res2);

    const std::string line3 = "";
    const std::string res3   = "";
    EXPECT_EQ(parser.calc(default_vartype::VARTYPE_NATURAL, line3), res3);

    const std::string line4 = "";
    const std::string res4   = "";
    EXPECT_EQ(parser.calc(default_vartype::VARTYPE_NATURAL, line3), res3);
    
    const std::string line5 = "";
    const std::string res5   = "";
    EXPECT_EQ(parser.calc(default_vartype::VARTYPE_NATURAL, line3), res3);
    
    const std::string line6 = "";
    const std::string res6   = "";
    EXPECT_EQ(parser.calc(default_vartype::VARTYPE_NATURAL, line3), res3);
}
