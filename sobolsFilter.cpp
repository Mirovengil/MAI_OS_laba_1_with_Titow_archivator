#include "sobolsFilter.h"

const int SOBOLS_MATRIX_SIZE = 3;
const int SOBOLS_MATRIX_X[SOBOLS_MATRIX_SIZE][SOBOLS_MATRIX_SIZE] =
{
    1,  2,  1,
    0,  0,  0,
    -1, -2, -1,
}; 

const int SOBOLS_MATRIX_Y[SOBOLS_MATRIX_SIZE][SOBOLS_MATRIX_SIZE] =
{
    -1, 0,  +1,
    -2, 0,  +2,
    -1, 0,  +1,
}; 