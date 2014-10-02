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

}
struct Matrix hamming_generate_gen_matrix(struct Hamming_config * conf)
{

}


unsigned int hamming_length(struct Data * word1, struct Data * word2) // Renvoie la distance de hamming entre 2 codes
{
    // Formule valable en base 2 seulement
    unsigned int = 0;

    for(int i = 0; i < word1->data_number; i++)
        r + = data_get(&word1, i) ^ data_get(&word2, i);

    return r;
}

struct Hamming_config generate_config(unsigned short int l, unsigned short int m) // l = longueur des elements de la base, m = param�tre de hamming
{
    struct Hamming_config conf;
    struct Base base;

    // Configuration de la base
    base.d = int_pow(2, l);
    base.l = l;

    // Calcul des param�tres
    conf.total_size = (int_pow(d, m) - 1)/(d - 1);
    conf.word_size = conf.total_size - m;

    // Enregistrement des param�tres
    conf.base = base;
    conf.m = m;

    // Creation de la matrice de controle
    conf.control_matrix = hamming_generate_gen_matrix(&conf);

    return conf;
}
