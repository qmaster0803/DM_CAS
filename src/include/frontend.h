// Author: Ivanov Artyom 3381

#pragma once

#include "Natural.h"
#include "Integer.h"
#include "Rational.h"
#include "Polynomial.h"

// --------------------------------------
// NATURAL
// --------------------------------------

// N-1
int COM_NN_D(const Natural &n1, const Natural &n2);

// N-2
bool NZER_N_B(const Natural &n);

// N-3
Natural ADD_1N_N(const Natural &n);

// N-4
Natural ADD_NN_N(const Natural &n1, const Natural &n2);

// N-5
Natural SUB_NN_N(const Natural &n1, const Natural &n2);

// N-6
Natural MUL_ND_N(const Natural &n1, uint8_t d);

// N-7
Natural MUL_Nk_N(const Natural &n, std::size_t k);

// N-8
Natural MUL_NN_N(const Natural &n1, const Natural &n2);

// N-9
Natural SUB_NDN_N(const Natural &n1, const Natural &n2, uint8_t d);

// N-10
// something strange xD

// N-11
Natural DIV_NN_N(const Natural &n1, const Natural &n2);

// N-12
Natural MOD_NN_N(const Natural &n1, const Natural &n2);

// N-13
Natural GCF_NN_N(const Natural &n1, const Natural &n2);

// N-14
Natural LCM_NN_N(const Natural &n1, const Natural &n2);

// --------------------------------------
// INTEGER
// --------------------------------------

// Z-1
Integer ABS_Z_Z(const Integer &i);

// Z-2
int SGN_Z_D(const Integer &i);

// Z-3
Integer MUL_ZM_Z(const Integer &i);

// Z-4
Integer TRANS_N_Z(const Natural &n);

// Z-5
Natural TRANZ_Z_N(const Integer &i);

// Z-6
Integer ADD_ZZ_Z(const Integer &i1, const Integer &i2);

// Z-7
Integer SUB_ZZ_Z(const Integer &i1, const Integer &i2);

// Z-8
Integer MUL_ZZ_Z(const Integer &i1, const Integer &i2);

// Z-9
Integer DIV_ZZ_Z(const Integer &i1, const Integer &i2);

// Z-10
Integer MOD_ZZ_Z(const Integer &i1, const Integer &i2);

// --------------------------------------
// RATIONAL
// --------------------------------------

// Q-1
Rational RED_Q_Q(const Rational &r);

// Q-2
// TODO later
bool INT_Q_B(const Rational &r);

// Q-3
Integer TRANS_Z_Q(const Integer &i);

// Q-4
Integer TRANS_Q_Z(const Rational &i);

// Q-5
Rational ADD_QQ_Q(const Rational &r1, const Rational &r2);

// Q-6
Rational SUB_QQ_Q(const Rational &r1, const Rational &r2);

// Q-7
Rational MUL_QQ_Q(const Rational &r1, const Rational &r2);

// Q-8
Rational DIV_QQ_Q
