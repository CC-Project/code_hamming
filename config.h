#ifndef CONFIG_H
    #define CONFIG_H
    #define DEBUG 1 //If enable, debugging routines will be compiled

	//The following preprocessor code selects the architecture
	#ifdef __AVR__
        #warning AVR plateform selected
        #define BAUD_RATE 0x19      //38400
		#define F_CPU	16000000UL  //CPU clock frequency
		#include <avr/io.h>
		#define EXIT_FAILURE -1
    #else
        #warning Windows plateform selected
        #include <inttypes.h>
        #include <stdlib.h>
	#endif

    // Configurations. Warning: BASE_L <= 8
    #define BASE_L 1                // Length of the elements in the base chosen (For instance, in F_8: BASE_D = 8 but BASE_L = 3 because 8 = 2^3.)
    #define BASE_D (1 << BASE_L)    //Number of elements in the set. 2^l = d

    // Hamming configuration
    #define HAMMING_M 3  // Hamming parameter <= 8
    #define HAMMING_EXTENDED 0

#endif // CONFIG_H
