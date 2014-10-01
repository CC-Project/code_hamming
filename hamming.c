#include "hamming.h"
#include <math.h>

struct Data hamming_encode(struct Hamming_config * conf, struct Data * word)
{
    struct Matrix word_matrix = new_matrix(word->data_number, 1);
    word_matrix->data = word;

    struct Matrix result = mul_matrix(conf->control_matrix, word_matrix);
    return result.data;
}
/*
struct Data hamming_decode(struct * Hamming_config conf, struct Data * word)
{

}

struct Data hamming_check(struct * Hamming_config conf, struct Data * word)


struct Matrix hamming_generate_control_matrix(struct Hamming_config * conf)
{

}
*/

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
    conf.control_matrix = hamming_generate_control_matrix(&conf);

    return conf;
}
