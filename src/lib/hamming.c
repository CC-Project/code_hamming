#include "../include/hamming.h"

// Set up
struct Hamming_config* hamming_generate_config()
{
    struct Hamming_config* config = malloc(sizeof(struct Hamming_config));

    hamming_generate_control_matrix(config);
    hamming_generate_generator_matrix(config);
    hamming_generate_syndromes_array(config);

    return config;
}

void hamming_free_config(struct Hamming_config *conf)
{
    matrix_free(conf->CONTROL_MATRIX);
    matrix_free(conf->GENERATOR_MATRIX);
    data_free(conf->SYNDROMES_ARRAY);
    free(conf);
}

// Coding and decoding matrix
void hamming_generate_generator_matrix(struct Hamming_config * conf)
{
    //Get the control matrix
    struct Matrix* control = matrix_copy(conf->CONTROL_MATRIX);

    for(uint8_t i = 1; i <= control->rows; i++)
        matrix_del_col(control->cols, control); //Removes the m last cols

    struct Matrix* identity = matrix_generate(control->cols, control->cols);
    matrix_make_identity(identity);

    conf->GENERATOR_MATRIX = matrix_concat_down(identity, control); //Merge it with the identity

    // Frees memory
    matrix_free(identity);
    matrix_free(control);
}

void hamming_generate_control_matrix(struct Hamming_config * conf)
{
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
}

void hamming_generate_syndromes_array(struct Hamming_config * conf)
{
    conf->SYNDROMES_ARRAY = data_generate(8 * (N + 1)); // On fait +1 pour prendre en compte le zéro
    struct Matrix* syndrome_test_matrix = matrix_generate(N, 1);
    struct Matrix* syndrome_result = NULL;
    uint16_t syndrome;

    // Pour la base 2
    for(uint16_t i = 1; i <= N; i++)
    {
        // Sets the "N - i" bit
        matrix_set(syndrome_test_matrix, N - i + 1, 1, 1);

        // Computation of the syndrome
        syndrome_result = hamming_syndrome(syndrome_test_matrix, conf);
        syndrome = matrix_word_to_int(syndrome_result);

        // Adds the syndrome
        if(conf->SYNDROMES_ARRAY->data_array[syndrome] == 0)
            conf->SYNDROMES_ARRAY->data_array[syndrome] = N - i;

        // Resets the bit
        matrix_set(syndrome_test_matrix, N - i + 1, 1, 0);
        matrix_free(syndrome_result);
    }

    // Frees matrix
    matrix_free(syndrome_test_matrix);
}

// Manipulation of data
struct Matrix* hamming_encode(struct Matrix * word, struct Hamming_config * conf)
{
    return matrix_mul(conf->GENERATOR_MATRIX, word);
}

struct Matrix* hamming_decode(struct Matrix * word, struct Hamming_config * conf)
{
    struct Matrix* word_decode = matrix_generate(K, 1);

    for(uint16_t i = 1; i <= K; i++)
        matrix_set(word_decode, i, 1, matrix_get(word, i, 1));

    return word_decode;
}

struct Matrix* hamming_correction(struct Matrix * word, struct Hamming_config * conf)
{
    struct Matrix* synd = hamming_syndrome(word, conf);
    struct Matrix* word_correct = matrix_copy(word);

    if(!matrix_is_null(synd))
    {
        uint8_t synd_check = hamming_check_syndrome(synd, conf) + 1;
        matrix_set(word_correct, synd_check, 1, opposite_bit(matrix_get(word, synd_check, 1)));

        return word_correct;
    }

    matrix_free(synd);
    return word_correct;
}

uint8_t hamming_check_syndrome(struct Matrix* synd, struct Hamming_config* conf)
{
    return conf->SYNDROMES_ARRAY->data_array[matrix_word_to_int(synd)];
}

struct Matrix* hamming_syndrome(struct Matrix* word, struct Hamming_config* conf)
{
    return matrix_mul(conf->CONTROL_MATRIX, word);
    // On retourne le nombre en binaire correspondant au syndrome (Suppose que la matrice data recue soit d'une taille < 255 lignes, m < 8)
}
