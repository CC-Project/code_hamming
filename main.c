#include <stdlib.h>
#include <stdio.h>
#include "hamming.h"

int main()
{
    struct Base base = base_generate(1);
    struct Hamming_config conf = hamming_generate_config(1, 3);

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

    uint8_t r = hamming_check(&conf, &(d));

    printf("Correction C x de :\n");
    printf("%d", r);
    printf(" | ");
    print_var_bits(r);
    return 0;
}
