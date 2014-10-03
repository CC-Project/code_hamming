#define DEBUG

#include <stdlib.h>
#include <stdio.h>
#include "hamming.h"

int main()
{
    struct Base base = base_generate(2,1);

    //Fonctions de test sur la structure data.
    /*
    struct Data d = data_generate(base, 12);

    uint8_t i = 0;
    data_set(10, 1, &d);
    print_var_bits(d.data_array[0]);
    print_var_bits(d.data_array[1]);
    for(i=0; i<d.data_number; i++)
        printf("%d\n", data_get(i, &d));

    data_delete(&d);
    */

    //Fonctions de test sur la structure matrix
    struct Matrix m = matrix_generate(2,2,base);

    matrix_delete(&m);
    return 0;
}
