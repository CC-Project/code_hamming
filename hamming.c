#include "hamming.h"

struct Matrix hamming_encode(struct Matrix * word, struct Hamming_config * conf)
{
    struct Matrix result = matrix_mul(&(conf->CONTROL_MATRIX), word);
    return result;
}

struct Matrix hamming_syndrome(struct Matrix * word, struct Hamming_config * conf)
{
    struct Matrix result = matrix_mul(&(conf->CONTROL_MATRIX), word);
    return result; // On retourne le nombre en binaire correspondant au syndrome (=> que la matrice data re�u soit d'une taille < 255 lignes, m < 8)
}

struct Matrix hamming_decode(struct Matrix * word, struct Hamming_config * conf)
{
    struct Matrix word_decode = matrix_generate(conf->W_SIZE, 1);

    for(uint16_t i = 1; i <= conf->W_SIZE; i++)
        matrix_set(&word_decode, i, 1, matrix_get(word, i, 1));

    return word_decode;
}

struct Matrix hamming_correction(struct Matrix * word, struct Hamming_config * conf)
{
    struct Matrix synd = hamming_syndrome(word, conf);

    if(!matrix_isempty(&synd))
    {
        struct Matrix word_correct = matrix_copy(word);
        uint8_t synd_check = hamming_check_syndrome(&synd, conf) + 1;

        matrix_set(&word_correct, synd_check, 1, opposite_word(matrix_get(word, synd_check, 1)));

        return word_correct;
    }
    else
        return *word;
}

uint8_t hamming_check_syndrome(struct Matrix * synd, struct Hamming_config * conf)
{
    return conf->SYNDROMES_ARRAY.data_array[matrix_word_to_int(synd)];
}

/**
###########
**/
struct Matrix hamming_generate_control_matrix(struct Hamming_config * conf)
{
    uint16_t cols = (1 << HAMMING_M);
    struct Matrix control = matrix_generate(HAMMING_M, cols); // Generation de la matrice de controle

    // C'est ici qu'intervient une condition sur m : m <= 12, en effet, data ne peut contenir que 2^16 data, en resolvant m*2^m <= 2^16 on trouve m <= 12

    /* Principe pour la base 2 :
        On remplit la matrice de maniere recursive avec les vecteur de la base canonique de 2^m
        On supprime ensuite les lignes 2^i avec i dans [0,m-1]
    */

    // Remplissage de la matrice de controle
    for(uint8_t i = 1; i <= HAMMING_M; i++)
        for(uint16_t j = 1; j <= cols; j++)
            if(((j - 1) / (1 << (HAMMING_M - i))) % 2 == 0)
                matrix_set(&control, i, j, 0);
            else
                matrix_set(&control, i, j, 1);

    // On rend la matrice syst�matique
    matrix_del_col(1, &control);

    for(uint8_t j = 0; j < HAMMING_M; j++)
        matrix_del_col((1 << j) - j, &control);

    struct Matrix identity = matrix_generate(HAMMING_M, HAMMING_M);
    matrix_make_identity(&identity);

    struct Matrix result = matrix_collapse_right(&control, &identity);

    // Frees memory
    matrix_free(&identity);
    matrix_free(&control);

    return result;
}

struct Matrix hamming_generate_gen_matrix(struct Hamming_config * conf)
{
    struct Matrix control = matrix_copy(&(conf->CONTROL_MATRIX)); // R�cup�ration de la matrice de controle

    for(uint8_t i = 1; i <= control.rows; i++)
        matrix_del_col(control.cols, &control); // On supprime les m derni�res colonnes qui correspondent a l'identit�

    struct Matrix identity = matrix_generate(control.cols, control.cols);
    matrix_make_identity(&identity);

    struct Matrix result = matrix_collapse_down(&identity, &control); // On colle ensuite cette matrice avec l'identit�

    // Frees memory
    matrix_free(&identity);
    matrix_free(&control);

    return result;
}

struct Data hamming_generate_syndromes_array(struct Hamming_config * conf)
{
    struct Matrix d = matrix_generate(conf->EW_SIZE, 1); struct Matrix dc;
    struct Data syndrome_array = data_generate(sizeof(uint8_t) * (1 << HAMMING_M));

    uint8_t synd; uint16_t nb;

    // Pour la base 2
    for(uint16_t i = 1; i <= conf->EW_SIZE; i++)
    {
        nb = conf->EW_SIZE - i + 1;
        matrix_set(&d, nb, 1, 1);
        dc = hamming_syndrome(&d, conf);

        // Ici, on sait que m <= 8. donc que dc est cod� sur 8 bits
        synd = matrix_word_to_int(&dc); // On r�cup�re le syndrome sous forme d'entier

        if(synd != 0 && syndrome_array.data_array[synd] == 0) // Si le syndrome n'a pas deja ete calcule
            syndrome_array.data_array[synd] = conf->EW_SIZE - i; // On le met a jour

        matrix_set(&d, nb, 1, 0);
    }
    // Frees memory
    matrix_free(&d);
    matrix_free(&dc);

    return syndrome_array;
}

struct Hamming_config hamming_generate_config() // l = longueur des elements de la base, m = param�tre de hamming
{
    struct Hamming_config config;

    // ### Calcul des param�tres
    config.EW_SIZE = (int_pow(BASE_D, HAMMING_M) - 1)/(BASE_D - 1);
    config.W_SIZE = config.EW_SIZE - HAMMING_M;
    config.C_SIZE = (HAMMING_EXTENDED) ? 4 : 3; // 3 = code de hamming simple

    // ### Creation de la matrice de controle
    config.CONTROL_MATRIX = hamming_generate_control_matrix(&config);
    config.GENERATRIX_MATRIX = hamming_generate_gen_matrix(&config);

    // ### Generation du tableau de syndromes
    config.SYNDROMES_ARRAY = hamming_generate_syndromes_array(&config);

    return config;
}

void hamming_free_config(struct Hamming_config *conf)
{
    matrix_free(&(conf->GENERATRIX_MATRIX));
    matrix_free(&(conf->CONTROL_MATRIX));

    free(&(conf->SYNDROMES_ARRAY));
    free(conf);
}
