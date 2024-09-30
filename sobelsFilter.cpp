#include "sobelsFilter.h"

const int SOBELS_MATRIX_SIZE = 3;
const int SOBELS_MATRIX_X[SOBELS_MATRIX_SIZE][SOBELS_MATRIX_SIZE] =
{
    1,  2,  1,
    0,  0,  0,
    -1, -2, -1,
}; 

const int SOBOLS_MATRIX_Y[SOBELS_MATRIX_SIZE][SOBELS_MATRIX_SIZE] =
{
    -1, 0,  +1,
    -2, 0,  +2,
    -1, 0,  +1,
}; 