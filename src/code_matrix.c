#include "code_matrix.h"

// Set up
struct Matrix_config* cmatrix_generate_config()
{
    struct Matrix_config* config = malloc(sizeof(struct Matrix_config));

    cmatrix_generate_control_matrix(config);
    cmatrix_generate_generator_matrix(config);
    cmatrix_generate_syndromes_array(config);

    return config;
}

void cmatrix_free_config(struct Matrix_config *conf)
{
    matrix_free(conf->CONTROL_MATRIX);
    matrix_free(conf->GENERATOR_MATRIX);
    free(conf->SYNDROMES_ARRAY);
    free(conf);
}

// -------------- Coding and decoding matrix ------------------
void cmatrix_generate_control_matrix(struct Matrix_config * conf)
{
    #if USED_CODE == CODE_HAMMING // Hamming code
        struct Matrix* control  = matrix_generate(M, (1 << M)); // Generation of the control matrix

        // C'est ici qu'intervient une condition sur m : m <= 12, en effet, data ne peut contenir que 2^16 data, en resolvant m*2^m <= 2^16 on trouve m <= 12

        // Fills the control matrix
        for(uint16_t i = 1; i <= M; i++)
            for(uint16_t j = 1; j <= (1 << M); j++)
                if(((j - 1) / (1 << (M - i))) % 2 == 0)
                    matrix_set(control, i, j, 0);
                else
                    matrix_set(control, i, j, 1);

        // Make the matrix systematic
        matrix_del_col(1, control);

        //Sub the identity
        for(uint8_t j = 0; j < M; j++)
            matrix_del_col((1 << j) - j, control);

        struct Matrix* identity = matrix_generate(M, M);
        matrix_make_identity(identity);

        conf->CONTROL_MATRIX  = matrix_concat_right(control, identity);

        // Frees memory
        matrix_free(identity);
        matrix_free(control);
    #elif USED_CODE == CODE_REPETITION
        struct Matrix* control = matrix_generate((uint16_t)(K * 2), (uint16_t)(K));

        for(uint8_t i = 0; i < K; i++)
            for(uint8_t p = 0; p < 2; p++)
                matrix_set(control, (p * K + i) + 1, i + 1, 1);

        struct Matrix* identity = matrix_generate((uint16_t)(K * 2), (uint16_t)(K * 2));
        matrix_make_identity(identity);

        conf->CONTROL_MATRIX = matrix_concat_right(control, identity); //Merge it with the identity

        matrix_free(identity); matrix_free(control);
    #endif // HAMMING_CONFIG
}

void cmatrix_generate_generator_matrix(struct Matrix_config * conf)
{
    #if USED_CODE == CODE_HAMMING // Hamming code
        // Get the control matrix
        struct Matrix* control = matrix_copy(conf->CONTROL_MATRIX);

        for(uint8_t i = 1; i <= control->rows; i++)
            matrix_del_col(control->cols, control); //Removes the m last cols

        struct Matrix* identity = matrix_generate(control->cols, control->cols);
        matrix_make_identity(identity);

        conf->GENERATOR_MATRIX = matrix_concat_down(identity, control); //Merge it with the identity

        // Frees memory
        matrix_free(identity);
        matrix_free(control);
    #elif USED_CODE == CODE_REPETITION
        struct Matrix* generator = matrix_generate((uint16_t)(K * 3), (uint16_t)(K));

        for(uint8_t i = 0; i < K; i++)
            for(uint8_t p = 0; p < 3; p++)
                matrix_set(generator, (p * K + i) + 1, i + 1, 1);

        conf->GENERATOR_MATRIX = generator;
    #endif // HAMMING_CONFIG
}


void cmatrix_generate_syndromes_array(struct Matrix_config * conf)
{
    /*
    #if USED_CODE == CODE_HAMMING // Hamming code
        conf->SYNDROMES_ARRAY = data_generate(8 * (N + 1)); // = 2^m
        struct Matrix* syndrome_test_matrix = matrix_generate(N, 1);
        struct Matrix* syndrome_result = NULL;
        uint16_t syndrome;

        for(uint16_t i = 1; i <= N; i++)
        {
            // Sets the "N - i" bit
            matrix_set(syndrome_test_matrix, N - i + 1, 1, 1);

            // Computation of the syndrome
            syndrome_result = cmatrix_syndrome(syndrome_test_matrix, conf);
            matrix_show_word(syndrome_result);
            syndrome = matrix_word_to_int(syndrome_result);
            printf("%d\n", syndrome);
            // Adds the syndrome
            if(conf->SYNDROMES_ARRAY->data_array[syndrome] == 0)
                conf->SYNDROMES_ARRAY->data_array[syndrome] = N - i;

            // Resets the bit
            matrix_set(syndrome_test_matrix, N - i + 1, 1, 0);
            matrix_free(syndrome_result);
        }

        // Frees matrix

    */

    // Code général
    conf->SYNDROMES_ARRAY = calloc((1 << conf->CONTROL_MATRIX->rows), sizeof(SIZE_SYNDROME_ALLOCATION)); // = 2^m
    struct Matrix* syndrome_test_matrix = matrix_generate(N, 1);
    struct Matrix* syndrome_result;
    uint16_t syndrome;

    // Correction de seulement une erreur (valable pour tout les codes)
    for(SIZE_SYNDROME_ALLOCATION i = 0; i < N; i++)
    {
        // Sets the "N - i" bit
        matrix_set(syndrome_test_matrix, N - i, 1, 1);

        // Computation of the syndrome
        syndrome_result = cmatrix_syndrome(syndrome_test_matrix, conf);
        syndrome = matrix_word_to_int(syndrome_result);

        matrix_show_word(syndrome_test_matrix);
        matrix_show_word(syndrome_result);

        // Adds the syndrome
        if(conf->SYNDROMES_ARRAY[syndrome] == 0)
            conf->SYNDROMES_ARRAY[syndrome] = N - i - 1;

        // Resets the bit
        matrix_set(syndrome_test_matrix, N - i, 1, 0);
        matrix_free(syndrome_result);
    }

    matrix_free(syndrome_test_matrix);
}

// Manipulation of data
struct Matrix* cmatrix_encode(struct Matrix * word, struct Matrix_config * conf)
{
    return matrix_mul(conf->GENERATOR_MATRIX, word);
}

struct Matrix* cmatrix_decode(struct Matrix * word, struct Matrix_config * conf)
{
    struct Matrix* corr_word = cmatrix_correction(word, conf);
    struct Matrix* result = cmatrix_extract(word, conf);
    matrix_free(corr_word);

    return result;
}

// --------------- //
struct Matrix* cmatrix_extract(struct Matrix * word, struct Matrix_config * conf)
{
    struct Matrix* word_decode = matrix_generate(K, 1);

    for(uint16_t i = 1; i <= K; i++)
        matrix_set(word_decode, i, 1, matrix_get(word, i, 1));

    return word_decode;
}
struct Matrix* cmatrix_correction(struct Matrix * word, struct Matrix_config * conf)
{
    struct Matrix* synd = cmatrix_syndrome(word, conf);
    struct Matrix* word_correct = matrix_copy(word);

    if(!matrix_is_null(synd))
    {
        uint8_t synd_check = cmatrix_check_syndrome(synd, conf) + 1;
        matrix_set(word_correct, synd_check, 1, opposite_bit(matrix_get(word, synd_check, 1)));

        return word_correct;
    }

    matrix_free(synd);
    return word_correct;
}

SIZE_SYNDROME_ALLOCATION cmatrix_check_syndrome(struct Matrix* synd, struct Matrix_config* conf)
{
    return conf->SYNDROMES_ARRAY[matrix_word_to_int(synd)];
}

struct Matrix* cmatrix_syndrome(struct Matrix* word, struct Matrix_config* conf)
{
    return matrix_mul(conf->CONTROL_MATRIX, word);
}
