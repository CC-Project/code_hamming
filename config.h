#ifndef CONFIG_H
    #define CONFIG_H
    #pragma once

    #include "hamming_config.h"

	// The following preprocessor code selects the architecture
	#ifdef __AVR__
        #ifndef AVR_WARNING
            #define AVR_WARNING
            #warning AVR plateform selected
        #endif // AVR_WARNING

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
    //#define DEBUG 1 // If enable, debugging routines will be compiled
#endif // CONFIG_H
