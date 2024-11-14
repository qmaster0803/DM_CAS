#include <gtest/gtest.h>

#include "../include/backend.h"

using namespace backend;

class NaturalTest : public ::testing::Test {
protected:
    Natural n1;
    Natural n2;
    Natural n3; // Additional Natural numbers for tests
    Natural n4;

    void SetUp() override
    {
        n1 = Natural("5");
        n2 = Natural("432432423050394854398503453083052345");
        n3 = Natural(0); // Used for zero tests
        n4 = Natural(123);
    }
};

// -----------------------------------------
// Natural
// -----------------------------------------

// N-1
TEST_F(NaturalTest, COM_NN_D_test)
{
    EXPECT_EQ(COM_NN_D(n1, n2), 1); // n1 < n2
    EXPECT_EQ(COM_NN_D(n2, n1), 2); // n2 > n1
    EXPECT_EQ(COM_NN_D(n1, n1), 0); // n1 == n1
}

// N-2
TEST_F(NaturalTest, NZER_N_B_test)
{
    EXPECT_FALSE(NZER_N_B(n3)); // Should return false for zero
    EXPECT_TRUE(NZER_N_B(n1)); // Should return true for non-zero
}

// N-3
TEST_F(NaturalTest, ADD_1N_N_test)
{
    EXPECT_EQ(ADD_1N_N(n2), Natural("432432423050394854398503453083052346"));
    EXPECT_EQ(ADD_1N_N(n3), Natural(1));
}

// N-4
TEST_F(NaturalTest, ADD_NN_N_test)
{
    EXPECT_EQ(ADD_NN_N(n1, n2), Natural("432432423050394854398503453083052350"));
    EXPECT_EQ(ADD_NN_N(n3, n1), Natural(5)); // 0 + 5 = 5
}

// N-5
TEST_F(NaturalTest, SUB_NN_N_test)
{
    EXPECT_EQ(SUB_NN_N(n2, n1), Natural("432432423050394854398503453083052340"));
    EXPECT_EQ(SUB_NN_N(n2, n3), n2);
    EXPECT_THROW({ SUB_NN_N(n1, n2); }, std::out_of_range); // Should throw for n1 < n2
}

// N-6
TEST_F(NaturalTest, MUL_ND_N_test)
{
    EXPECT_EQ(MUL_ND_N(n2, 2), Natural("864864846100789708797006906166104690")); 
    EXPECT_THROW({ MUL_ND_N(n1, 10); }, std::invalid_argument); // Should throw for d > 9
}

// N-7
TEST_F(NaturalTest, MUL_Nk_N_test)
{
    Natural k = Natural("1235");
    
    EXPECT_EQ(MUL_Nk_N(n1, k), n1 << k);
    EXPECT_EQ(MUL_Nk_N(n2, n1), n2 << n1);
    EXPECT_EQ(MUL_Nk_N(n1, n3), n1);
}

// N-8
TEST_F(NaturalTest, MUL_NN_N_test)
{
    EXPECT_EQ(MUL_NN_N(n1, n2), Natural("2162162115251974271992517265415261725"));
    EXPECT_EQ(MUL_NN_N(n1, n3), Natural(0));
    EXPECT_EQ(MUL_NN_N(n3, n2), Natural(0));
}

// N-9
TEST_F(NaturalTest, SUB_NDN_N_test)
{
    EXPECT_EQ(SUB_NDN_N(n2, 2, n1), Natural("432432423050394854398503453083052335"));
    EXPECT_THROW(SUB_NDN_N(n2, 10, n1), std::invalid_argument); // Should throw for d > 9
}

// N-10
TEST_F(NaturalTest, DIV_NN_Dk_test)
{
    // TODO!!!!!
    EXPECT_EQ(DIV_NN_Dk(n1, n2, n4), 0);
    EXPECT_EQ(DIV_NN_Dk(n2, n1, Natural(10)), 8);
    EXPECT_THROW({ DIV_NN_Dk(n1, n3, n2); }, std::domain_error);
}

// N-11
TEST_F(NaturalTest, DIV_NN_N_test)
{
    EXPECT_EQ(DIV_NN_N(n2, n1), Natural("86486484610078970879700690616610469"));
    EXPECT_THROW(DIV_NN_N(n1, n3), std::domain_error);
}

// N-12
TEST_F(NaturalTest, MOD_NN_N_test)
{
    EXPECT_EQ(MOD_NN_N(n2, n1), Natural(0));
    EXPECT_EQ(MOD_NN_N(n1, n2), Natural(5));
    EXPECT_THROW({ MOD_NN_N(n2, n3); }, std::domain_error);
    EXPECT_EQ(MOD_NN_N(n3, n2), Natural(0));
}

// N-13
TEST_F(NaturalTest, GCF_NN_N_test)
{
    EXPECT_EQ(GCF_NN_N(n2, n1), Natural(5));
    EXPECT_EQ(GCF_NN_N(n1, n2), Natural(5));
    EXPECT_EQ(GCF_NN_N(n4, Natural(12)), Natural(3));
}

// N-14
TEST_F(NaturalTest, LCM_NN_N_test)
{
    EXPECT_EQ(LCM_NN_N(n2, n1), n2);
    EXPECT_EQ(LCM_NN_N(n4, n4), n4);
    EXPECT_EQ(LCM_NN_N(n2, n1), n2);
}

// N-additional-1
TEST_F(NaturalTest, SUB_1N_N_test)
{
    EXPECT_EQ(SUB_1N_N(n1), Natural(4)); // 5 - 1 = 4
    EXPECT_EQ(SUB_1N_N(n2), Natural("432432423050394854398503453083052344"));
    EXPECT_THROW({ SUB_1N_N(n3); }, std::out_of_range);
}

// N-additional-2
TEST_F(NaturalTest, TRANS_N_Q_test)
{
    Rational r = TRANS_N_Q(n1);
    EXPECT_EQ(r, Rational(5)); // Assuming Rational works similarly
}

// N-additional-3
TEST_F(NaturalTest, TRANS_N_P_test)
{
    Polynomial p = TRANS_N_P(n1);
    EXPECT_EQ(p, Polynomial(5)); // Assuming Polynomial works similarly
}

// -----------------------------------------
// Integer
// -----------------------------------------

class IntegerTest : public ::testing::Test {
protected:
    Integer i1;
    Integer i2;
    Integer i3;
    Integer i4;
    
    void SetUp() override {
        i1 = Integer(0);
        i2 = Integer(25);
        i3 = Integer(-231123);
        i4 = Integer(54353452);
    }
};

// Z-1
TEST_F(IntegerTest, ABS_Z_Z_test)
{
    EXPECT_EQ(ABS_Z_Z(i1), Integer(0));
    EXPECT_EQ(ABS_Z_Z(i2), Integer(25));
    EXPECT_EQ(ABS_Z_Z(i3), Integer(231123));
    EXPECT_EQ(ABS_Z_Z(i4), Integer(54353452));
}

// Z-2
TEST_F(IntegerTest, SGN_Z_D_test)
{
    EXPECT_EQ(SGN_Z_D(i1), 0);
    EXPECT_EQ(SGN_Z_D(i2), 1);
    EXPECT_EQ(SGN_Z_D(i3), -1);
}

// Z-3
TEST_F(IntegerTest, MUL_ZM_Z_test)
{
    EXPECT_EQ(MUL_ZM_Z(i1), Integer(0));
    EXPECT_EQ(MUL_ZM_Z(i2), Integer(-25));
    EXPECT_EQ(MUL_ZM_Z(i3), Integer(231123));
}

// Z-4
TEST_F(IntegerTest, TRANS_N_Z_test)
{
    Natural n("213");
    EXPECT_EQ(TRANS_N_Z(n), Integer(213));
}

// Z-5
TEST_F(IntegerTest, TRANS_Z_N_test)
{
    EXPECT_EQ(TRANS_Z_N(Integer(10)), Natural(10));
    EXPECT_THROW(TRANS_Z_N(Integer(-5)), std::runtime_error);
}

// Z-6
TEST_F(IntegerTest, ADD_ZZ_Z_test)
{
    EXPECT_EQ(ADD_ZZ_Z(i1, i2), Integer(25));
    EXPECT_EQ(ADD_ZZ_Z(i1, i3), i3);
    EXPECT_EQ(ADD_ZZ_Z(i2, i3), Integer(-231098));
    EXPECT_EQ(ADD_ZZ_Z(i4, i3), Integer(54122329));
}

// Z-7
TEST_F(IntegerTest, SUB_ZZ_Z_test)
{
    EXPECT_EQ(SUB_ZZ_Z(i1, i2), Integer(-25));
    EXPECT_EQ(SUB_ZZ_Z(i1, i3), Integer(231123));
    EXPECT_EQ(SUB_ZZ_Z(i2, i3), Integer(231148));
    EXPECT_EQ(SUB_ZZ_Z(i3, i4), Integer(-54584575));
}

// Z-8
TEST_F(IntegerTest, MUL_ZZ_Z_test)
{
    EXPECT_EQ(MUL_ZZ_Z(i1, i2), Integer(0));
    EXPECT_EQ(MUL_ZZ_Z(i3, i1), Integer(0));
    EXPECT_EQ(MUL_ZZ_Z(i2, i3), Integer(-5778075));
    EXPECT_EQ(MUL_ZZ_Z(i3, i4), Integer("-12562332886596"));
}

// Z-9
TEST_F(IntegerTest, DIV_ZZ_Z_test)
{
    EXPECT_EQ(DIV_ZZ_Z(i2, i3), Integer(-1));
    EXPECT_THROW(DIV_ZZ_Z(i2, i1), std::domain_error); // Check division by zero
    EXPECT_EQ(DIV_ZZ_Z(i3, i2), Integer(-9245));
    EXPECT_EQ(DIV_ZZ_Z(i4, i3), Integer(-236));
}

// Z-10
TEST_F(IntegerTest, MOD_ZZ_Z_test)
{
    EXPECT_EQ(MOD_ZZ_Z(i2, i3), Integer(-231098));
    EXPECT_THROW(MOD_ZZ_Z(i2, i1), std::domain_error); // Check division by zero
    EXPECT_EQ(MOD_ZZ_Z(i3, i2), Integer(2));
    EXPECT_EQ(MOD_ZZ_Z(i4, i3), Integer(-191576));
}

// Z-additional-1
TEST_F(IntegerTest, MUL_Zk_Z_test)
{
    Natural k1(3);
    Natural k2(0);
    EXPECT_EQ(MUL_Zk_Z(i1, k1), Integer(0)); // 0 << 3 = 0
    EXPECT_EQ(MUL_Zk_Z(i2, k1), Integer(25000)); // 25 << 3 = 25000
    EXPECT_EQ(MUL_Zk_Z(i3, k1), Integer(-231123000));
    EXPECT_EQ(MUL_Zk_Z(i3, k2), Integer(-231123));
}

// Z-additional-2
TEST_F(IntegerTest, ADD_1Z_Z_test)
{
    EXPECT_EQ(ADD_1Z_Z(Integer(-1)), Integer(0));
    EXPECT_EQ(ADD_1Z_Z(i1), Integer(1));
    EXPECT_EQ(ADD_1Z_Z(i2), Integer(26));
    EXPECT_EQ(ADD_1Z_Z(i3), Integer(-231122));
    EXPECT_EQ(ADD_1Z_Z(i4), Integer(54353453));
}

// Z-additional-3
TEST_F(IntegerTest, SUB_1Z_Z_test)
{
    EXPECT_EQ(SUB_1Z_Z(Integer(1)), Integer(0));
    EXPECT_EQ(SUB_1Z_Z(i1), Integer(-1));
    EXPECT_EQ(SUB_1Z_Z(i2), Integer(24));
    EXPECT_EQ(SUB_1Z_Z(i3), Integer(-231124));
    EXPECT_EQ(SUB_1Z_Z(i4), Integer(54353451));
}

// Z-additional-4
TEST_F(IntegerTest, NZER_Z_B_test)
{
    EXPECT_EQ(NZER_Z_B(i1), false);
    EXPECT_EQ(NZER_Z_B(i2), true);
    EXPECT_EQ(NZER_Z_B(i3), true);
}

// Z-additional-5
TEST_F(IntegerTest, TRANS_Z_P_test)
{
    EXPECT_EQ(TRANS_Z_P(i1), Polynomial(0));
    EXPECT_EQ(TRANS_Z_P(i2), Polynomial(25));
    EXPECT_EQ(TRANS_Z_P(i3), Polynomial(-231123));
}

// Z-additional-6
TEST_F(IntegerTest, COM_ZZ_D_test)
{
    EXPECT_EQ(COM_ZZ_D(i1, i2), 1);
    EXPECT_EQ(COM_ZZ_D(i2, i3), 2);
    EXPECT_EQ(COM_ZZ_D(i4, i2), 2);
    EXPECT_EQ(COM_ZZ_D(i3, i3), 0);
}

// Z-additional-7
TEST_F(IntegerTest, GCF_ZZ_Z_test)
{
    EXPECT_EQ(GCF_ZZ_Z(i1, i2), Integer(25));
    EXPECT_EQ(GCF_ZZ_Z(i2, i3), Integer(1));
    EXPECT_EQ(GCF_ZZ_Z(i2, i4), Integer(1));
}

// Z-additional-8
TEST_F(IntegerTest, LCM_ZZ_Z_test)
{
    EXPECT_EQ(LCM_ZZ_Z(i1, i2), Integer(0));
    EXPECT_EQ(LCM_ZZ_Z(i2, i3), Integer("5778075"));
    EXPECT_EQ(LCM_ZZ_Z(i2, i4), Integer("1358836300"));
}

// -----------------------------------------
// Rational
// -----------------------------------------

class RationalTest : public ::testing::Test {
protected:
    Rational r1;
    Rational r2;
    Rational r3;
    Rational r4;
    Rational r5;
    
    void SetUp() override
    {
        r1 = Rational(0);
        r2 = Rational("2");
        r3 = Rational("6/5");
        r4 = Rational("-3");
        r5 = Rational("-13/10");
    }
};

// Q-1
TEST_F(RationalTest, RED_Q_Q_test)
{
    EXPECT_EQ(RED_Q_Q(Rational("0/5")), r1);
    EXPECT_EQ(RED_Q_Q(Rational("18/15")), r3);;
}

// Q-2
TEST_F(RationalTest, INT_Q_B_test)
{
    EXPECT_EQ(INT_Q_B(r1), true);
    EXPECT_EQ(INT_Q_B(r2), true);
    EXPECT_EQ(INT_Q_B(r3), false);
    EXPECT_EQ(INT_Q_B(r4), true);
    EXPECT_EQ(INT_Q_B(r5), false);
}

// Q-3
TEST_F(RationalTest, TRANS_Z_Q_test)
{
    EXPECT_EQ(TRANS_Z_Q(Integer(0)), r1);
    EXPECT_EQ(TRANS_Z_Q(Integer("2")), r2);
    EXPECT_EQ(TRANS_Z_Q(Integer("-3")), r4);
}

// Q-4
TEST_F(RationalTest, TRANS_Q_Z_test)
{
    EXPECT_EQ(TRANS_Q_Z(r1), Integer(0));
    EXPECT_EQ(TRANS_Q_Z(r2), Integer(2));
    EXPECT_THROW({ TRANS_Q_Z(r3); }, std::runtime_error);
    EXPECT_EQ(TRANS_Q_Z(r4), Integer(-3));
    EXPECT_THROW({ TRANS_Q_Z(r5); }, std::runtime_error);
}

// Q-5
TEST_F(RationalTest, ADD_QQ_Q_test)
{
    EXPECT_EQ(ADD_QQ_Q(r1, r2), Rational(2));
    EXPECT_EQ(ADD_QQ_Q(r1, r4), Rational(-3));
    EXPECT_EQ(ADD_QQ_Q(r1, r5), Rational("-13/10"));
    EXPECT_EQ(ADD_QQ_Q(r2, r3), Rational("16/5"));
    EXPECT_EQ(ADD_QQ_Q(r3, r5), Rational("-1/10"));
}

// Q-6
TEST_F(RationalTest, SUB_QQ_Q_test)
{
    EXPECT_EQ(SUB_QQ_Q(r1, r2), Rational(-2));
    EXPECT_EQ(SUB_QQ_Q(r1, r4), Rational(3));
    EXPECT_EQ(SUB_QQ_Q(r1, r5), Rational("13/10"));
    EXPECT_EQ(SUB_QQ_Q(r2, r3), Rational("4/5"));
    EXPECT_EQ(SUB_QQ_Q(r3, r5), Rational("5/2"));
}

// Q-7
TEST_F(RationalTest, MUL_QQ_Q_test)
{
    EXPECT_EQ(MUL_QQ_Q(r1, r2), Rational(0));
    EXPECT_EQ(MUL_QQ_Q(r1, r4), Rational(0));
    EXPECT_EQ(MUL_QQ_Q(r1, r5), Rational(0));
    EXPECT_EQ(MUL_QQ_Q(r2, r3), Rational("12/5"));
    EXPECT_EQ(MUL_QQ_Q(r3, r5), Rational("-39/25"));
}

// Q-8
TEST_F(RationalTest, DIV_QQ_Q_test)
{
    EXPECT_EQ(DIV_QQ_Q(r1, r2), Rational(0));
    EXPECT_EQ(DIV_QQ_Q(r1, r4), Rational(0));
    EXPECT_EQ(DIV_QQ_Q(r1, r5), Rational(0));
    EXPECT_THROW({ DIV_QQ_Q(r5, r1); }, std::domain_error);
    EXPECT_EQ(DIV_QQ_Q(r2, r3), Rational("5/3"));
    EXPECT_EQ(DIV_QQ_Q(r3, r5), Rational("-12/13"));
}

// Q-additional-1
TEST_F(RationalTest, NZER_Q_B_test)
{
    EXPECT_EQ(NZER_Q_B(r1), false);
    EXPECT_EQ(NZER_Q_B(r2), true);
    EXPECT_EQ(NZER_Q_B(r3), true);
    EXPECT_EQ(NZER_Q_B(r4), true);
    EXPECT_EQ(NZER_Q_B(r5), true);
}

// Q-additional-3
TEST_F(RationalTest, ABS_Q_Q_test)
{
    EXPECT_EQ(ABS_Q_Q(r1), Rational(0));
    EXPECT_EQ(ABS_Q_Q(r2), Rational(2));
    EXPECT_EQ(ABS_Q_Q(r3), Rational("6/5"));
    EXPECT_EQ(ABS_Q_Q(r4), Rational(3));
    EXPECT_EQ(ABS_Q_Q(r5), Rational("13/10"));
}

// Q-additional-4
TEST_F(RationalTest, SGN_Q_D_test)
{
    EXPECT_EQ(SGN_Q_D(r1), 0);
    EXPECT_EQ(SGN_Q_D(r2), 1);
    EXPECT_EQ(SGN_Q_D(r3), 1);
    EXPECT_EQ(SGN_Q_D(r4), -1);
    EXPECT_EQ(SGN_Q_D(r5), -1);
}

// Q-additional-5
TEST_F(RationalTest, MUL_QM_Q_test)
{
    EXPECT_EQ(MUL_QM_Q(r1), Rational(0));
    EXPECT_EQ(MUL_QM_Q(r2), Rational("-2"));
    EXPECT_EQ(MUL_QM_Q(r3), Rational("-6/5"));
    EXPECT_EQ(MUL_QM_Q(r4), Rational(3));
    EXPECT_EQ(MUL_QM_Q(r5), Rational("13/10"));
}

// Q-additional-6
TEST_F(RationalTest, TRANS_Q_N_test)
{
    EXPECT_EQ(TRANS_Q_N(r1), Natural(0));
    EXPECT_EQ(TRANS_Q_N(r2), Natural(2));
    EXPECT_THROW({ TRANS_Q_N(r3); }, std::runtime_error);
    EXPECT_THROW({ TRANS_Q_N(r4); }, std::runtime_error);
    EXPECT_THROW({ TRANS_Q_N(r5); }, std::runtime_error);
}

// Q-additional-7
TEST_F(RationalTest, TRANS_Q_P_test)
{
    EXPECT_EQ(TRANS_Q_P(r1), Polynomial(0));
    EXPECT_EQ(TRANS_Q_P(r2), Polynomial(2));
    EXPECT_EQ(TRANS_Q_P(r3), Polynomial("{6/5^0}"));
    EXPECT_EQ(TRANS_Q_P(r4), Polynomial("{-3^0}"));
    EXPECT_EQ(TRANS_Q_P(r5), Polynomial("{-13/10^0}"));
}

// Q-additional-8
TEST_F(RationalTest, COM_QQ_D_test)
{
    EXPECT_EQ(COM_QQ_D(r1, r2), 1);
    EXPECT_EQ(COM_QQ_D(r2, r1), 2);
    EXPECT_EQ(COM_QQ_D(r2, r2), 0);
    EXPECT_EQ(COM_QQ_D(r3, r4), 2);
    EXPECT_EQ(COM_QQ_D(r4, r5), 1);
    EXPECT_EQ(COM_QQ_D(r3, r5), 2);
}

TEST_F(RationalTest, INV_Q_Q_test)
{
    EXPECT_EQ(INV_Q_Q(r1), Rational("0"));
    EXPECT_EQ(INV_Q_Q(r2), Rational("1/2"));
    EXPECT_EQ(INV_Q_Q(r3), Rational("5/6"));
    EXPECT_EQ(INV_Q_Q(r4), Rational("-1/3"));
    EXPECT_EQ(INV_Q_Q(r5), Rational("-10/13"));
}

// -----------------------------------------
// Polynomial
// -----------------------------------------

class PolynomialTest : public ::testing::Test {
protected:
    Polynomial p1;
    Polynomial p2;
    Polynomial p3;
    Polynomial p4;
    Polynomial p5;
    Polynomial p6;
    
    void SetUp() override
    {
        p1 = Polynomial(0);
        p2 = Polynomial("{10^5}");
        p3 = Polynomial("{5^2;6/5^1;-100/9}");
        p4 = Polynomial("99");
        p5 = Polynomial("{1^2;-2^1;1}");
        p6 = Polynomial("{-1^2;2^1;-1}");
    }

};

// P-1
TEST_F(PolynomialTest, ADD_PP_P)
{
    EXPECT_EQ(ADD_PP_P(p1, p2), Polynomial("{10^5}"));
    EXPECT_EQ(ADD_PP_P(p2, p3), Polynomial("{10^5;5^2;6/5^1;-100/9}"));
    EXPECT_EQ(ADD_PP_P(p2, p4), Polynomial("{10^5;99}"));
    EXPECT_EQ(ADD_PP_P(p1, p4), Polynomial("99"));
    EXPECT_EQ(ADD_PP_P(p5, p6), Polynomial(0));
}

// P-2
TEST_F(PolynomialTest, SUB_PP_P)
{
    EXPECT_EQ(SUB_PP_P(p1, p2), Polynomial("{-10^5}"));
    EXPECT_EQ(SUB_PP_P(p2, p3), Polynomial("{10^5;-5^2;-6/5^1;100/9}"));
    EXPECT_EQ(SUB_PP_P(p2, p4), Polynomial("{10^5;-99}"));
    EXPECT_EQ(SUB_PP_P(p1, p4), Polynomial("-99"));
    EXPECT_EQ(SUB_PP_P(p5, p6), Polynomial("{2^2;-4^1;2}"));
}

// P-3
TEST_F(PolynomialTest, MUL_PQ_P)
{
    EXPECT_EQ(MUL_PQ_P(p1, Rational("1232135435/324")), Polynomial("0"));
    EXPECT_EQ(MUL_PQ_P(p2, Rational("-45305/12423423")),
              Polynomial("{-453050/12423423^5}"));
    EXPECT_EQ(MUL_PQ_P(p3, Rational("4342")),
              Polynomial("{21710^2;26052/5^1;-434200/9}"));
    EXPECT_EQ(MUL_PQ_P(p4, Rational(0)), Polynomial(0));
    EXPECT_EQ(MUL_PQ_P(p6, Rational("9012310543503459")),
              Polynomial("{-9012310543503459^2;18024621087006918^1;-9012310543503459}"));
}

// P-4
TEST_F(PolynomialTest, MUL_Pxk_P)
{
    Natural k1 = Natural(0);
    Natural k2 = Natural(1);
    Natural k3 = Natural(5);
    Natural k4 = Natural(10);
    Natural k5 = Natural(100);
    
    EXPECT_EQ(MUL_Pxk_P(p1, k1), Polynomial("0"));
    EXPECT_EQ(MUL_Pxk_P(p1, k2), Polynomial("0"));
    EXPECT_EQ(MUL_Pxk_P(p3, k3), Polynomial("{5^7;6/5^6;-100/9^5}"));
    EXPECT_EQ(MUL_Pxk_P(p4, k5), Polynomial("{99^100}"));
    EXPECT_EQ(MUL_Pxk_P(p5, k5), Polynomial("{1^102;-2^101;1^100}"));
}

// P-5
TEST_F(PolynomialTest, LED_P_Q)
{
    EXPECT_EQ(LED_P_Q(p1), Rational(0));
    EXPECT_EQ(LED_P_Q(p2), Rational(10));
    EXPECT_EQ(LED_P_Q(p3), Rational("5"));
    EXPECT_EQ(LED_P_Q(p4), Rational("99"));
    EXPECT_EQ(LED_P_Q(p5), Rational("1"));
}

// P-6
TEST_F(PolynomialTest, DEG_P_N)
{
    EXPECT_EQ(DEG_P_N(p1), Natural(0));
    EXPECT_EQ(DEG_P_N(p2), Natural(5));
    EXPECT_EQ(DEG_P_N(p3), Natural(2));
    EXPECT_EQ(DEG_P_N(Polynomial("{5^6;6^1000;2^10;5^3}")), Natural(1000));
    EXPECT_EQ(DEG_P_N(p4), Natural(0));
    EXPECT_EQ(DEG_P_N(p5), Natural(2));
}

// P-7
TEST_F(PolynomialTest, FAC_P_Q)
{
    EXPECT_EQ(FAC_P_Q(p1), Rational(0));
    EXPECT_EQ(FAC_P_Q(p2), Rational("10"));
    EXPECT_EQ(FAC_P_Q(p3), Rational("1/45"));
    EXPECT_EQ(FAC_P_Q(p4), Rational("99"));
    EXPECT_EQ(FAC_P_Q(p5), Rational("1"));
    EXPECT_EQ(FAC_P_Q(Polynomial("{3/2^4;-5/4^3;7/3^2;-9/2^1;1/6}")),
              Rational("1/12"));
}

// P-8
TEST_F(PolynomialTest, MUL_PP_P)
{
    EXPECT_EQ(MUL_PP_P(p1, p2), Polynomial("0"));
    EXPECT_EQ(MUL_PP_P(p2, p3), Polynomial("{50^7;12^6;-1000/9^5}"));
    EXPECT_EQ(MUL_PP_P(p2, p4), Polynomial("{990^5}"));
    EXPECT_EQ(MUL_PP_P(p4, p1), Polynomial("0"));
    EXPECT_EQ(MUL_PP_P(p5, p6), Polynomial("{-1^4;4^3;-6^2;4^1;-1}"));
}

// P-9
TEST_F(PolynomialTest, DIV_PP_P) 
{
    EXPECT_THROW({ DIV_PP_P(p2, p1); }, std::domain_error);
    EXPECT_EQ(DIV_PP_P(p2, p3), Polynomial("{2^3;-12/25^2;25648/5625^1;-101296/46875}"));
    EXPECT_EQ(DIV_PP_P(p3, p5), Polynomial("5"));
    EXPECT_EQ(DIV_PP_P(p1, p3), Polynomial("0"));
    EXPECT_EQ(DIV_PP_P(p2, p2), Polynomial(1));
    EXPECT_EQ(DIV_PP_P(Polynomial("{2^3;-3^2;7^1;-52}"), Polynomial("{-4^2;5^1;8}")),
              Polynomial("{-1/2^1;1/8}"));
}

// P-10
TEST_F(PolynomialTest, MOD_PP_P)
{
    EXPECT_THROW({ MOD_PP_P(p2, p1); }, std::domain_error);
    EXPECT_EQ(MOD_PP_P(p2, p3), Polynomial("{337009952/6328125^1;-405184/16875}"));
    EXPECT_EQ(MOD_PP_P(p3, p5), Polynomial("{56/5^1;-145/9}"));
    EXPECT_EQ(MOD_PP_P(p3, p2), p3);
    EXPECT_EQ(MOD_PP_P(Polynomial("{2^3;-3^2;7^1;-52}"), Polynomial("{-4^2;5^1;8}")),
              Polynomial("{83/8^1;-53}"));
}

// P-11
TEST_F(PolynomialTest, GCF_PP_P)
{
    EXPECT_EQ(GCF_PP_P(p1, p2), Polynomial("{1^5}"));
    EXPECT_EQ(GCF_PP_P(p2, p2), Polynomial("{1^5}"));
    EXPECT_EQ(GCF_PP_P(p3, p5), Polynomial("1"));
    EXPECT_EQ(GCF_PP_P(p5, p6), Polynomial("{1^2;-2^1;1}"));
    EXPECT_EQ(GCF_PP_P(p4, p5), Polynomial("1"));
}

// P-12
TEST_F(PolynomialTest, DER_P_P)
{
    EXPECT_EQ(DER_P_P(p1), Polynomial(0));
    EXPECT_EQ(DER_P_P(p2), Polynomial("{50^4}"));
    EXPECT_EQ(DER_P_P(p3), Polynomial("{10^1;6/5}"));
    EXPECT_EQ(DER_P_P(p4), Polynomial("0"));
    EXPECT_EQ(DER_P_P(p5), Polynomial("{2^1;-2}"));
    EXPECT_EQ(DER_P_P(p6), Polynomial("{-2^1;2}"));
}

// P-13
TEST_F(PolynomialTest, NMR_P_P)
{
    Polynomial base1 = Polynomial("{1^1;-1}");
    Polynomial base2 = Polynomial("{1^1;1}");
    
    EXPECT_EQ(NMR_P_P(base1 * base2), Polynomial("{1^2;-1}"));
    EXPECT_EQ(NMR_P_P(base1 * base1 * base1 * base2),
              base1 * base2);
    EXPECT_EQ(NMR_P_P(base1 * base2 * base2 * base2 * base2),
              base1 * base2);
    EXPECT_EQ(NMR_P_P(base1 * base2 * base1 * base2 * base2),
              base1 * base2);

    // Expected result
    Polynomial nmred = p3 * p4 * Polynomial("{1^1;-1}");
    nmred *= nmred.msc().get_inversed();
    
    EXPECT_EQ(NMR_P_P(p3 * p3 * p4 * p5 * p6), nmred);
}

// P-additional-1
TEST_F(PolynomialTest, NZER_P_B)
{
    EXPECT_EQ(NZER_P_B(p1), false);
    EXPECT_EQ(NZER_P_B(p2), true);
    EXPECT_EQ(NZER_P_B(p3), true);
    EXPECT_EQ(NZER_P_B(p4), true);
    EXPECT_EQ(NZER_P_B(p5), true);
}

// P-additional-2
TEST_F(PolynomialTest, INT_P_B)
{
    EXPECT_EQ(INT_P_B(p1), true);
    EXPECT_EQ(INT_P_B(p2), false);
    EXPECT_EQ(INT_P_B(p3), false);
    EXPECT_EQ(INT_P_B(p4), true);
    EXPECT_EQ(INT_P_B(p5), false);
    EXPECT_EQ(INT_P_B(p6), false);
}
