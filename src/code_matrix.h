#ifndef HAMMING_H
    #define HAMMING_H
    #pragma once

    #ifndef __AVR__
        #include <inttypes.h>
        #include <stdlib.h>
    #endif // __AVR__

    // Include
    #include "../../lib_utilities/utilities.h"
    #include "../../lib_data/data.h"
    #include "../config.h"
    #include "matrix.h"

    struct Matrix_config
    {
        // Corrections matrix
        struct Matrix* CONTROL_MATRIX; // Size: (2^m - 1) * m
        struct Matrix* GENERATOR_MATRIX;
        uint8_t* SYNDROMES_ARRAY; // Syndrom array (m <= 8 donc les syndrome sont codé sur 8 bits au max, d'ou le uint8_t)
    };

    // Set up
    struct Matrix_config* cmatrix_generate_config();
    void cmatrix_free_config(struct Matrix_config* conf);

    // Coding and decoding matrix
    void cmatrix_generate_generator_matrix(struct Matrix_config* conf);
    void cmatrix_generate_control_matrix(struct Matrix_config* conf);
    void cmatrix_generate_syndromes_array(struct Matrix_config* conf); // Generate the array of syndromes

    // Manipulation of data
    struct Matrix* cmatrix_encode(struct Matrix* word, struct Matrix_config* conf);
    struct Matrix* cmatrix_decode(struct Matrix* word, struct Matrix_config* conf);
    struct Matrix* cmatrix_extract(struct Matrix * word, struct Matrix_config * conf);

    struct Matrix* cmatrix_correction(struct Matrix* word, struct Matrix_config* conf);
    struct Matrix* cmatrix_syndrome(struct Matrix* word, struct Matrix_config*conf); // Calcul le syndrome associé a un code
    uint8_t cmatrix_check_syndrome(struct Matrix* word, struct Matrix_config* conf); // Retourne en binaire le numero du bit defectueux
#endif // HAMMING_H
