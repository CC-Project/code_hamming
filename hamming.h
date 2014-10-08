#ifndef HAMMING_H
    #define HAMMING_H
    #include "utilities.h"  //Fonctions utilitaires
    #include "base.h"       //Structure d'indication de la base num�rique
    #include "data.h"       //Structure de donn�e Data
    #include "matrix.h"     //Impl�mentation des matrices

    struct Hamming_config
    {
        // Hamming code parameters
        uint8_t total_size;
        uint8_t word_size;
        uint8_t correction_size;

        struct Base base;   // Base de travail
        uint8_t m;          // Parametres d'encodage de Hamming (On travaillera avec m < 16 pour des raisons de place m�moire)

        struct Matrix control_matrix; // La matrice de controle associ�e de taille (2^m - 1) x m
        struct Matrix generatrix_matrix; // La matrice g�n�ratrice
    };

    // Function to initialize configuration
    struct Hamming_config hamming_generate_config(uint8_t l, uint8_t m);

    // Gestion des matrices de codage/ decodage
    struct Matrix hamming_generate_gen_matrix(struct Hamming_config * conf);
    struct Matrix hamming_generate_control_matrix(struct Hamming_config * conf);

    // Functions to manipulate data
    struct Data hamming_encode(struct Hamming_config * conf, struct Data * word);

    // Data check to find errors
    int16_t hamming_check(struct Hamming_config * conf, struct Data * word);

#endif // HAMMING_H
