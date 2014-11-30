#ifndef HAMMING_H
    #define HAMMING_H
    #include "config.h"

    struct Hamming_config
    {
        // Hamming code parameters
        uint8_t total_size;
        uint8_t word_size;
        uint8_t correction_size;
        uint8_t m;          	            // Encoding parameters

        struct Matrix control_matrix; 		// La matrice de controle associée de taille (2^m - 1) x m
        struct Matrix generatrix_matrix; 	// Generator matrix
        uint8_t* syndrome_array; 			// Le tableau de syndromes (m <= 8 donc les syndrome sont codé sur 8 bits au max, d'ou le uint8_t)
    };

    // Function to initialize configuration
    struct Hamming_config hamming_generate_config(uint8_t m);
    void hamming_free_config(struct Hamming_config *conf);

    // Gestion des matrices de codage/ decodage
    struct Matrix hamming_generate_gen_matrix(struct Hamming_config * conf);
    struct Matrix hamming_generate_control_matrix(struct Hamming_config * conf);

    // Functions to manipulate data
    struct Matrix hamming_encode(struct Hamming_config * conf, struct Matrix * word);
    struct Matrix hamming_decode(struct Hamming_config * conf, struct Matrix * word);
    uint8_t hamming_check_syndrome(struct Hamming_config * conf, struct Matrix * word); // Retourne en binaire le numero du bit defectueux
    struct Matrix hamming_correction(struct Hamming_config * conf, struct Matrix * word);

    // Data check to find the syndrome
    struct Matrix hamming_syndrome(struct Hamming_config *conf, struct Matrix * word); // Calcul le syndrome associé a un code
    void hamming_fill_syndromes_array(struct Hamming_config * conf); // Generate the array of syndromes

#endif // HAMMING_H
