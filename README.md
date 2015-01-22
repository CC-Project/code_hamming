Library for the Hamming Code
============================
Implementation of the Hamming Codes for PC and AVR architectures.  
The set of the symbols used is {0,1}.  

TODO
----
void matrix_show(struct Matrix* m);	// Prints out a matrix. Not adapted to avr.  
void data_show(struct Data* d);     // Prints out a data structure. Not adapted to AVR.  
Optimize the code in data_get.  
Adapt to work with BASE_L > 1.  
Hamming extended code.  
Check if utilities.h doesnt include shit.  

Notes on the config file
------------------------
The DEBUG macro allows to compile functions to control the proceedings of the program.  
If working with AVR devices, you need to change BAUD_RATE and F_CPU (CPU clock frequency).  
BASE_L is the length of the elements in the base chosen. For instance, if set to 1, the set of words will be {0,1}. 
However, if BASE_L is set to 2, then the set of words will be {11, 10, 01, 00}. 
It must be set under 8.  
BASE_D is the number of elements in the set. 2^BASE_L = BASE_D.  
HAMMING_M is the Hamming parameter <= 8  
HAMMING_EXTENDED indicates wether or not the extended codes are enabled.  


Note on the Matrix struct
-------------------------
Number of cols and rows are uint16_t -> Matrix max length is 65535 x 65535 (2^16 -1 * 2^16 - 1).  
A matrix can store numbers going until 2^BASE_L - 1