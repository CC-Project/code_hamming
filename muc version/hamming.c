#include "hamming.h"

struct Matrix hamming_encode(struct Hamming_config * conf, struct Matrix * word)
{
    struct Matrix result = matrix_mul(&(conf->generatrix_matrix), word);
    return result;
}

struct Matrix hamming_decode(struct Hamming_config * conf, struct Matrix * word)
{
    struct Matrix word_decode = matrix_generate(conf->word_size, 1);

    for(uint16_t i = 1; i <= conf->word_size; i++)
        matrix_set(&word_decode, i, 1, matrix_get(word, i, 1));

    return word_decode;
}

void hamming_fill_syndromes_array(struct Hamming_config * conf)
{
    struct Matrix d = matrix_generate(conf->total_size, 1); struct Matrix dc;
    uint8_t synd; uint16_t nb;

    // Pour la base 2
    for(uint16_t i = 1; i <= conf->total_size; i++)
    {
        nb = conf->total_size - i + 1;
        matrix_set(&d, nb, 1, 1);
        dc = hamming_syndrome(conf, &d);

        // Ici, on sait que m <= 8. donc que dc est codé sur 8 bits
        synd = matrix_word_to_int(&dc); // On récupère le syndrome sous forme d'entier

        if(synd != 0 && conf->syndrome_array[synd] == 0) // Si le syndrome n'a pas deja ete calcule
            conf->syndrome_array[synd] = conf->total_size - i; // On le met a jour

        matrix_set(&d, nb, 1, 0);
    }
    // Frees memory
    matrix_free(&d);
    matrix_free(&dc);
}

uint8_t hamming_check_syndrome(struct Hamming_config * conf, struct Matrix * synd)
{
    return conf->syndrome_array[matrix_word_to_int(synd)];
}

struct Matrix hamming_correction(struct Hamming_config * conf, struct Matrix * word)
{
    struct Matrix synd = hamming_syndrome(conf, word);

    if(!matrix_isempty(&synd))
    {
        struct Matrix word_correct = matrix_copy(word);
        uint8_t synd_check = hamming_check_syndrome(conf, &synd) + 1;

        matrix_set(&word_correct, synd_check, 1, opposite_word(matrix_get(word, synd_check, 1)));

        return word_correct;
    }
    else
        return *word;
}

struct Matrix hamming_syndrome(struct Hamming_config *conf, struct Matrix * word)
{
    struct Matrix r = matrix_mul(&(conf->control_matrix), word);
    return r; // On retourne le nombre en binaire correspondant au syndrome (=> que la matrice data reçu soit d'une taille < 255 lignes, m < 8)
}

struct Matrix hamming_generate_control_matrix(struct Hamming_config * conf)
{
    uint16_t cols = (1 << conf->m );
    struct Matrix control = matrix_generate(conf->m, cols); // Generation de la matrice de controle
    // C'est ici qu'intervient la condition m <= 12, en effet, data ne peut contenir que 2^16 data, en resolvant m*2^m <= 2^16 on trouve m <= 12

    // Remplissage de la matrice de controle
    /* Principe pour la base 2 :
        On remplit la matrice de maniere recursive avec les vecteur de la base canonique de 2^m
        On supprime ensuite les lignes 2^i avec i dans [0,m-1]
    */

    for(uint8_t i = 1; i <= conf->m; i++)
        for(uint16_t j = 1; j <= cols; j++)
            if(((j - 1) / (1 << (conf->m - i))) % 2 == 0)
                matrix_set(&control, i, j, 0);
            else
                matrix_set(&control, i, j, 1);

    // On rend la matrice systématique
    matrix_del_col(1, &control);

    for(uint8_t j = 0; j < conf->m; j++)
        matrix_del_col((1 << j) - j, &control);

    struct Matrix identity = matrix_generate(conf->m, conf->m);
    matrix_make_identity(&identity);

    return matrix_collapse_right(&control, &identity);
}

struct Matrix hamming_generate_gen_matrix(struct Hamming_config * conf)
{
    struct Matrix control = matrix_copy(&(conf->control_matrix)); // Récupération de la matrice de controle

    for(uint8_t i = 1; i <= control.rows; i++)
        matrix_del_col(control.cols, &control); // On supprime les m dernières colonnes qui correspondent a l'identité

    struct Matrix identity = matrix_generate(control.cols, control.cols);
    matrix_make_identity(&identity);

    struct Matrix gen = matrix_collapse_down(&identity, &control); // On colle ensuite cette matrice avec l'identité
    return gen;
}

struct Hamming_config hamming_generate_config(uint8_t m) // l = longueur des elements de la base, m = paramètre de hamming
{
    struct Hamming_config conf;

    // ### Calcul des paramètres
    conf.total_size = (int_pow(BASE_D, m) - 1)/(BASE_D - 1);
    conf.word_size = conf.total_size - m;

    conf.correction_size = 3; // 3 = code de hamming simple

    // ### Enregistrement des paramètres
    conf.m = m;

    // ### Creation de la matrice de controle
    conf.control_matrix = hamming_generate_control_matrix(&conf);
    conf.generatrix_matrix = hamming_generate_gen_matrix(&conf);

    // ### Generation du tableau de syndromes
    // Allocation dynamique
    uint16_t nb_alloc = (1 << conf.m);
    conf.syndrome_array = malloc(nb_alloc * sizeof(uint8_t));

    // Verification de l'allocation
    if ( conf.syndrome_array == NULL )
         error("ERROR : hamming_generate_config : Dynamic allocation not possible (syndrome_array)");

    // Réinitialisation des cases
    for(uint16_t i = 0; i < nb_alloc; i++)
        conf.syndrome_array[i] = 0;

    // Filling
    hamming_fill_syndromes_array(&conf);

    return conf;
}

void hamming_free_config(struct Hamming_config *conf)
{
    matrix_free(&(conf->generatrix_matrix));
    matrix_free(&(conf->control_matrix));

    free(conf->syndrome_array);
    free(conf);
}
