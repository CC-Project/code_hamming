#include <stdlib.h>
#include <stdio.h>
#include "hamming.h"

int main()
{
    struct Base base = base_generate(2,1);
    struct Matrix m = matrix_generate(5,5,base);

    matrix_set(&m, 2,3,1);
    matrix_set(&m, 3,1,1);
    matrix_set(&m, 5,1,1);

    matrix_show(&m);

    //matrix_del_col(4, &m);

    matrix_free(&m);
    //*/
    return 0;
}
