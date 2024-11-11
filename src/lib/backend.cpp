// Author: Ivanov Artyom 3381

#include "../include/backend.h"

#include "stdexcept"

#define E_NOT_DIGIT "d must be digit, not a number!"

// --------------------------------------------
// Natural
// --------------------------------------------

// N-1
int backend::COM_NN_D(Natural n1, Natural n2)
{
    if (n1 > n2)
        return 2;
    else if (n1 < n2)
        return 1;
    else
        return 0;
}

// N-2
bool backend::NZER_N_B(Natural n) { return n.is_zero(); }

// N-3
Natural backend::ADD_1N_N(Natural n) { return ++n; }

// N-4
Natural backend::ADD_NN_N(Natural n1, Natural n2) { return n1 + n2; }

// N-5
Natural backend::SUB_NN_N(Natural n1, Natural n2) { return n1 - n2; };

// N-6
Natural backend::MUL_ND_N(Natural n1, uint8_t d)
{
    if (d > 9)
        throw std::invalid_argument(E_NOT_DIGIT);
        
    return n1 * Natural(d);
}

// N-7
Natural backend::MUL_Nk_N(Natural n, Natural k) { return n << k; }

// N-8
Natural backend::MUL_NN_N(Natural n1, Natural n2) { return n1 * n2; }

// N-9
Natural backend::SUB_NDN_N(Natural n1, Natural n2, uint8_t d) 
{
    if (d > 9)
        throw std::invalid_argument(E_NOT_DIGIT);
    
    return n1 - Natural(d) * n2;
}

// N-10
uint8_t backend::DIV_NN_Dk(Natural n1, Natural n2, Natural k)
    { return n1.first_div_digit(n2 << k); }

// N-11
Natural backend::DIV_NN_N(Natural n1, Natural n2) { return n1 / n2; }

// N-12
Natural backend::MOD_NN_N(Natural n1, Natural n2) { return n1 % n2; }

// N-13
Natural backend::GCF_NN_N(Natural n1, Natural n2) { return n1.gcd(n2); }

// N-14
Natural backend::LCM_NN_N(Natural n1, Natural n2) { return n1.lcm(n2); }

// --------------------------------------
// INTEGER
// --------------------------------------

// Z-1
Integer backend::ABS_Z_Z(Integer i) { return i.abs(); }

// Z-2
int backend::SGN_Z_D(Integer i)
{
    if (i.is_zero())
        return 0;
    else if (i.is_neg())
        return -1;
    else
        return 1;
}

// Z-3
Integer backend::MUL_ZM_Z(Integer i)
{
    i.neg();
    return i;
}

// Z-4
Integer backend::TRANS_N_Z(Natural n) { return Integer(n); }

// Z-5
Natural backend::TRANZ_Z_N(Integer i) { return Natural(i); }

// Z-6
Integer backend::ADD_ZZ_Z(Integer i1, Integer i2) { return i1 + i2; }

// Z-7
Integer backend::SUB_ZZ_Z(Integer i1, Integer i2) { return i1 - i2; }

// Z-8
Integer backend::MUL_ZZ_Z(Integer i1, Integer i2) { return i1 * i2; }

// Z-9
Integer backend::DIV_ZZ_Z(Integer i1, Integer i2) { return i1 / i2; }

// Z-10
Integer backend::MOD_ZZ_Z(Integer i1, Integer i2) { return i1 % i2; }

// --------------------------------------
// RATIONAL
// --------------------------------------

// Q-1
// TODO in future
Rational backend::RED_Q_Q(Rational r) { return r; }

// Q-2
bool backend::INT_Q_B(Rational r) { return r.is_integer(); }

// Q-3
Rational backend::TRANS_Z_Q(Integer i) { return Rational(i); }

// Q-4
Integer backend::TRANS_Q_Z(Rational r) { return Integer(r); }

// Q-5
Rational backend::ADD_QQ_Q(Rational r1, Rational r2) { return r1 + r2; }

// Q-6
Rational backend::SUB_QQ_Q(Rational r1, Rational r2) { return r1 - r2; }

// Q-7
Rational backend::MUL_QQ_Q(Rational r1, Rational r2) { return r1 * r2; }

// Q-8
Rational backend::DIV_QQ_Q(Rational r1, Rational r2) { return r1 / r2; }

// P-1
Polynomial backend::ADD_PP_P(Polynomial p1, Polynomial p2) { return p1 + p2; }

// P-2
Polynomial backend::SUB_PP_P(Polynomial p1, Polynomial p2) { return p1 - p2; }

// P-3
Polynomial backend::MUL_PQ_P(Polynomial p, Rational r) { return p * r; }

// P-4
Polynomial backend::MUL_Pxk_P(Polynomial p, Natural k) { return p << k; }

// P-5
Rational backend::LED_P_Q(Polynomial p) { return p.msc(); }

// P-6
Natural backend::DEG_P_N(Polynomial p) { return p.deg(); }

// P-7
Rational backend::FAC_P_Q(Polynomial p) { return p.fac(); }

// P-8
Polynomial backend::MUL_PP_P(Polynomial p1, Polynomial p2) { return p1 * p2; }

// P-9
Polynomial backend::DIV_PP_P(Polynomial p1, Polynomial p2) { return p1 / p2; }

// P-10
Polynomial backend::MOD_PP_P(Polynomial p1, Polynomial p2) { return p1 % p2; }

// P-11
Polynomial backend::GCF_PP_P(Polynomial p1, Polynomial p2) { return p1.gcd(p2); }

// P-12
Polynomial backend::DER_P_P(Polynomial p) { return p.derivative(); }

// P-13
Polynomial backend::NMR_P_P(Polynomial p) { return p.to_simple_roots(); }
