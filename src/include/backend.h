// Author: Ivanov Artyom 3381

#pragma once

#include "Natural.h"
#include "Integer.h"
#include "Rational.h"
#include "Polynomial.h"

namespace backend {

// --------------------------------------
// NATURAL
// --------------------------------------

// N-1
int COM_NN_D(Natural n1, Natural n2);

// N-2
bool NZER_N_B(Natural n);

// N-3
Natural ADD_1N_N(Natural n);

// N-4
Natural ADD_NN_N(Natural n1, Natural n2);

// N-5
Natural SUB_NN_N(Natural n1, Natural n2);

// N-6
Natural MUL_ND_N(Natural n1, uint8_t d);

// N-7
Natural MUL_Nk_N(Natural n, Natural k);

// N-8
Natural MUL_NN_N(Natural n1, Natural n2);

// N-9
Natural SUB_NDN_N(Natural n1, Natural n2, uint8_t d);

// N-10
uint8_t DIV_NN_Dk(Natural n1, Natural n2, Natural k);

// N-11
Natural DIV_NN_N(Natural n1, Natural n2);

// N-12
Natural MOD_NN_N(Natural n1, Natural n2);

// N-13
Natural GCF_NN_N(Natural n1, Natural n2);

// N-14
Natural LCM_NN_N(Natural n1, Natural n2);

// N-additional-1
Natural SUB_1N_N(Natural n);

// --------------------------------------
// INTEGER
// --------------------------------------

// Z-1
Integer ABS_Z_Z(Integer i);

// Z-2
int SGN_Z_D(Integer i);

// Z-3
Integer MUL_ZM_Z(Integer i);

// Z-4
Integer TRANS_N_Z(Natural n);

// Z-5
Natural TRANS_Z_N(Integer i);

// Z-6
Integer ADD_ZZ_Z(Integer i1, Integer i2);

// Z-7
Integer SUB_ZZ_Z(Integer i1, Integer i2);

// Z-8
Integer MUL_ZZ_Z(Integer i1, Integer i2);

// Z-9
Integer DIV_ZZ_Z(Integer i1, Integer i2);

// Z-10
Integer MOD_ZZ_Z(Integer i1, Integer i2);

// Z-additional-1
Integer MUL_Zk_Z(Integer i, Natural k);

// Z-additional-2
Integer ADD_1Z_Z(Integer i);

// Z-additional-3
Integer SUB_1Z_Z(Integer i);

// --------------------------------------
// RATIONAL
// --------------------------------------

// Q-1
Rational RED_Q_Q(Rational r);

// Q-2
bool INT_Q_B(Rational r);

// Q-3
Rational TRANS_Z_Q(Integer i);

// Q-4
Integer TRANS_Q_Z(Rational r);

// Q-5
Rational ADD_QQ_Q(Rational r1, Rational r2);

// Q-6
Rational SUB_QQ_Q(Rational r1, Rational r2);

// Q-7
Rational MUL_QQ_Q(Rational r1, Rational r2);

// Q-8
Rational DIV_QQ_Q(Rational r1, Rational r2);

// ------------------------------------------------------
// Polynomial
// ------------------------------------------------------

// P-1
Polynomial ADD_PP_P(Polynomial p1, Polynomial p2);

// P-2
Polynomial SUB_PP_P(Polynomial p1, Polynomial p2);

// P-3
Polynomial MUL_PQ_P(Polynomial p, Rational r);

// P-4
Polynomial MUL_Pxk_P(Polynomial p, Natural k);

// P-5
Rational LED_P_Q(Polynomial p);

// P-6
Natural DEG_P_N(Polynomial p);

// P-7
Rational FAC_P_Q(Polynomial p);

// P-8
Polynomial MUL_PP_P(Polynomial p1, Polynomial p2);

// P-9
Polynomial DIV_PP_P(Polynomial p1, Polynomial p2);

// P-10
Polynomial MOD_PP_P(Polynomial p1, Polynomial p2);

// P-11
Polynomial GCF_PP_P(Polynomial p1, Polynomial p2);

// P-12
Polynomial DER_P_P(Polynomial p);

// P-13
Polynomial NMR_P_P(Polynomial p);

} // end of backend namespace
