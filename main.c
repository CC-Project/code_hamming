#include <stdlib.h>
#include <stdio.h>
#include "hamming.h"

int main()
{
    struct Base base = base_generate(2,1);
    struct Matrix m = matrix_generate(5,5,base);

    matrix_set(&m, 1,1,1);
    matrix_set(&m, 3,1,1);
    matrix_set(&m, 1,2,1);
    matrix_set(&m, 1,5,1);
    matrix_set(&m, 2,3,1);
    matrix_set(&m, 5,3,1);

    struct Data d = m.data;
    data_show(&d);
    printf("\n\n");
    data_delete(3,&d);

    data_show(&d);
    matrix_free(&m);
    data_free(&d);
    //*/
    return 0;
}
