#ifndef HAMMING_H
    #define HAMMING_H
    #include "utilities.h"  //Fonctions utilitaires
    #include "base.h"       //Structure d'indication de la base numérique
    #include "data.h"       //Structure de donnée Data
    #include "matrix.h"     //Implémentation des matrices

    struct Hamming_config
    {
        // Hamming code parameters
        uint8_t total_size;
        uint8_t word_size;
        uint8_t correction_size;

        struct Base base;   // Base de travail
        uint8_t m;          // Parametres d'encodage de Hamming (On travaillera avec m <= 8 pour des raisons pratiques)

        struct Matrix control_matrix; // La matrice de controle associée de taille (2^m - 1) x m
        struct Matrix generatrix_matrix; // La matrice génératrice
        struct Matrix syndrome_matrix; // Le tableau de syndromes (m <= 8 donc les syndrome sont codé sur 8 bits au max, d'ou le uint8_t)
    };

    // Function to initialize configuration
    struct Hamming_config hamming_generate_config(struct Base base, uint8_t m);
    void hamming_free_config(struct Hamming_config *conf);

    // Gestion des matrices de codage/ decodage
    struct Matrix hamming_generate_gen_matrix(struct Hamming_config * conf);
    struct Matrix hamming_generate_control_matrix(struct Hamming_config * conf);

    // Functions to manipulate data
    struct Matrix hamming_encode(struct Hamming_config * conf, struct Matrix * word);
    struct Matrix hamming_decode(struct Hamming_config * conf, struct Matrix * word);
    uint8_t hamming_check(struct Hamming_config * conf, struct Matrix * word); // Retourne en binaire le numero du bit defectueux

    // Data check to find the syndrome
    struct Matrix hamming_syndrome(struct Hamming_config * conf, struct Matrix * word); // Calcul le syndrome associé a un code
    struct Matrix hamming_generate_syndromes_matrix(struct Hamming_config * conf); // Generate the array of syndromes

#endif // HAMMING_H
