#include <gtest/gtest.h>

#include "../include/Integer.h"

TEST(Integer_test, DefaultConstructor)
{
    Integer a;
    EXPECT_EQ(static_cast<std::string>(a), "0");
}

TEST(Integer_test, IntConstructor)
{
    Integer a(42);
    EXPECT_EQ(static_cast<std::string>(a), "42");
}

TEST(Integer_test, StringConstructor)
{
    Integer p("12345");
    Integer n("-123123");
    EXPECT_EQ(static_cast<std::string>(p), "12345");
    EXPECT_EQ(static_cast<std::string>(n), "-12345");
}

TEST(Integer_test, CharArrayConstructor)
{
    char p_arr[] = {'6', '7', '8', '9', '0'};
    char n_arr[] = {'-', '6', '7', '8', '9', '0'};

    Integer p(p_arr);
    Integer n(n_arr);
    EXPECT_EQ(static_cast<std::string>(p), "67890");
    EXPECT_EQ(static_cast<std::string>(n), "-67890");
}

TEST(Integer_test, CopyConstructor)
{
    Integer a(99);
    Integer copy(a);
    EXPECT_EQ(copy, a);
}

TEST(Integer_test, MoveConstructor)
{
    Integer a(88);
    Integer moved(std::move(a));
    EXPECT_EQ(static_cast<std::string>(moved), "88");
}

TEST(Integer_test, Comparison)
{

    Integer p1 = 52321321;
    Integer p2 = 232;
    Integer n1 = -12312321;
    Integer n2 = "-90213123232312323222210090909999999999449";
    Integer z  = 0;

    // two positives comparison
    EXPECT_FALSE(p1 <  p2);
    EXPECT_FALSE(p1 <= p2);
    EXPECT_FALSE(p1 == p2);
    EXPECT_TRUE (p1 >  p2);
    EXPECT_TRUE (p1 >= p2);
    EXPECT_FALSE(p1 != p2);

    // positive and negative comparison
    EXPECT_FALSE(p1 <  n1);
    EXPECT_FALSE(p1 <= n1);
    EXPECT_FALSE(p1 == n1);
    EXPECT_TRUE (p1 >  n1);
    EXPECT_TRUE (p1 >= n1);
    EXPECT_FALSE(p1 != n2);

    // two negatives comparison
    EXPECT_FALSE(n1 <  n2);
    EXPECT_FALSE(n1 <= n2);
    EXPECT_FALSE(n1 == n2);
    EXPECT_TRUE (n1 >  n2);
    EXPECT_TRUE (n1 >= n2);
    EXPECT_FALSE(n1 != n2);

    // positive and zero comparison
    EXPECT_FALSE(p1 <  z);
    EXPECT_FALSE(p1 <= z);
    EXPECT_FALSE(p1 == z);
    EXPECT_TRUE (p1 >  z);
    EXPECT_TRUE (p1 >= z);
    EXPECT_FALSE(p1 != z);

    // negative and zero comparison
    EXPECT_TRUE (n1 <  z);
    EXPECT_TRUE (n1 <= z);
    EXPECT_FALSE(n1 == z);
    EXPECT_FALSE(n1 >  z);
    EXPECT_FALSE(n1 >= z);
    EXPECT_FALSE(n1 != z);

    // comparison of two equal elements
    EXPECT_FALSE(p1 >  p1);
    EXPECT_TRUE (p1 <= p1);
    EXPECT_TRUE (p1 == p1);
    EXPECT_FALSE(p1 >  p1);
    EXPECT_TRUE (p1 >= p1);
    EXPECT_FALSE(p1 != p1);
}

TEST(Integer_test, AdditionOperator)
{
    Integer p1(321675);
    Integer p2(702934);
    Integer n1(-1021);
    Integer n2("-2135435534535399999009");
    Integer z;

    Integer r1 = p1 + p2;
    Integer r2 = p1 + n1;
    Integer r3 = n1 + n2;
    Integer r4 = p1 + z;
    Integer r5 = z + z;

    EXPECT_EQ(static_cast<std::string>(r1), "1024609");
    EXPECT_EQ(static_cast<std::string>(r2), "320654");
    EXPECT_EQ(static_cast<std::string>(r3), "-2135435534535400000030");
    EXPECT_EQ(static_cast<std::string>(r4), "321675");
    EXPECT_EQ(static_cast<std::string>(r5), "0");
}

TEST(Integer_test, SubstractionOperator)
{
    Integer p1(321675);
    Integer p2(702934);
    Integer n1(-1021);
    Integer n2("-2135435534535399999009");
    Integer z;

    Integer r1 = p1 - p2;
    Integer r2 = p1 - n1;
    Integer r3 = n1 - n2;
    Integer r4 = p1 -  z;
    Integer r5 = z  - p1;
    Integer r6 = n1 - p1;

    EXPECT_EQ(static_cast<std::string>(r1), "-381259");
    EXPECT_EQ(static_cast<std::string>(r2), "322696");
    EXPECT_EQ(static_cast<std::string>(r3), "2135435534535399997988");
    EXPECT_EQ(static_cast<std::string>(r4), "321675");
    EXPECT_EQ(static_cast<std::string>(r5), "-321675");
    EXPECT_EQ(static_cast<std::string>(r6), "-322696");
}

TEST(Integer_test, MultiplicationOperator)
{
    Integer p1(321675);
    Integer p2(702934);
    Integer n1(-1021);
    Integer n2("-2135435534535399999009");
    Integer z;

    Integer r1 = p1 * p2;
    Integer r2 = p1 * n1;
    Integer r3 = n1 * n2;
    Integer r4 = p1 *  z;
    Integer r5 = z  * n1;
    Integer r6 = n1 * p1;

    EXPECT_EQ(static_cast<std::string>(r1), "226116294450");
    EXPECT_EQ(static_cast<std::string>(r2), "-328430175");
    EXPECT_EQ(static_cast<std::string>(r3), "2180279680760643398988189");
    EXPECT_EQ(static_cast<std::string>(r4), "0");
    EXPECT_EQ(static_cast<std::string>(r5), "0");
    EXPECT_EQ(static_cast<std::string>(r6), "-328430175");
}

TEST(Integer_test, DivisionOperator)
{
    Integer p1(321675);
    Integer p2(702934);
    Integer n1(-1021);
    Integer n2("-2135435534535399999009");
    Integer z;

    Integer r1 = p1 / p2;
    Integer r2 = p1 / n1;
    Integer r3 = n2 / n1;
    Integer r4 = z  / n1;
    Integer r5 = n1 / p1;

    EXPECT_EQ(static_cast<std::string>(r1), "0");
    EXPECT_EQ(static_cast<std::string>(r2), "-316");
    EXPECT_EQ(static_cast<std::string>(r3), "2091513745872086189");
    EXPECT_THROW(p1 / z, std::domain_error);
    EXPECT_EQ(static_cast<std::string>(r4), "0");
    EXPECT_EQ(static_cast<std::string>(r5), "0");
}

TEST(Integer_test, ModulusOperator)
{
    Integer p1(321675);
    Integer p2(702934);
    Integer n1(-1021);
    Integer n2("-2135435534535399999009");
    Integer z;

    Integer r1 = p1 % p2;
    Integer r2 = p1 % n1;
    Integer r3 = n2 % n1;
    Integer r4 = z  % n1;
    Integer r5 = n1 % p1;

    EXPECT_EQ(static_cast<std::string>(r1), "321675");
    EXPECT_EQ(static_cast<std::string>(r2), "-535");
    EXPECT_EQ(static_cast<std::string>(r3), "-1021");
    EXPECT_THROW(p1 % z, std::domain_error);
    EXPECT_EQ(static_cast<std::string>(r4), "0");
    EXPECT_EQ(static_cast<std::string>(r5), "320654");
}

TEST(Integer_test, ShiftLeftOperator)
{
    Integer p(213123123);
    Integer n("-2154867946778953485739845");
    Integer z;

    EXPECT_EQ(p << 0, p);
    EXPECT_EQ(static_cast<std::string>(p << 3), "213123123000");

    EXPECT_EQ(n << 0, n);
    EXPECT_EQ(static_cast<std::string>(n << 3), "-2154867946778953485739845000");

    EXPECT_EQ(z << 0, "0");
    EXPECT_EQ(static_cast<std::string>(n << 3), "0");
}

TEST(Integer_test, PreIncrementOperator)
{
    Integer p(5);
    Integer n(-1);
    Integer z;
    ++p;
    ++n;
    ++z;
    EXPECT_EQ(static_cast<std::string>(p), "6");
    EXPECT_EQ(static_cast<std::string>(n), "0");
    EXPECT_EQ(static_cast<std::string>(z), "1");
}

TEST(Integer_test, PostIncrementOperator)
{
    Integer p(5);
    Integer n(-1);
    Integer z;
    Integer r = p++;
    n++;
    z++;
    EXPECT_EQ(static_cast<std::string>(r), "5");
    EXPECT_EQ(static_cast<std::string>(p), "6");
    EXPECT_EQ(static_cast<std::string>(n), "0");
    EXPECT_EQ(static_cast<std::string>(z), "1");
}

TEST(Integer_test, PreDecrementOperator)
{
    Integer p(5);
    Integer n(-1);
    Integer z;
    --p;
    --n;
    --z;
    EXPECT_EQ(static_cast<std::string>(p), "4");
    EXPECT_EQ(static_cast<std::string>(n), "-2");
    EXPECT_EQ(static_cast<std::string>(z), "-1");
}

TEST(Integer_test, PostDecrementOperator)
{
    Integer p(5);
    Integer n(-1);
    Integer z;
    Integer r = p--;
    n--;
    z--;
    EXPECT_EQ(static_cast<std::string>(r), "5");
    EXPECT_EQ(static_cast<std::string>(p), "4");
    EXPECT_EQ(static_cast<std::string>(n), "-2");
    EXPECT_EQ(static_cast<std::string>(z), "-1");
}

// Тест оператора преобразования в строку
TEST(Integer_test, ToStringOperator)
{
    Integer p(123);
    Integer n(-123);
    std::string str1 = static_cast<std::string>(p);
    std::string str2 = static_cast<std::string>(n);
    EXPECT_EQ(str1, "123");
    EXPECT_EQ(str2, "-123");
}