#ifndef CONFIG_H
    #define CONFIG_H
    #pragma once

	// The following preprocessor code selects the architecture
	#ifdef __AVR__
        #warning AVR plateform selected
        #define BAUD_RATE 0x19      //38400
		#define F_CPU	16000000UL  //CPU clock frequency
		#include <avr/io.h>
		#define EXIT_FAILURE -1
		#define EXIT_SUCCESS 1
    #else
        #warning Windows plateform selected

        #include <inttypes.h>
        #include <stdlib.h>
	#endif
	// Project configuration
    #define DEBUG 1 // If enable, debugging routines will be compiled

    // Hamming configuration
    #define M 3  // Hamming parameter <= 8
    #define N (1 << M) - 1 //Length of the encoded words
    #define K N-M //Length of the data word (without encoding)

#endif // CONFIG_H
