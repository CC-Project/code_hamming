#ifndef CODE_MATRIX_H
    #define CODE_MATRIX_H
    #pragma once

    #ifdef __AVR__
        #include <avr/pgmspace.h>
    #endif // __AVR__

    #include <inttypes.h>
    #include <stdlib.h>
    #include "../../lib_utilities/utilities.h"
    #include "../../lib_data/data.h"
    #include "../config.h"
    #include "matrix.h"

    struct Matrix_config
    {
        struct Matrix* CONTROL_MATRIX;
        struct Matrix* GENERATOR_MATRIX;
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
    uint8_t* cmatrix_get_erroneous_bits(struct Matrix* word); // Retourne en binaire les numeros des bits defectueux
    #define cmatrix_syndrome(word, conf) matrix_mul(conf->CONTROL_MATRIX, word);
#endif // HAMMING_H
