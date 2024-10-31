#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
#include "../include/Natural.h"

TEST(Natural_test, Comparison_test)
{
    Natural a = 5;
    Natural b = 1124112460;
    Natural c = 0;
    Natural d = 5;

    EXPECT_TRUE (a <  b);
    EXPECT_TRUE (a <= b);
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(a >  b);
    EXPECT_FALSE(a >= b);
    
    EXPECT_FALSE(a <  c);
    EXPECT_FALSE(a <= c);
    EXPECT_FALSE(a == c);
    EXPECT_TRUE (a >  c);
    EXPECT_TRUE (a >= c);

    EXPECT_TRUE (c <  d);
    EXPECT_TRUE (c <= d);
    EXPECT_FALSE(c == d);
    EXPECT_FALSE(c >  d);
    EXPECT_FALSE(c >= d);

    EXPECT_FALSE(a <  d);
    EXPECT_TRUE (a <= d);
    EXPECT_TRUE (a == d);
    EXPECT_FALSE(a >  d);
    EXPECT_TRUE (a >= d);
}

TEST(Natural_test, Add_test)
{
    Natural a = 5;
    Natural b = 9;
    Natural c = "96145123123816513651812471246152426416245";
    Natural d = "718175412047233846975431963418274316825342378162043127301625391231243";

    const Natural res1 = 14;
    const Natural res2 = "718175412047233846975431963514419439949158891813855598547777817647488";

    EXPECT_EQ(res1, (a + b));
    EXPECT_EQ(res2, (c + d));

    Natural test1 = a + b;
    Natural test2 = c + d;
    EXPECT_EQ(res1, test1);
    EXPECT_EQ(res2, test2);

    auto test1_auto = a + b;
    auto test2_auto = c + d;
    EXPECT_EQ(res1, test1_auto);
    EXPECT_EQ(res2, test2_auto);

    EXPECT_EQ(a + 1, 6);
}

TEST(Natural_test, Sub_test)
{
    Natural a = 5;
    Natural b = 9;
    Natural c = "96145123123816513651812471246152426416245";
    Natural d = "718175412047233846975431963418274316825342378162043127301625391231243";

    const Natural res1 = 4;
    const Natural res2 = "718175412047233846975431963322129193701525864510230656055472964814998";

    EXPECT_EQ(res1, (b - a));
    EXPECT_EQ(res2, (d - c));

    Natural test1 = b - a;
    Natural test2 = d - c;
    EXPECT_EQ(res1, test1);
    EXPECT_EQ(res2, test2);

    auto test1_auto = b - a;
    auto test2_auto = d - c;
    EXPECT_EQ(res1, test1_auto);
    EXPECT_EQ(res2, test2_auto);

    EXPECT_EQ(a - 1, 4);

    EXPECT_EQ(Natural(15) - 10, Natural(5));
    EXPECT_THROW({ auto n = a - b; }, std::out_of_range);
    EXPECT_THROW({ auto n = c - d; }, std::out_of_range);
}

TEST(Natural_test, Div_test)
{
    Natural a = "97698126531298371231203";
    Natural b = "1923761927387612714";

    EXPECT_EQ(a / b, 50784);
    EXPECT_EQ(b / a, 0);

    EXPECT_EQ(Natural(0) / Natural(1), 0);
    EXPECT_EQ(Natural(6) / Natural(7), 0);
    EXPECT_EQ(Natural(7) / Natural(7), 1);

    EXPECT_EQ(Natural(154) / 3, 51);

    EXPECT_THROW({ auto i = Natural(135) / Natural(0); }, std::domain_error);
}

TEST(Natural_test, Mod_test)
{
    Natural a = "97698126531298371231203";
    Natural b = "1923761927387612714";

    EXPECT_EQ(a % b, Natural("1800810845847163427"));
    EXPECT_EQ(b % a, b);

    EXPECT_EQ(Natural(0) % Natural(1), 0);
    EXPECT_EQ(Natural(6) % Natural(7), 6);
    EXPECT_EQ(Natural(7) % Natural(7), 0);

    EXPECT_EQ(Natural(154) % 3, 1);

    EXPECT_THROW({ auto i = Natural(135) % Natural(0); }, std::domain_error);
}

TEST(Natural_test, Inc_dec_test)
{
    Natural a = "97698126531298371231203";
    Natural b = "5";

    EXPECT_EQ(++a, Natural("97698126531298371231204"));
    EXPECT_EQ(a++, Natural("97698126531298371231204"));
    EXPECT_EQ(a,   Natural("97698126531298371231205"));
    
    EXPECT_EQ(++b, 6);
    EXPECT_EQ(b++, 6);
    EXPECT_EQ(b,   7);

    EXPECT_EQ(--a, Natural("97698126531298371231204"));
    EXPECT_EQ(a--, Natural("97698126531298371231204"));
    EXPECT_EQ(a,   Natural("97698126531298371231203"));
    
    EXPECT_EQ(--b, 6);
    EXPECT_EQ(b--, 6);
    EXPECT_EQ(b,   5);

    Natural c = 1;
    EXPECT_EQ(--c, 0);
    EXPECT_THROW({ --c; }, std::out_of_range);

    c = 1;
    EXPECT_EQ(c--, 1);
    EXPECT_THROW({ c--; }, std::out_of_range);
}

TEST(Natural_test, Visualization_test)
{
    Natural a = "97698126531298371231203";
    Natural b = 0;
    Natural c = 5;

    EXPECT_EQ((std::string)a, "97698126531298371231203");
    EXPECT_EQ((std::string)b, "0");
    EXPECT_EQ((std::string)c, "5");
    
    std::stringstream ss_a;
    std::stringstream ss_b;
    std::stringstream ss_c;
    ss_a << a;
    ss_b << b;
    ss_c << c;
    EXPECT_EQ(ss_a.str(), "97698126531298371231203");
    EXPECT_EQ(ss_b.str(), "0");
    EXPECT_EQ(ss_c.str(), "5");
}
