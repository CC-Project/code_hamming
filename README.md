Library for the Hamming Code
==================================
Implementation of the Hamming Codes (several available) for PC and AVR architectures.

TODO
====
void matrix_show(struct Matrix* m);	// Prints out a matrix. Not adapted to avr.
void data_show(struct Data* d);     // Prints out a data structure. Not adapted to AVR.
Comment la matrice de controle est calculée? Pourquoi on calcule pas plutot la matrice génératrice, et à partir de celle ci, on en déduit la matrice de controle?
Pourquoi BASE_L <= 8 ?
Hamming.c : Fonction hamming_free_config: pourquoi pas un data_free au lieu du free(&(conf->SYNDROMES_ARRAY)) ?

Description
===========
The Hamming codes are linear error-correcting codes. 
The correction is performed using a generator matrix and a control matrix.
Any linear code is equivalent to a systematic code, thus, the matrix are built like a systematic code.
