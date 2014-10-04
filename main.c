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
    struct Matrix m = matrix_generate(3,3,base);
    uint8_t i = 0;
    for(i = 1; i <= 3; i++)
        matrix_set_value(&m, i, i, 1);
    matrix_show(&m);
    matrix_void(&m);
    matrix_show(&m);

    struct Matrix id = matrix_generate_identity(3, base);
    matrix_show(&id);
    //matrix_delete(&id);

    matrix_delete(&m);
    //*/
    return 0;
}
