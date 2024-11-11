// Author: Ivanov Artyom 3381

#include "../include/backend.h"

#include "stdexcept"

#define E_NOT_DIGIT "d must be digit, not a number!"
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
bool NZER_N_B(Natural n) { return n.is_zero(); }

// N-3
Natural ADD_1N_N(Natural n) { return ++n; }

// N-4
Natural ADD_NN_N(Natural n1, Natural n2) { return n1 + n2; }

// N-5
Natural SUB_NN_N(Natural n1, Natural n2) { return n1 - n2; };

// N-6
Natural MUL_ND_N(Natural n1, uint8_t d)
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
Natural SUB_NDN_N(Natural n1, Natural n2, uint8_t d) 
{
    if (d > 9)
        throw std::invalid_argument(E_NOT_DIGIT);
    
    return n1 - Natural(d) * n2;
}

// N-10
// something strange xD

// N-11
Natural DIV_NN_N(Natural n1, Natural n2) { return n1 / n2; }

// N-12
Natural MOD_NN_N(Natural n1, Natural n2) { return n1 % n2; }

// N-13
Natural GCF_NN_N(Natural n1, Natural n2) { return n1.gcd(n2); }

// N-14
Natural LCM_NN_N(Natural n1, Natural n2) { return n1.lcm(n2); }

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
Natural TRANZ_Z_N(Integer i) { return Natural(i); }

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

// --------------------------------------
// RATIONAL
// --------------------------------------

// Q-1
// TODO in future
Rational RED_Q_Q(Rational r) { return r; }

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
