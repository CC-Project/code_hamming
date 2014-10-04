#include <stdlib.h>
#include <stdio.h>
#include "hamming.h"

int main()
{
    struct Base base = base_generate(2,1);

    //Fonctions de test sur la structure data.
    /*
    struct Data d = data_generate(base, 4);

    uint8_t i = 0;
    data_set(3, 1, &d);
    print_var_bits(d.data_array[0]);
    //print_var_bits(d.data_array[1]);
    for(i=0; i<d.data_number; i++)
        printf("%d\n", data_get(i, &d));

    data_delete(&d);
    */

    //Fonctions de test sur la structure matrix
    //*

    struct Matrix m = matrix_generate(10, 1, base);
    struct Matrix id = matrix_generate(1, 10, base);

    matrix_set(&m, 3, 1, 1);
    matrix_set(&id, 1, 3, 1);
    matrix_show(&id);
    matrix_show(&m);

    struct Matrix r = matrix_mul(&m, &id);
    matrix_show(&r);

    matrix_free(&m);
    //*/
    return 0;
}
