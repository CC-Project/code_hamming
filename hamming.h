#ifndef HAMMING_H
    #define HAMMING_H
    #include "data.h"
    #include "matrix.h"

    struct Hamming_config
    {
        // Hamming code parameters
        uint8_t EW_SIZE; // Total size of the encoded words
        uint8_t W_SIZE; // Size of word
        uint8_t C_SIZE; // Size of the correction

        // Corrections matrix
        struct Matrix CONTROL_MATRIX; // Size: (2^m - 1) * m
        struct Matrix GENERATOR_MATRIX;
        struct Data* SYNDROMES_ARRAY; // Le tableau de syndromes (m <= 8 donc les syndrome sont codé sur 8 bits au max, d'ou le uint8_t)
    };

    // Set up
    struct Hamming_config hamming_generate_config();
    void hamming_free_config(struct Hamming_config *conf);

    // Coding and decoding matrix
    struct Matrix hamming_generate_generator_matrix(struct Hamming_config * conf);
    struct Matrix hamming_generate_control_matrix(struct Hamming_config * conf);
    struct Data* hamming_generate_syndromes_array(struct Hamming_config * conf); // Generate the array of syndromes

    // Manipulation of data
    struct Matrix hamming_encode(struct Matrix * word, struct Hamming_config * conf);
    struct Matrix hamming_decode(struct Matrix * word, struct Hamming_config * conf);
    struct Matrix hamming_correction(struct Matrix * word, struct Hamming_config * conf);
    uint8_t hamming_check_syndrome(struct Matrix * word, struct Hamming_config * conf); // Retourne en binaire le numero du bit defectueux
    struct Matrix hamming_syndrome(struct Matrix * word, struct Hamming_config *conf); // Calcul le syndrome associé a un code

#endif // HAMMING_H
