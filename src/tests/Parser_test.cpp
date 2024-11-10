#include <gtest/gtest.h>

#include "../include/Parser.h"

TEST(Parser_test, base)
{
    Parser parser;

    parser.parse_and_calc(VARTYPE_NATURAL, "5 + 5 + 7 * 8 / 3");
    parser.parse_and_calc(VARTYPE_NATURAL, "5");
    parser.parse_and_calc(VARTYPE_NATURAL, "5 + 5 % 2 + 7 * 8");
    parser.parse_and_calc(VARTYPE_NATURAL, "5 % 0 + 5 + 7 * 8");
    
    EXPECT_EQ();
}
