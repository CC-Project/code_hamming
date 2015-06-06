// Import configuration
#include "config.h"
//Import all modules and libs
#include "../lib_data/data.h"
#include "../lib_utilities/utilities.h"

#include "src/code_matrix.h"
#include "src/matrix.h"
int main()
{
    struct Matrix_config* conf = cmatrix_generate_config();

    // Display the generator and control matrix

    printf("Control matrix: \n");
    matrix_show(conf->CONTROL_MATRIX);

    printf("Generator matrix: \n");
    matrix_show(conf->GENERATOR_MATRIX);

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
    matrix_set(d, 2, 1, 1);
    matrix_set(d, 5, 1, 1);
    printf("Data modified : %d elements\n", d->data->data_number);
    matrix_show_word(d);

    // Correction
    struct Matrix* r = cmatrix_syndrome(d, conf);

    printf("\n\nCorrection\n-----------\n\n");
    printf("Syndrome of the modified code : %d \n", matrix_word_to_int(r));

    printf("Corrected matrix :\n", matrix_word_to_int(r));

    matrix_show_word(cmatrix_correction(d, conf));
/*
    if(!matrix_is_null(r))
    {
        uint8_t b = cmatrix_check_syndrome(r, conf);
        printf("The bit %d is corrupted\n", b + 1);
    }
    else
        printf("No bit corrupted\n");

    printf("Corrected matrix :\n", matrix_word_to_int(r));

    matrix_show_word(cmatrix_decode(d, conf));

    matrix_free(dte);
    matrix_free(d);
    matrix_free(r);

    cmatrix_free_config(conf);*/
/*
    uint8_t synd_array[2048][3] = {0};
    struct Matrix* syndrome_test_matrix = matrix_generate(conf->CONTROL_MATRIX->cols, 1);
    struct Matrix* syndrome_result;
    uint16_t syndrome;
    uint16_t compteur = 0;

    // Correction de seulement une erreur (valable pour tout les codes)
    for(uint8_t i = 0; i < conf->CONTROL_MATRIX->cols; i++)
        for(uint8_t j = 0; j <= i; j++)
            for(uint8_t k = 0; k <= j; k++)
            {
                // Sets the "N - i" bit
                matrix_set(syndrome_test_matrix, conf->CONTROL_MATRIX->cols - i, 1, 1);
                if(j != i)
                    matrix_set(syndrome_test_matrix, conf->CONTROL_MATRIX->cols - j, 1, 1);
                if(k != j)
                    matrix_set(syndrome_test_matrix, conf->CONTROL_MATRIX->cols - k, 1, 1);
                // Computation of the syndrome
                syndrome_result = cmatrix_syndrome(syndrome_test_matrix, conf);
                syndrome = matrix_word_to_int(syndrome_result);
                /*
                printf("------------------\n\n(%d, %d, %d) : %d\n", i, j, k, syndrome);
                matrix_show_word(syndrome_test_matrix);

                // Adds the syndrome
                synd_array[syndrome][0] = conf->CONTROL_MATRIX->cols - i;
                synd_array[syndrome][1] = (j == i) ? 0 : conf->CONTROL_MATRIX->cols - j;
                synd_array[syndrome][2] = (k == j) ? 0 : conf->CONTROL_MATRIX->cols - k;

                // Resets the bit
                // Sets the "N - i" bit
                matrix_set(syndrome_test_matrix, conf->CONTROL_MATRIX->cols - i, 1, 0);
                if(j != i)
                    matrix_set(syndrome_test_matrix, conf->CONTROL_MATRIX->cols - j, 1, 0);
                if(k != j)
                    matrix_set(syndrome_test_matrix, conf->CONTROL_MATRIX->cols - k, 1, 0);

                matrix_free(syndrome_result);
                compteur++;
            }

    printf("\n\nTotal : %d; taille : %d", compteur, sizeof(synd_array));
    matrix_free(syndrome_test_matrix);
/*
    printf("\n\n\n");
    printf("uint8_t SYNDROME_ARRAY[%d][3] PROGMEM = {", 1 << conf->CONTROL_MATRIX->rows);

    for(uint16_t k = 0; k < 1 << conf->CONTROL_MATRIX->rows; k++)
        if(k == (1 << conf->CONTROL_MATRIX->rows) - 1)
            printf("{%d, %d, %d}", synd_array[k][0], synd_array[k][1], synd_array[k][2]);
        else
            printf("{%d, %d, %d}, ", synd_array[k][0], synd_array[k][1], synd_array[k][2]);

    printf("};\n\n\n");
*/
/*
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

    printf("Corrected matrix :\n", matrix_word_to_int(r));

    matrix_show_word(cmatrix_decode(d, conf));

    matrix_free(dte);
    matrix_free(d);
    matrix_free(r);

    cmatrix_free_config(conf);

    return 0;*/
}
