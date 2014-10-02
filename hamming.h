#include "matrix.h"

struct Hamming_config
{
	uint8_t total_size;
	uint8_t word_size;
	uint8_t correction_size;
	// --- //
    struct Base base; // Base de travail
	uint8_t m; // Parametres d'encodage de Hamming (On travaillera avec m < 16 pour des raisons de place m�moire)
	// --- //
	struct Matrix control_matrix; // La matrice de controle associ�e de taille (2^m - 1) x m
};

struct Data hamming_encode(struct Hamming_config * conf, struct Data * word);
uint16_t hamming_length(struct Data * word1, struct Data * word2);
struct Hamming_config generate_config(uint8_t l, uint8_t m);


