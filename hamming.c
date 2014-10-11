#include "hamming.h"
#include <math.h>


struct Data hamming_encode(struct Hamming_config * conf, struct Data * word)
{
    struct Matrix word_matrix = matrix_generate(word->data_number, 1, word->data_base);
    word_matrix.data = *word;

    struct Matrix result = matrix_mul(&(conf->generatrix_matrix), &word_matrix);
    return result.data;
}
/*
struct Data hamming_decode(struct * Hamming_config conf, struct Data * word)
{

}
*/

int16_t hamming_check(struct Hamming_config *conf, struct Data * word)
{
    struct Matrix data = matrix_generate(word->data_number, 1, word->data_base);
    data.data = *word;

    struct Matrix r = matrix_mul(&(conf->control_matrix), &data);

    return r.data.data_array[0] >> (8 - conf->m); // On retourne le nombre en binaire correspondant � l'emplacement de l'erreur (=> que la matrice data re�u soit d'une taille < 255 lignes, m < 8)
}
struct Matrix hamming_generate_control_matrix(struct Hamming_config * conf)
{
    uint16_t cols = int_pow(2, conf->m);
    struct Matrix control = matrix_generate(conf->m, cols, conf->base); // Generation de la matrice de controle
    // C'est ici qu'intervient la condition m <= 12, en effet, data ne peut contenir que 2^16 data, en resolvant m*2^m <= 2^16 on trouve m <= 12

    // Remplissage de la matrice de controle
    /* Principe pour la base 2 :
        On remplit la matrice de maniere recursive avec les vecteur de la base canonique de 2^m
        On supprime ensuite les lignes 2^i avec i dans [0,m-1]
    */

    for(uint8_t i = 1; i <= conf->m; i++)
        for(uint16_t j = 1; j <= cols; j++)
            if(((j - 1) / int_pow(2, conf->m - i)) % 2 == 0)
                matrix_set(&control, i, j, 0);
            else
                matrix_set(&control, i, j, 1);

    // On rend la matrice syst�matique
    matrix_del_col(1, &control);

    for(uint8_t j = 0; j < conf->m; j++)
        matrix_del_col(int_pow(2, j) - j, &control);

    struct Matrix identity = matrix_generate(conf->m, conf->m, conf->base);
    matrix_make_identity(&identity);

    return matrix_collapse_right(&control, &identity);
}


struct Matrix hamming_generate_gen_matrix(struct Hamming_config * conf)
{
    struct Matrix control = matrix_copy(&(conf->control_matrix)); // R�cup�ration de la matrice de controle

    for(uint8_t i = 1; i <= control.rows; i++)
        matrix_del_col(control.cols, &control); // On supprime les m derni�res colonnes qui correspondent a l'identit�

    struct Matrix identity = matrix_generate(control.cols, control.cols, conf->base);
    matrix_make_identity(&identity);

    struct Matrix gen = matrix_collapse_down(&identity, &control); // On colle ensuite cette matrice avec l'identit�
    return gen;
}
/*
uint16_t hamming_length(struct Data * word1, struct Data * word2) // Renvoie la distance de hamming entre 2 codes
{
    // Formule valable en base 2 seulement
    uint16_t r = 0;

    for(uint8_t i = 0; i < word1->data_number; i++)
        r += data_get(&word1, i) ^ data_get(&word2, i);

    return r;
}
*/
struct Hamming_config hamming_generate_config(uint8_t l, uint8_t m) // l = longueur des elements de la base, m = param�tre de hamming
{
    struct Hamming_config conf;
    struct Base base;

    // Configuration de la base
    base.d = int_pow(2, l);
    base.l = l;

    // Calcul des param�tres
    conf.total_size = (int_pow(base.d, m) - 1)/(base.d - 1);
    conf.word_size = conf.total_size - m;
    conf.correction_size = 3; // 3 = code de hamming simple, 4 = code de hamming �tendu

    // Enregistrement des param�tres
    conf.base = base;
    conf.m = m;

    // Creation de la matrice de controle
    conf.control_matrix = hamming_generate_control_matrix(&conf);
    conf.generatrix_matrix = hamming_generate_gen_matrix(&conf);
    return conf;
}

void hamming_free_config(struct Hamming_config *conf)
{
    matrix_free(&(conf->generatrix_matrix));
    matrix_free(&(conf->control_matrix));
    free(conf);
}
