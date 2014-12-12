#ifndef CONFIG_H
    #define CONFIG_H

    #define DEBUG 1 //If enable, utilities routines will be compiled

	//The following preprocessor code selects the architecture
	#ifdef __AVR__
        #warning AVR plateform selected
        #define BAUD_RATE 0x19      //38400
		#define F_CPU	16000000UL  //CPU clock frequency
		#include <avr/io.h>
		#define EXIT_FAILURE -1
    #else
        #warning Target is not an AVR
        #include <inttypes.h>
        #include <stdlib.h>
	#endif

    // Configurations
    #define BASE_L 1                // Length of the elements in the base (For instance, in F_8: d = 8 but l = 3)
    #define BASE_D (1 << BASE_L)    //Number of elements in the working set. 2^l = d
    // Warning : BASE_L <= 8

    // Hamming configuration
    #define HAMMING_M 4  // Hamming parameter <= 8
    #define HAMMING_EXTENDED 0

#endif // CONFIG_H
