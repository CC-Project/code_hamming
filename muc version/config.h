#ifndef CONFIG_H
    #define CONFIG_H
	#ifdef __AVR__
        #warning AVR plateform selected
        #define BAUD_RATE 0x19      //38400
		#define F_CPU	16000000UL  //CPU clock frequency
		#include <avr/io.h>
    #else
        #warning Target is not an AVR
        #include <inttypes.h>
	#endif

	#include <math.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include "utilities.h"
	#include "data.h"		//Data structures
	#include "matrix.h"
	#include "hamming.h"


	//Defines the hamming parameters
	#define BASE_L 2			    // Length of the elements in the base (For instance, in F_8: d = 8 but l = 3)
	#define BASE_D ( 1 << BASE_L)   //Number of elements in the working set. 2^l = d


#endif // CONFIG_H
