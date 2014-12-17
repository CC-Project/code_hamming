#ifndef UTILITIES_H
    #define UTILITIES_H
    #include "config.h"
    #include "data.h"
    #include "matrix.h"
    #include <stdio.h>

    #ifdef __AVR__
        void uart_init(void);
        void uart_tx_char(char c);
        void uart_tx_str(int8_t* str);
        void uart_newline(void);
        int freeRam(); //Returns the memory available
    #else
        char bin_to_ascii(uint8_t bin);
        uint8_t ascii_to_bin(char bin);
    #endif

    uint8_t error(char* str); // Exit the program with the error code EXIT_FAILED
    void print_var_bits(uint8_t var);
    uint16_t int_pow(uint16_t a, uint16_t b);   //Computes a^b
    uint8_t opposite_word(uint8_t word);        //Returns the opposite word (10011 -> 01100)
    uint8_t opposite_bit(uint8_t bit);
    uint16_t rand_a_b(uint16_t a, uint16_t b);  //Returns a random number between a and b (inclusive)
    //uint8_t xor_bit_to_bit(uint8_t a, uint8_t b);   //Not finished

#endif // UTILITIES_H
