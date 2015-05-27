#pragma once
#ifndef MATRIX_CODE_CONFIG_H
    #define MATRIX_CODE_CONFIG_H

    // Project configuration
    #define DEBUG // If enable, debugging routines will be compiled

    #include "code_config.h"

	// The following preprocessor code selects the architecture
	#ifdef __AVR__
        #ifndef AVR_WARNING
            #define AVR_WARNING
            #warning AVR plateform selected
        #endif // AVR_WARNING

        #define BAUD_RATE 0x19      //38400
		#define F_CPU	16000000UL  //CPU clock frequency
		#include <avr/io.h>
    #else
        #warning Windows plateform selected

        #include <inttypes.h>
        #include <stdlib.h>
	#endif

#endif // CONFIG_H
