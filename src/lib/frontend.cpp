#include "../include/frontend.h"

int COM_NN_D(const Natural &n1, const Natural &n2)
{
    if (n1 > n2)
        return 2;
    else if (n1 < n2)
        return 1;
    else
        return 0;
}

bool NZER_N_B(const Natural &n) { return n.is_zero(); }
