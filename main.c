#include <stdlib.h>
#include <stdio.h>
#include "utilities.h"
#include "hamming.h"

int main()
{
    struct Base base = base_generate(1);

    //Test code
    /**
    uint8_t* i = malloc(2*sizeof(uint8_t));
    i[0] = 1;
    i[1] = 2;
    i = realloc(i, 3 * sizeof(uint8_t));
    i[2] = 3;
    printf("%d %d %d", i[0], i[1], i[2]);
    free(i);
    **/

    //Test code for data struct
    /**
    struct Data d = data_generate(base,9);
    data_set(0,2, &d);
    data_set(1, data_get(0,&d), &d);
    data_show(&d);
    data_delete(1,&d);
    data_show(&d);
    data_add(3,&d);
    data_show(&d);
    data_free(&d);
    **/

    //Test code for matrix struct

    //Test code for hamming

    struct Hamming_config conf = hamming_generate_config(1, 6);

    printf("Matrice de controle :\n");
    matrix_show(&(conf.control_matrix));

    printf("Matrice generatrice :\n");
    matrix_show(&(conf.generatrix_matrix));

    struct Data dte = data_generate(base, 4);
    dte.data_array[0] = 0b10100000;

    struct Data d = hamming_encode(&conf, &dte);

    printf("Data to encode (dte) :\n");
    data_show(&dte);

    printf("Data encoded (de) :\n");
    data_show(&d);

    data_set(5, 1, &d);

    printf("Data modified (dm) :\n");
    data_show(&d);

    uint8_t r = hamming_check(&conf, &(d));

    printf("Correction C x de :\n");
    printf("%d", r);
    printf(" | ");
    print_var_bits(r);
    hamming_free_config(&conf);
}
