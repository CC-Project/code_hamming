// Import configuration
#include "config.h"
#include "code_config.h"
//Import all modules and libs
#include "../lib_data/data.h"
#include "../lib_utilities/utilities.h"

#include "src/code_matrix.h"
#include "src/matrix.h"
int main()
{
    /*
    struct Matrix* a = matrix_generate(6, 1);
    struct Matrix* b = matrix_generate(3, 6);

    matrix_set(a, 1, 1, 1); matrix_set(a, 3, 1, 1); matrix_set(a, 6, 1, 1);
    matrix_set(b, 1, 1, 1); matrix_set(b, 1, 6, 1); matrix_set(b, 2, 1, 1); matrix_set(b, 2, 3, 1); matrix_set(b, 2, 6, 1); matrix_set(b, 3, 1, 1); matrix_set(b, 3, 6, 1);
    matrix_show(a); matrix_show(b);

    struct Matrix* r = matrix_mul(b, a);
    matrix_show(r);
    data_show(r->data);
*/

    struct Matrix_config* conf = cmatrix_generate_config();
    #if USED_CODE == CODE_HAMMING
        printf("\nTest of the (%d, %d, 3) Hamming code\n--------------------------------\n\n", N, K);
    #elif USED_CODE == CODE_REPETITION
        printf("\nTest of the (%d, %d) repetition code\n--------------------------------\n\n", N, K);
    #endif
    // Display the generator and control matrix
    printf("Control matrix: \n");
    matrix_show(conf->CONTROL_MATRIX);

    printf("Generator matrix: \n");
    matrix_show(conf->GENERATOR_MATRIX);

    printf("Syndromes array: \n");
    for(uint8_t i = 0; i < (1 << conf->CONTROL_MATRIX->rows); i++)
        printf("|%d : %d|\n", i, conf->SYNDROMES_ARRAY[i]);

    printf("\n");

    // Generation of the word to encode
    struct Matrix* dte = matrix_generate(K, 1);
    matrix_set(dte, 3, 1, 1);
    matrix_set(dte, 1, 1, 1);

    // Display
    printf("Data to encode : %d elements\n", dte->data->data_number);
    matrix_show_word(dte);

    // Encoding
    struct Matrix* d = cmatrix_encode(dte, conf);
    printf("Data encoded : %d elements\n", d->data->data_number);
    matrix_show_word(d);

    // Add an error
    data_set(4, 0, d->data);

    printf("Data modified : %d elements\n", d->data->data_number);
    matrix_show_word(d);

    // Correction
    struct Matrix* r = cmatrix_syndrome(d, conf);

    printf("\n\nCorrection\n-----------\n\n");
    printf("Syndrome of the modified code : %d \n", matrix_word_to_int(r));

    if(!matrix_is_null(r))
    {
        uint8_t b = cmatrix_check_syndrome(r, conf);
        printf("The bit %d is corrupted\n", b + 1);
    }
    else
        printf("No bit corrupted\n");

    matrix_free(dte);
    matrix_free(d);
    matrix_free(r);

    cmatrix_free_config(conf);

    return 0;
}
