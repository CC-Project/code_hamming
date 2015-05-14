#ifndef HAMMING_CONFIG_H
    #define HAMMING_CONFIG_H

    // Hamming configuration
    #define M 3  // Hamming parameter <= 8
    #define N (1 << M) - 1 //Length of the encoded words
    #define K N-M //Length of the data word (without encoding)
#endif // HAMMING_CONFIG_H_INCLUDED
