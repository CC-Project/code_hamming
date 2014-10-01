#include "matrix.h"

struct Hamming_config
{
	unsigned short int total_size;
	unsigned short int word_size;
	unsigned short int correction_size;
	// --- //
	unsigned short int m; // Parametres d'encodage de Hamming
	struct Base base; // Base de travail
	// --- //
	struct Matrix control_matrix; // La matrice de controle associée
};

struct Data hamming_encode(struct Hamming_config * conf, struct Data * word);
struct Hamming_config generate_config(unsigned short int d, unsigned short int m);

