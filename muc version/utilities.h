#ifndef UTILITIES_H
    #define UTILITIES_H

    #ifdef __AVR__
        void uart_init(void);
        void uart_tx_char(char c);
        void uart_tx_str(int8_t* str);
        void uart_newline(void);
    #else
    #endif

    void error(char* str);
    uint16_t int_pow(uint16_t a, uint16_t b);   //Computes a^b
    void print_var_bits(uint8_t var);
    uint8_t opposite_word(uint8_t word);        //Returns the opposite word (10011 -> 01100). Not finished
    int rand_a_b(int a, int b);                 //Returns a random number between a and b (inclusive)
    char bin_to_ascii(uint8_t bin);
    uint8_t ascii_to_bin(char bin);

#endif // UTILITIES_H
