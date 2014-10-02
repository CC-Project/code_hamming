#include "hamming.h"
#include <math.h>

struct Data hamming_encode(struct Hamming_config * conf, struct Data * word)
{
    struct Matrix word_matrix = matrix_generate(word->data_number, 1);
    word_matrix->data = word;

    struct Matrix result = matrix_mul(conf->control_matrix, word_matrix);
    return result.data;
}
/*
struct Data hamming_decode(struct * Hamming_config conf, struct Data * word)
{

}

struct Data hamming_check(struct * Hamming_config conf, struct Data * word)
{

}
*/
struct Matrix hamming_generate_control_matrix(struct Hamming_config * conf)
{
    struct Matrix control = matrix_generate(int_pow(2, conf->m) - 1, m); // Generation de la matrice de controle

    // Remplissage de la matrice de controle
}
struct Matrix hamming_generate_gen_matrix(struct Hamming_config * conf)
{
    struct Matrix control = conf->control_matrix; // Récupération de la matrice de controle

    for(uint8_t i = 0; i < conf->m; i++)
        control = matrix_del_col(control, control.cols - 1); // On supprime les m dernière colonnes qui correspondent a l'identité

    struct Matrix gen = matrix_collapse_down(matrix_generate_identity(int_pow(2, conf->m) - 1 - conf->m), control) // On colle ensuite cette matrice avec l'identité
}

uint16_t hamming_length(struct Data * word1, struct Data * word2) // Renvoie la distance de hamming entre 2 codes
{
    // Formule valable en base 2 seulement
    unsigned int = 0;

    for(int i = 0; i < word1->data_number; i++)
        r + = data_get(&word1, i) ^ data_get(&word2, i);

    return r;
}

struct Hamming_config generate_config(uint8_t l, uint8_t m) // l = longueur des elements de la base, m = paramètre de hamming
{
    struct Hamming_config conf;
    struct Base base;

    // Configuration de la base
    base.d = int_pow(2, l);
    base.l = l;

    // Calcul des paramètres
    conf.total_size = (int_pow(d, m) - 1)/(d - 1);
    conf.word_size = conf.total_size - m;

    // Enregistrement des paramètres
    conf.base = base;
    conf.m = m;

    // Creation de la matrice de controle
    conf.control_matrix = hamming_generate_gen_matrix(&conf);

    return conf;
}
