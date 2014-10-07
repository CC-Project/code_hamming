#include <stdlib.h>
#include <stdio.h>
#include "hamming.h"

int main()
{
    struct Base base = base_generate(2,1);
    struct Hamming_config conf= hamming_generate_config(1, 3);

    matrix_show(&(conf.control_matrix));
    matrix_show(&(conf.generatrix_matrix));
    return 0;
}
