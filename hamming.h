#include "matrix.h"

struct Hamming_config
{
	unsigned short int total_size;
	unsigned short int word_size;
	unsigned short int correction_size;
	// --- //
    struct Base base; // Base de travail
	unsigned short int m; // Parametres d'encodage de Hamming
	// --- //
	struct Matrix control_matrix; // La matrice de controle associée
};

struct Data hamming_encode(struct Hamming_config * conf, struct Data * word);
unsigned int hamming_length(struct Data * word1, struct Data * word2);
struct Hamming_config generate_config(unsigned short int l, unsigned short int m);


