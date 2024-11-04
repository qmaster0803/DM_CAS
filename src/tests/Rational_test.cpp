#include <gtest/gtest.h>
#include <stdexcept>

#include "../include/Rational.h"

TEST(Rational_test, DefaultConstructor)
{
    Rational a;
    EXPECT_EQ(static_cast<std::string>(a), "0/1");
}

TEST(Rational_test, IntConstructor)
{
    Rational p(42);
    Rational n(-123);
    Rational z(0);
    EXPECT_EQ(static_cast<std::string>(p), "42/1");
    EXPECT_EQ(static_cast<std::string>(n), "-123/1");
    EXPECT_EQ(static_cast<std::string>(z), "0/1");
}

TEST(Rational_test, StringConstructor)
{
    // no numbers
    EXPECT_THROW({ Rational(""); }, std::invalid_argument);
    EXPECT_THROW({ Rational("/"); }, std::invalid_argument);
    EXPECT_THROW({ Rational("."); }, std::invalid_argument);
    EXPECT_THROW({ Rational("/."); }, std::invalid_argument);

    // / and . in one expr
    EXPECT_THROW({ Rational("-123/231234.34"); }, std::invalid_argument);
    EXPECT_THROW({ Rational("-534/.12332"); }, std::invalid_argument);
    EXPECT_THROW({ Rational("-534/.12332"); }, std::invalid_argument);

    // >= 2 dots
    EXPECT_THROW({ Rational("-534.123.32"); }, std::invalid_argument);
    EXPECT_THROW({ Rational("-53.41.23.32"); }, std::invalid_argument);

    // >= 2 slashes
    EXPECT_THROW({ Rational("-534//12332"); }, std::invalid_argument);
    EXPECT_THROW({ Rational("-534/12/332"); }, std::invalid_argument);
    EXPECT_THROW({ Rational("-534/12/332/"); }, std::invalid_argument);

    EXPECT_EQ(static_cast<std::string>(Rational("-23/23")), "-1/1");
    // test with zero
    EXPECT_EQ(static_cast<std::string>(Rational("0/23")), "0/1");

    // decimal fraction
    EXPECT_EQ(static_cast<std::string>(Rational("4545.23")), "454523/100");

    // integer
    EXPECT_EQ(static_cast<std::string>(Rational("0912")), "912/1");
    EXPECT_EQ(static_cast<std::string>(Rational("-18624")), "-18624/1");

    // reduction
    EXPECT_EQ(static_cast<std::string>(Rational("46/23")), "2/1");
    EXPECT_EQ(static_cast<std::string>(Rational("45.25")), "181/4");
    EXPECT_EQ(static_cast<std::string>(Rational("0.23")), "23/100");
    EXPECT_EQ(static_cast<std::string>(Rational("0/2312312312313123")), "0/1");
    EXPECT_EQ(static_cast<std::string>(Rational("-2312312312313123.23")), "-231231231231312323/100");
}

TEST(Rational_test, CharArrayConstructor)
{
    const char num[] = "-123.232";

    EXPECT_EQ(static_cast<std::string>(Rational(num)), "-15404/125");

    // other tested in string contructor
}

TEST(Rational_test, NaturalConstructor)
{
    EXPECT_EQ(Rational(Natural("342349023432343242")), Rational("342349023432343242/1"));
}

TEST(Rational_test, IntegerConstructor)
{
    EXPECT_EQ(Rational(Integer("-342349023432343242")), Rational("-342349023432343242"));
    EXPECT_EQ(Rational(Integer("342349023432343242")), Rational("342349023432343242"));
}

TEST(Rational_test, IntegerAndNaturalConstructor)
{
    Integer int_p("23412331");
    Integer int_n("-9985986859");
    Integer int_z;

    Natural nat_p("2342342");
    Natural nat_z;

    Rational r1(int_p, nat_p);
    Rational r2(int_n, nat_p);
    Rational r3(int_z, nat_p);


    EXPECT_EQ(static_cast<std::string>(r1), "23412331/2342342");
    EXPECT_EQ(static_cast<std::string>(r2), "-9985986859/2342342");
    EXPECT_EQ(static_cast<std::string>(r3), "0/1");

    EXPECT_THROW({ Rational(int_p, nat_z); }, std::invalid_argument);
    EXPECT_THROW({ Rational(int_z, nat_z); }, std::invalid_argument);
}

TEST(Rational_test, CopyConstructor)
{
    Rational r1("-232604563943889057289742894781/120345893485980285");
    Rational r2(r1);
    EXPECT_EQ(r1, r2);
}

TEST(Rational_test, MoveConstructor)
{
    Rational r1("12322123654654664564646546456546.212312321313");
    Rational r2(std::move(r1));
    EXPECT_FALSE(r2.is_integer());
    EXPECT_EQ(static_cast<std::string>(r2), "12322123654654664564646546456546212312321313/1000000000000");
}

TEST(Rational_test, IsZero)
{
    Rational r;
    EXPECT_TRUE(r.is_zero());

    Rational r_nonzero(5);
    EXPECT_FALSE(r_nonzero.is_zero());
}

TEST(Rational_test, IsReducted)
{
    EXPECT_TRUE(Rational("-10/3").is_reducted());
    EXPECT_TRUE(Rational("1/3").is_reducted());
    EXPECT_TRUE(Rational("0/2").is_reducted());
}

TEST(Rational_test, IsInteger)
{
    EXPECT_FALSE(Rational("-10/3").is_integer());
    EXPECT_TRUE(Rational("-10/1").is_integer());
    EXPECT_TRUE(Rational("-10/5").is_integer());
    EXPECT_TRUE(Rational("0/5").is_integer());

}

TEST(Rational_test, Comparison)
{
    Rational q1("52321321/2321");
    Rational q2(232);
    Rational q3("-12312321");
    Rational q4("-123/902131299449");
    Rational q5(0);

    // >
    EXPECT_TRUE(q1 > q2);    // q1 is larger than q2
    EXPECT_FALSE(q2 > q1);   // q2 is not larger than q1
    EXPECT_FALSE(q3 > q1);   // q3 is less than q1
    EXPECT_TRUE(q4 > q3);    // q3 is less than q4
    EXPECT_TRUE(q5 > q4);    // q4 is less than zero

    // <
    EXPECT_FALSE(q1 < q2);   // q1 is not less than q2
    EXPECT_TRUE(q2 < q1);    // q2 is less than q1
    EXPECT_TRUE(q3 < q2);    // q3 is less than q2
    EXPECT_FALSE(q4 < q3);   // q3 is less than q4
    EXPECT_FALSE(q5 < q4);   // zero is not less than q4

    // >=
    EXPECT_TRUE(q1 >= q1);   // q1 is equal to q1
    EXPECT_TRUE(q1 >= q2);   // q1 is greater than q2
    EXPECT_FALSE(q2 >= q1);  // q2 is not greater than or equal to q1
    EXPECT_TRUE(q3 >= q3);   // q3 is equal to q3
    EXPECT_TRUE(q5 >= q5);   // zero is equal to zero

    // <=
    EXPECT_TRUE(q1 <= q1);   // q1 is equal to q1
    EXPECT_FALSE(q1 <= q2);  // q1 is not less than or equal to q2
    EXPECT_TRUE(q2 <= q1);   // q2 is less than or equal to q1
    EXPECT_TRUE(q3 <= q3);   // q3 is equal to q3
    EXPECT_TRUE(q5 <= q5);   // zero is equal to zero

    // ==
    EXPECT_FALSE(q1 == q2);  // q1 and q2 are not equal
    EXPECT_TRUE(q3 == q3);   // q3 is equal to itself
    EXPECT_TRUE(q5 == Rational(0)); // zero is equal to zero

    // !=
    EXPECT_TRUE(q1 != q2);   // q1 and q2 are not equal
    EXPECT_FALSE(q3 != q3);  // q3 is equal to itself
    EXPECT_TRUE(q4 != q3);   // q4 and q3 are not equal
    EXPECT_FALSE(q5 != Rational(0)); // zero is equal to zero
}

TEST(Rational_test, AdditionOperator)
{
    Rational q1("52321321/2321");
    Rational q2(232);
    Rational q3("-12312321");
    Rational q4("-123/902131299449");
    Rational q5(0);

    Rational r1 = q1 + q2;
    Rational r2 = q2 + q3;
    Rational r3 = q1 + q4;
    Rational r4 = q4 + q5;
    Rational r5 = q5 + q5;

    EXPECT_EQ(static_cast<std::string>(r1), "52859793/2321");
    EXPECT_EQ(static_cast<std::string>(r2), "-12312089/1");
    EXPECT_EQ(static_cast<std::string>(r3), "47200701302617966646/2093846746021129");
    EXPECT_EQ(static_cast<std::string>(r4), "-123/902131299449");
    EXPECT_EQ(static_cast<std::string>(r5), "0/1");
}

TEST(Rational_test, SubstractionOperator)
{
    Rational q1("52321321/2321");
    Rational q2(232);
    Rational q3("-12312321");
    Rational q4("-123/902131299449");
    Rational q5(0);

    Rational r1 = q1 - q2;
    Rational r2 = q2 - q3;
    Rational r3 = q1 - q4;
    Rational r4 = q4 - q5;
    Rational r5 = q5 - q5;

    EXPECT_EQ(static_cast<std::string>(r1), "51782849/2321");
    EXPECT_EQ(static_cast<std::string>(r2), "12312553/1");
    EXPECT_EQ(static_cast<std::string>(r3), "47200701302618537612/2093846746021129");
    EXPECT_EQ(static_cast<std::string>(r4), "-123/902131299449");
    EXPECT_EQ(static_cast<std::string>(r5), "0/1");
}

TEST(Rational_test, MultiplicationOperator)
{
    Rational q1("52321321/2321");
    Rational q2(232);
    Rational q3("-12312321");
    Rational q4("-123/902131299449");
    Rational q5(0);

    Rational r1 = q1 * q2;
    Rational r2 = q2 * q3;
    Rational r3 = q1 * q4;
    Rational r4 = q4 * q5;
    Rational r5 = q5 * q5;

    EXPECT_EQ(static_cast<std::string>(r1), "12138546472/2321");
    EXPECT_EQ(static_cast<std::string>(r2), "-2856458472/1");
    EXPECT_EQ(static_cast<std::string>(r3), "-6435522483/2093846746021129");
    EXPECT_EQ(static_cast<std::string>(r4), "0/1");
    EXPECT_EQ(static_cast<std::string>(r5), "0/1");
}

TEST(Rational_test, DivisionOperator)
{
    Rational q1("52321321/2321");
    Rational q2(232);
    Rational q3("-12312321");
    Rational q4("-123/902131299449");
    Rational q5(0);

    Rational r1 = q1 / q2;
    Rational r2 = q2 / q3;
    Rational r3 = q1 / q4;
    Rational r4 = q5 / q1;

    EXPECT_EQ(static_cast<std::string>(r1), "52321321/538472");
    EXPECT_EQ(static_cast<std::string>(r2), "-232/12312321");
    EXPECT_EQ(static_cast<std::string>(r3), "-47200701302618252129/285483");
    EXPECT_THROW({ q4 / q5; }, std::domain_error);
    EXPECT_EQ(static_cast<std::string>(r4), "0/1");
}

// Тест оператора преобразования в строку
TEST(Rational_test, ToStringOperator)
{
    Rational q1("123");
    Rational q2("-123");
    Rational q3("123/123");
    Rational q4("123/-123");
    Rational q5("123.2344");
    Rational q6("0");
    Rational q7("0/6");
    Rational q8("1232131231");

    std::string str1 = static_cast<std::string>(q1);
    std::string str2 = static_cast<std::string>(q2);
    std::string str3 = static_cast<std::string>(q3);
    std::string str4 = static_cast<std::string>(q4);
    std::string str5 = static_cast<std::string>(q5);
    std::string str6 = static_cast<std::string>(q6);
    std::string str7 = static_cast<std::string>(q7);
    std::string str8 = static_cast<std::string>(q8);

    EXPECT_EQ(str1, "123/1");
    EXPECT_EQ(str2, "-123/1");
    EXPECT_EQ(str3, "1/1");
    EXPECT_EQ(str4, "-1/1");
    EXPECT_EQ(str5, "154043/1250");
    EXPECT_EQ(str6, "0/1");
    EXPECT_EQ(str7, "0/1");
    EXPECT_EQ(str8, "1232131231/1");
}

TEST(Rational_test, QToZOperator)
{
    EXPECT_THROW({ static_cast<Integer>(Rational("25/36")); }, std::runtime_error);
    EXPECT_NO_THROW({ static_cast<Integer>(Rational("0/36")); });
    EXPECT_THROW({ static_cast<Integer>(Rational("-25/36")); }, std::runtime_error);

    EXPECT_EQ(static_cast<Integer>(Rational("-25/5")), Integer(-5));
    EXPECT_EQ(static_cast<Integer>(Rational("0/5")), Integer(0));
    EXPECT_EQ(static_cast<Integer>(Rational("-1231231239/1231231239")), Integer(-1));
    EXPECT_EQ(static_cast<Integer>(Rational("90034/-2")), Integer(-45017));
}
