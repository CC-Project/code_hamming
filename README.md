Library for the Hamming Code
============================
Implementation of the Hamming Codes (several available) for PC and AVR architectures.  

TODO
----
void matrix_show(struct Matrix* m);	// Prints out a matrix. Not adapted to avr.  
void data_show(struct Data* d);     // Prints out a data structure. Not adapted to AVR.  
struct Matrix* hamming_generate_generator_matrix(struct Hamming_config * conf); //// On supprime les m dernières colonnes qui correspondent a l'identité?  
Hamming.c and Hamming.h -> A lot of comments needed.  
Correct the names of the func  

Description
----------
The Hamming codes are linear error-correcting codes.   
The correction is performed using a generator matrix and a control matrix.  
Any linear code is equivalent to a systematic code, thus, the matrix are built like a systematic code.  

Note on the Matrix struct
-------------------------
Number of cols and rows are uint16_t -> Matrix max length is 65535 x 65535 (2^16 -1 * 2^16 - 1).  
A matrix can store numbers going until 2^BASE_L - 1  