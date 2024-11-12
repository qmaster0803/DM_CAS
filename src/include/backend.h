// Author: Ivanov Artyom 3381

#pragma once

#include <stdexcept>

#include "Natural.h"
#include "Integer.h"
#include "Rational.h"
#include "Polynomial.h"

#define E_NOT_DIGIT "d must be digit, not a number!"

namespace backend {

// all functions written in .h because of their small volume

// --------------------------------------------
// Natural
// --------------------------------------------

// N-1
int COM_NN_D(Natural n1, Natural n2)
{
    if (n1 > n2)
        return 2;
    else if (n1 < n2)
        return 1;
    else
        return 0;
}

// N-2
bool NZER_N_B(Natural n) { return !n.is_zero(); }

// N-3
Natural ADD_1N_N(Natural n) { return ++n; }

// N-4
Natural ADD_NN_N(Natural n1, Natural n2) { return n1 + n2; }

// N-5
Natural SUB_NN_N(Natural n1, Natural n2) { return n1 - n2; };

// N-6
Natural MUL_ND_N(Natural n1, int d)
{
    if (d > 9)
        throw std::invalid_argument(E_NOT_DIGIT);
        
    return n1 * Natural(d);
}

// N-7
Natural MUL_Nk_N(Natural n, Natural k) { return n << k; }

// N-8
Natural MUL_NN_N(Natural n1, Natural n2) { return n1 * n2; }

// N-9
Natural SUB_NDN_N(Natural n1, uint8_t d, Natural n2) 
{
    if (d > 9)
        throw std::invalid_argument(E_NOT_DIGIT);
    
    return n1 - Natural(d) * n2;
}

// N-10
int DIV_NN_Dk(Natural n1, Natural n2, Natural k)
    { return n1.first_div_digit(n2 << k); }

// N-11
Natural DIV_NN_N(Natural n1, Natural n2) { return n1 / n2; }

// N-12
Natural MOD_NN_N(Natural n1, Natural n2) { return n1 % n2; }

// N-13
Natural GCF_NN_N(Natural n1, Natural n2) { return n1.gcd(n2); }

// N-14
Natural LCM_NN_N(Natural n1, Natural n2) { return n1.lcm(n2); }

// N-additional-1
Natural SUB_1N_N(Natural i) { return --i; }

// N-additional-2
Rational TRANS_N_Q(Natural n) { return Rational(n); }

// N-additional-3
Polynomial TRANS_N_P(Natural n) { return Polynomial(n); }

// --------------------------------------
// INTEGER
// --------------------------------------

// Z-1
Integer ABS_Z_Z(Integer i) { return i.abs(); }

// Z-2
int SGN_Z_D(Integer i)
{
    if (i.is_zero())
        return 0;
    else if (i.is_neg())
        return -1;
    else
        return 1;
}

// Z-3
Integer MUL_ZM_Z(Integer i)
{
    i.neg();
    return i;
}

// Z-4
Integer TRANS_N_Z(Natural n) { return Integer(n); }

// Z-5
Natural TRANS_Z_N(Integer i) { return Natural(i); }

// Z-6
Integer ADD_ZZ_Z(Integer i1, Integer i2) { return i1 + i2; }

// Z-7
Integer SUB_ZZ_Z(Integer i1, Integer i2) { return i1 - i2; }

// Z-8
Integer MUL_ZZ_Z(Integer i1, Integer i2) { return i1 * i2; }

// Z-9
Integer DIV_ZZ_Z(Integer i1, Integer i2) { return i1 / i2; }

// Z-10
Integer MOD_ZZ_Z(Integer i1, Integer i2) { return i1 % i2; }

// Z-additional-1
Integer MUL_Zk_Z(Integer i, Natural k) { return i << k; }

// Z-additional-2
Integer ADD_1Z_Z(Integer i) { return ++i; }

// Z-additional-3
Integer SUB_1Z_Z(Integer i) { return ++i; }

// Z-additional-4
bool NZER_Z_B(Integer i) { return !i.is_zero(); }

// Z-additional-5
Polynomial TRANS_Z_P(Integer i) { return Polynomial(Rational(i)); }

// Z-additional-6
int COM_ZZ_D(Integer i1, Integer i2)
{
    if (i1 > i2)
        return 2;
    else if (i1 < i2)
        return 1;
    else
        return 0;
}

// Z-additional-7
Integer GCF_ZZ_Z(const Integer &i1, const Integer &i2) { return i1.gcd(i2); }

// Z-additional-8
Integer LCM_ZZ_Z(const Integer &i1, const Integer &i2) { return i1.lcm(i2); }

// --------------------------------------
// RATIONAL
// --------------------------------------

// Q-1
Rational RED_Q_Q(Rational r)
    { r.reduct(); return r; }

// Q-2
bool INT_Q_B(Rational r) { return r.is_integer(); }

// Q-3
Rational TRANS_Z_Q(Integer i) { return Rational(i); }

// Q-4
Integer TRANS_Q_Z(Rational r) { return Integer(r); }

// Q-5
Rational ADD_QQ_Q(Rational r1, Rational r2) { return r1 + r2; }

// Q-6
Rational SUB_QQ_Q(Rational r1, Rational r2) { return r1 - r2; }

// Q-7
Rational MUL_QQ_Q(Rational r1, Rational r2) { return r1 * r2; }

// Q-8
Rational DIV_QQ_Q(Rational r1, Rational r2) { return r1 / r2; }

// Q-additional-1
bool NZER_Q_B(Rational r) { return !r.is_zero(); }

// Q-additional-3
Rational ABS_Q_Q(Rational r) { return r.abs(); }

// Q-additional-4
int SGN_Q_D(Rational r)
{
    if (r.is_zero())
        return 0;
    else if (r.is_neg())
        return -1;
    else
        return 1;
}

// Q-additional-5
Rational MUL_QM_Q(Rational r) { return r.get_neg(); }

// Q-additional-6
Natural TRANS_Q_N(Rational r)
    { return static_cast<Natural>(static_cast<Integer>(r)); }

// Q-additional-7
Polynomial TRANS_Q_P(Rational r) { return Polynomial(r); }

// Q-additional-8
int COM_QQ_D(const Rational &r1, const Rational &r2)
{
    if (r1 > r2)
        return 2;
    else if (r1 < r2)
        return 1;
    else
        return 0;
}

// ------------------------------------------------------
// Polynomial
// ------------------------------------------------------

// P-1
Polynomial ADD_PP_P(Polynomial p1, Polynomial p2) { return p1 + p2; }

// P-2
Polynomial SUB_PP_P(Polynomial p1, Polynomial p2) { return p1 - p2; }

// P-3
Polynomial MUL_PQ_P(Polynomial p, Rational r) { return p * r; }

// P-4
Polynomial MUL_Pxk_P(Polynomial p, Natural k) { return p << k; }

// P-5
Rational LED_P_Q(Polynomial p) { return p.msc(); }

// P-6
Natural DEG_P_N(Polynomial p) { return p.deg(); }

// P-7
Rational FAC_P_Q(Polynomial p) { return p.fac(); }

// P-8
Polynomial MUL_PP_P(Polynomial p1, Polynomial p2) { return p1 * p2; }

// P-9
Polynomial DIV_PP_P(Polynomial p1, Polynomial p2) { return p1 / p2; }

// P-10
Polynomial MOD_PP_P(Polynomial p1, Polynomial p2) { return p1 % p2; }

// P-11
Polynomial GCF_PP_P(Polynomial p1, Polynomial p2) { return p1.gcd(p2); }

// P-12
Polynomial DER_P_P(Polynomial p) { return p.derivative(); }

// P-13
Polynomial NMR_P_P(Polynomial p) { return p.to_simple_roots(); }

// P-additional-1
bool NZER_P_B(Polynomial p) { return !p.is_zero(); }

// P-additional-2
bool INT_P_B(Polynomial p) { return p.is_integer(); }

} // end of backend namespace
