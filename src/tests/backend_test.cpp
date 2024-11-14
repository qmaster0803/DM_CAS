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
    EXPECT_EQ(ADD_1N_N(n1), Natural("432432423050394854398503453083052346"));
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
    EXPECT_THROW({ SUB_NN_N(n1, n2); }, std::invalid_argument); // Should throw for n1 < n2
}

// N-6
TEST_F(NaturalTest, MUL_ND_N_test)
{
    EXPECT_EQ(MUL_ND_N(n1, 2), Natural("864864846100789708797006906166104690")); 
    EXPECT_THROW({ MUL_ND_N(n1, 10); }, std::invalid_argument); // Should throw for d > 9
}

// N-7
TEST_F(NaturalTest, MUL_Nk_N_test)
{
    EXPECT_EQ(MUL_Nk_N(n1, n2), n1 << n2);
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
    EXPECT_EQ(DIV_NN_Dk(n2, n1, n3), 8);
}

// N-11
TEST_F(NaturalTest, DIV_NN_N_test)
{
    EXPECT_EQ(DIV_NN_N(n2, n1), Natural("86486484610078970879700690616610469"));
    EXPECT_THROW(DIV_NN_N(n1, n2), std::invalid_argument); // Should throw for n1 < n2
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
    EXPECT_EQ(LCM_NN_N(n4, n4), n2);
    EXPECT_EQ(LCM_NN_N(n2, n1), n2);
}

// N-additional-1
TEST_F(NaturalTest, SUB_1N_N_test)
{
    EXPECT_EQ(SUB_1N_N(n1), Natural(4)); // 5 - 1 = 4
    EXPECT_EQ(SUB_1N_N(n2), Natural("432432423050394854398503453083052334"));
    EXPECT_THROW({ SUB_1N_N(n3); }, std::out_of_range); // 5 - 1 = 4
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
    EXPECT_THROW(TRANS_Z_N(Integer(-5)), std::invalid_argument);
}

// Z-6
TEST_F(IntegerTest, ADD_ZZ_Z_test)
{
    EXPECT_EQ(ADD_ZZ_Z(i1, i2), Integer(25));
    EXPECT_EQ(ADD_ZZ_Z(i1, i3), Integer(-231123));
    EXPECT_EQ(ADD_ZZ_Z(i2, i3), Integer(-231098));
    EXPECT_EQ(ADD_ZZ_Z(i2, i3), Integer(54122329));
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
    EXPECT_EQ(DIV_ZZ_Z(i2, i3), Integer(0));
    EXPECT_THROW(DIV_ZZ_Z(i2, i1), std::domain_error); // Check division by zero
    EXPECT_EQ(DIV_ZZ_Z(i3, i2), Integer(-1));
    EXPECT_EQ(DIV_ZZ_Z(i4, i3), Integer(-236));
}

// Z-10
TEST_F(IntegerTest, MOD_ZZ_Z_test)
{
    EXPECT_EQ(MOD_ZZ_Z(i2, i3), Integer(-231098));
    EXPECT_THROW(MOD_ZZ_Z(i2, i1), std::domain_error); // Check division by zero
    EXPECT_EQ(MOD_ZZ_Z(i3, i2), Integer(-1));
    EXPECT_EQ(MOD_ZZ_Z(i4, i3), Integer(54122329));
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
    EXPECT_EQ(ADD_1Z_Z(Integer(1)), Integer(0));
    EXPECT_EQ(ADD_1Z_Z(i1), Integer(-1));
    EXPECT_EQ(ADD_1Z_Z(i2), Integer(24));
    EXPECT_EQ(ADD_1Z_Z(i3), Integer(-231124));
    EXPECT_EQ(ADD_1Z_Z(i4), Integer(54353451));
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
    EXPECT_EQ(GCF_ZZ_Z(i2, i4), Integer(4));
}

// Z-additional-8
TEST_F(IntegerTest, LCM_ZZ_Z_test)
{
    EXPECT_EQ(GCF_ZZ_Z(i1, i2), Integer(0));
    EXPECT_EQ(GCF_ZZ_Z(i2, i3), Integer("12562332886596"));
    EXPECT_EQ(LCM_ZZ_Z(i2, i4), Integer(326120712));
}

////////////////////////////
// TODO: all below
///////////////////////////

// -----------------------------------------
// Rational
// -----------------------------------------

class RationalTest : public ::testing::Test {
protected:
    Rational r1;
    Rational r2("2");
    Rational r3("6/5");
    Rational r4(-3);
    Rational r5;
    
    void SetUp() override {}
};

// Q-1
TEST_F(RationalTest, RED_Q_Q_test)
{
    Rational r(Natural(4), Integer(8)); // Assuming Rational constructor takes numerator and denominator
    Rational expected(1, 2); // Expected reduced rational
    EXPECT_EQ(RED_Q_Q(r), expected);
}

// Q-2
TEST_F(RationalTest, INT_Q_B_test)
{
    Rational r1(5, 1); // Integer as rational
    Rational r2(3, 2); // Non-integer rational
    EXPECT_TRUE(INT_Q_B(r1));
    EXPECT_FALSE(INT_Q_B(r2));
}

// Q-3
TEST_F(RationalTest, TRANS_Z_Q_test)
{
    Integer i(7); // Assuming an Integer constructor
    Rational expected(7, 1);
    EXPECT_EQ(TRANS_Z_Q(i), expected);
}

// Q-4
TEST_F(RationalTest, TRANS_Q_Z_test)
{
    Rational r(3, 1);
    Integer expected(3);
    EXPECT_EQ(TRANS_Q_Z(r), expected);
}

// Q-5
TEST_F(RationalTest, ADD_QQ_Q_test)
{
    Rational r1(1, 3);
    Rational r2(2, 3);
    Rational expected(1, 1); // 1
    EXPECT_EQ(ADD_QQ_Q(r1, r2), expected);
}

// Q-6
TEST_F(RationalTest, SUB_QQ_Q_test)
{
    Rational r1(5, 6);
    Rational r2(1, 6);
    Rational expected(2, 3);
    EXPECT_EQ(SUB_QQ_Q(r1, r2), expected);
}

// Q-7
TEST_F(RationalTest, MUL_QQ_Q_test)
{
    Rational r1(2, 3);
    Rational r2(3, 4);
    Rational expected(1, 2);
    EXPECT_EQ(MUL_QQ_Q(r1, r2), expected);
}

// Q-8
TEST_F(RationalTest, DIV_QQ_Q_test)
{
    Rational r1(1, 2);
    Rational r2(2, 3);
    Rational expected(3, 4);
    EXPECT_EQ(DIV_QQ_Q(r1, r2), expected);
}

// Q-additional-1
TEST_F(RationalTest, NZER_Q_B_test)
{
    Rational r1(0, 1);
    Rational r2(1, 1);
    EXPECT_TRUE(NZER_Q_B(r1));
    EXPECT_FALSE(NZER_Q_B(r2));
}

// Q-additional-3
TEST_F(RationalTest, ABS_Q_Q_test)
{
    Rational r(-3, 4);
    Rational expected(3, 4);
    EXPECT_EQ(ABS_Q_Q(r), expected);
}

// Q-additional-4
TEST_F(RationalTest, SGN_Q_D_test)
{
    Rational r1(3, 5);
    Rational r2(-8, 3);
    Rational r3(0, 1);
    EXPECT_EQ(SGN_Q_D(r1), 1);
    EXPECT_EQ(SGN_Q_D(r2), -1);
    EXPECT_EQ(SGN_Q_D(r3), 0);
}

// Q-additional-5
TEST_F(RationalTest, MUL_QM_Q_test)
{
    Rational r(3, 4);
    Rational expected(-3, 4);
    EXPECT_EQ(MUL_QM_Q(r), expected);
}

// Q-additional-6
TEST_F(RationalTest, TRANS_Q_N_test)
{
    Rational r(5, 1);
    Natural expected(5);
    EXPECT_EQ(TRANS_Q_N(r), expected);
}

// Q-additional-7
TEST_F(RationalTest, TRANS_Q_P_test)
{
    Rational r(1, 1);
    Polynomial expected(r);
    EXPECT_EQ(TRANS_Q_P(r), expected);
}

// Q-additional-8
TEST_F(RationalTest, COM_QQ_D_test)
{
    Rational r1(1, 2);
    Rational r2(3, 4);
    Rational r3(3, 4);
    EXPECT_EQ(COM_QQ_D(r1, r2), 1); // r1 < r2
    EXPECT_EQ(COM_QQ_D(r2, r1), 2); // r2 > r1
    EXPECT_EQ(COM_QQ_D(r2, r3), 0); // r2 == r3
}

// -----------------------------------------
// Polynomial
// -----------------------------------------

class PolynomialTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Any necessary setup can be done here
    }

};

TEST_F(PolynomialTest, ADD_PP_P)
{
    Polynomial p1({1, 2, 3}); // Represents 1 + 2x + 3x^2
    Polynomial p2({4, 5});    // Represents 4 + 5x

    Polynomial result = ADD_PP_P(p1, p2);
    Polynomial expected({5, 7, 3}); // Expected result: 5 + 7x + 3x^2

    EXPECT_EQ(result, expected);
}

TEST_F(PolynomialTest, SUB_PP_P)
{
    Polynomial p1({5, 5}); // Represents 5 + 5x
    Polynomial p2({1, 2, 3}); // Represents 1 + 2x + 3x^2

    Polynomial result = SUB_PP_P(p1, p2);
    Polynomial expected({4, 3, -3}); // Expected result: 4 + 3x - 3x^2

    EXPECT_EQ(result, expected);
}

TEST_F(PolynomialTest, MUL_PQ_P)
{
    Polynomial p({2, 3}); // Represents 2 + 3x
    Rational r(3, 1);     // Represents 3

    Polynomial result = MUL_PQ_P(p, r);
    Polynomial expected({6, 9}); // Expected result: 6 + 9x

    EXPECT_EQ(result, expected);
}

TEST_F(PolynomialTest, MUL_Pxk_P)
{
    Polynomial p({1, 2}); // Represents 1 + 2x
    Natural k(2);         // Represents multiplying by x^2

    Polynomial result = MUL_Pxk_P(p, k);
    Polynomial expected({0, 0, 1, 2}); // Expected result: 1 + 2x shifted by 2 (0 + 0x + 1x^2 + 2x^3)

    EXPECT_EQ(result, expected);
}

TEST_F(PolynomialTest, LED_P_Q)
{
    Polynomial p({1, -2, 1}); // Represents x^2 - 2x + 1

    Rational result = LED_P_Q(p);
    Rational expected(1, 1); // Leading coefficient is 1

    EXPECT_EQ(result, expected);
}

TEST_F(PolynomialTest, DEG_P_N)
{
    Polynomial p({0, 5, 0, 2}); // Represents 2x^3 + 5x

    Natural result = DEG_P_N(p);
    Natural expected(3); // Degree is 3

    EXPECT_EQ(result, expected);
}

TEST_F(PolynomialTest, FAC_P_Q)
{
    Polynomial p({1, 0, -1}); // Represents x^2 - 1

    Rational result = FAC_P_Q(p);
    Rational expected(1, 1); // Factorial of the polynomial (could depend on implementation)

    EXPECT_EQ(result, expected);
}

TEST_F(PolynomialTest, MUL_PP_P)
{
    Polynomial p1({1, 1}); // 1 + x
    Polynomial p2({1, 2}); // 1 + 2x

    Polynomial result = MUL_PP_P(p1, p2);
    Polynomial expected({1, 3, 2}); // (1 + x)(1 + 2x) = 1 + 3x + 2x^2

    EXPECT_EQ(result, expected);
}

TEST_F(PolynomialTest, DIV_PP_P) 
{
    Polynomial p1({1, 0, -2}); // x^2 - 2
    Polynomial p2({1, -1});    // x - 1

    Polynomial result = DIV_PP_P(p1, p2);
    Polynomial expected({1, 1}); // Result of division (may depend on implementation)

    EXPECT_EQ(result, expected);
}

TEST_F(PolynomialTest, MOD_PP_P)
{
    Polynomial p1({1, 0, -2}); // x^2 - 2
    Polynomial p2({1, -1});    // x - 1

    Polynomial result = MOD_PP_P(p1, p2);
    Polynomial expected({1}); // Remainder of the division

    EXPECT_EQ(result, expected);
}

TEST_F(PolynomialTest, GCF_PP_P)
{
    Polynomial p1({1, 2, 3}); // Represents 1 + 2x + 3x^2
    Polynomial p2({3, 6});    // Represents 3 + 6x

    Polynomial result = GCF_PP_P(p1, p2);
    Polynomial expected({3}); // Greatest common factor

    EXPECT_EQ(result, expected);
}

TEST_F(PolynomialTest, DER_P_P)
{
    Polynomial p({3, 4, 5}); // Represents 3 + 4x + 5x^2

    Polynomial result = DER_P_P(p);
    Polynomial expected({4, 10}); // Derivative: 4 + 10x

    EXPECT_EQ(result, expected);
}

TEST_F(PolynomialTest, NMR_P_P)
{
    Polynomial p({1, 2}); // Represents 1 + 2x

    Polynomial result = NMR_P_P(p);
    Polynomial expected({1}); // Normalized polynomial (could depend on implementation)

    EXPECT_EQ(result, expected);
}

TEST_F(PolynomialTest, NZER_P_B)
{
    Polynomial p({0, 0}); // Zero polynomial

    bool result = NZER_P_B(p);
    EXPECT_TRUE(result); // Should return true for zero polynomial
}

TEST_F(PolynomialTest, INT_P_B)
{
    Polynomial p({1, 0}); // Represents 1

    bool result = INT_P_B(p);
    EXPECT_TRUE(result); // Should return true for integer polynomial
}
