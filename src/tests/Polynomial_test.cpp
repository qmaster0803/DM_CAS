// Author: Komarov Daniil 3381

#include <gtest/gtest.h>
#include "../include/Polynomial.h"

// Test for constructor from an integer (including zero and negative integers)
TEST(PolynomialTest, IntConstructor) {
    Polynomial p1(5); // 5
    EXPECT_EQ(p1.msc(), Rational(5)); // Leading coefficient should be 5
    EXPECT_EQ(p1.deg(), Natural(0)); // Degree should be 0

    Polynomial p2(0); // 0
    EXPECT_TRUE(p2.is_zero()); // Polynomial should be zero

    Polynomial p3(-5); // -5
    EXPECT_EQ(p3.msc(), Rational(-5)); // Leading coefficient should be -5
    EXPECT_EQ(p3.deg(), Natural(0)); // Degree should be 0
}

// Test for constructor from a string (including complex cases, fractions, and constant terms)
TEST(PolynomialTest, StringConstructor) {
    Polynomial p1("{3^2;5^1;2^0}"); // 3x^2 + 5x + 2
    EXPECT_EQ(p1.msc(), Rational(3)); // Leading coefficient should be 3
    EXPECT_EQ(p1.deg(), Natural(2)); // Degree should be 2
    EXPECT_EQ(static_cast<std::string>(p1), "{3^2;5^1;2^0}");

    Polynomial p2("{1/2^3;3/4^1;1^0}"); // (1/2)x^3 + (3/4)x + 1
    EXPECT_EQ(p2.msc(), Rational("1/2")); // Leading coefficient should be 1/2
    EXPECT_EQ(p2.deg(), Natural(3)); // Degree should be 3

    Polynomial p3("{3/2^1;1^0}"); // (3/2)x + 1
    EXPECT_EQ(p3.msc(), Rational("3/2")); // Leading coefficient should be 3/2
    EXPECT_EQ(p3.deg(), Natural(1)); // Degree should be 1

    Polynomial p4("{5^0}"); // 5 (constant)
    EXPECT_EQ(p4.msc(), Rational(5)); // Leading coefficient should be 5
    EXPECT_EQ(p4.deg(), Natural(0)); // Degree should be 0
}

// Test for an empty string or an invalid string in the constructor
TEST(PolynomialTest, ConstructorFromStringEmpty) {
    Polynomial p(""); // Empty string
    EXPECT_TRUE(p.is_zero()); // Polynomial should be zero
}

// Test for multiplication by x^k
TEST(PolynomialTest, MulByXk) {
    Polynomial p1("{2^1;3^0}"); // 2x + 3
    Natural k(2);
    p1.mul_by_xk(k); // Multiply by x^2, expecting 2x^3 + 3x^2
    EXPECT_EQ(static_cast<std::string>(p1), "{2^3;3^2}");
    
    Polynomial p2("{0^1;1^0}"); // x
    Natural k1(3);
    p2.mul_by_xk(k1); // Multiply by x^3, expecting x^3
    EXPECT_EQ(static_cast<std::string>(p2), "{1^3}");

    Polynomial p3("{0^0}"); // 0
    p3.mul_by_xk(Natural(10)); // Multiply by x^10, expecting 0
    EXPECT_EQ(static_cast<std::string>(p3), "0");
}

// Test for derivative of a polynomial
TEST(PolynomialTest, Derivative) {
    Polynomial p("{3^2;5^1;2^0}"); // 3x^2 + 5x + 2
    Polynomial derivative = p.derivative(); // 6x + 5
    EXPECT_EQ(static_cast<std::string>(derivative), "{6^1;5^0}");

    Polynomial p1("{5^2;0^1}"); // 5x^2
    EXPECT_EQ(static_cast<std::string>(p1.derivative()), "{10^1}"); // Derivative: 10x

    Polynomial p2("{3^0}"); // Constant
    EXPECT_TRUE(p2.derivative().is_zero()); // Derivative of a constant should be zero
}

// Test for polynomial addition
TEST(PolynomialTest, Add) {
    Polynomial p1("{3^2;2^0}"); // 3x^2 + 2
    Polynomial p2("{1^2;1^0}"); // x^2 + 1
    Polynomial sum = p1 + p2; // (3x^2 + 2) + (x^2 + 1) = 4x^2 + 3
    EXPECT_EQ(static_cast<std::string>(sum), "{4^2;3^0}");
    
    Polynomial p3("{1^2}"); // x^2
    Polynomial p4("{1^2}"); // x^2
    sum = p3 + p4; // x^2 + x^2 = 2x^2
    EXPECT_EQ(static_cast<std::string>(sum), "{2^2}");
}

// Test for polynomial multiplication
TEST(PolynomialTest, Multiply) {
    Polynomial p1("{3^2;5^1}"); // 3x^2 + 5x
    Polynomial p2("{2^1;1^0}"); // 2x + 1
    Polynomial product = p1 * p2; // (3x^2 + 5x) * (2x + 1) = 6x^3 + 13x^2 + 5x
    EXPECT_EQ(static_cast<std::string>(product), "{6^3;13^2;5^1}");

    Polynomial p3("{0^1}"); // 0
    Polynomial p4("{1^0}"); // 1
    product = p3 * p4; // 0 * 1 = 0
    EXPECT_TRUE(product.is_zero());
}

// // Test for polynomial division
// TEST(PolynomialTest, Divide) {
//     Polynomial p1("{3^2;5^1}"); // 3x^2 + 5x
//     Polynomial p2("{x^1;1^0}"); // x + 1
//     Polynomial quotient = p1 / p2; // (3x^2 + 5x) / (x + 1) = 3x + 2
//     EXPECT_EQ(static_cast<std::string>(quotient), "{3^1;2^0}");

//     Polynomial p3("{1^2;0^1;0^0}"); // x^2
//     Polynomial p4("{1^1;1^0}"); // x + 1
//     quotient = p3 / p4; // x^2 / (x + 1) = x - 1
//     EXPECT_EQ(static_cast<std::string>(quotient), "{1^1;-1^0}");
// }

// Test for equality of polynomials
TEST(PolynomialTest, Equality) {
    Polynomial p1("{3^2;2^1;1^0}"); // 3x^2 + 2x + 1
    Polynomial p2("{3^2;2^1;1^0}"); // 3x^2 + 2x + 1
    EXPECT_TRUE(p1 == p2); // Polynomials should be equal

    Polynomial p3("{2^2;5^0}"); // 2x^2 + 5
    Polynomial p4("{2^2;6^0}"); // 2x^2 + 6
    EXPECT_FALSE(p3 == p4); // Polynomials should not be equal
}

// Test for checking if a polynomial is zero
TEST(PolynomialTest, IsZero) {
    Polynomial p("{0^2;0^1;0^0}"); // 0
    EXPECT_TRUE(p.is_zero()); // Polynomial should be zero
}

// Test for checking if a polynomial is an integer
TEST(PolynomialTest, IsInteger) {
    Polynomial p1("{2^2;5^0}"); // 2x^2 + 5
    EXPECT_FALSE(p1.is_integer()); // Polynomial should not be an integer
    
    Polynomial p2("{0^2;5^0}"); // 0x^2 + 5
    EXPECT_TRUE(p2.is_integer()); // Polynomial should be an integer
}

// Test for most significant coefficient (msc)
TEST(PolynomialTest, Msc) {
    Polynomial p("{3^2;5^1;2^0}"); // 3x^2 + 5x + 2
    EXPECT_EQ(p.msc(), Rational(3)); // Most significant coefficient should be 3

    Polynomial p2("{0^3;1^1;2^0}"); // x + 2
    EXPECT_EQ(p2.msc(), Rational(1)); // Most significant coefficient should be 1
}

// Test for degree of a polynomial
TEST(PolynomialTest, Degree) {
    Polynomial p("{3^2;5^1;2^0}"); // 3x^2 + 5x + 2
    EXPECT_EQ(p.deg(), Natural(2)); // Degree should be 2

    Polynomial p2("{5^0}"); // 5
    EXPECT_EQ(p2.deg(), Natural(0)); // Degree should be 0
}

