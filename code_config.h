#define CODE_HAMMING 1
#define CODE_REPETITION 2
#define CODE_GOLAY 3

// --------- CONFIGURATION ------------ //

#define USED_CODE CODE_GOLAY // 1 = Hamming, 2 = Repetition

#if USED_CODE == CODE_HAMMING
    #ifndef HAMMING_CONFIG
        #define HAMMING_CONFIG

        // Hamming configuration
        #define M 3  // Hamming parameter <= 8
        #define N (1 << M) - 1 // Length of the encoded words
        #define K (N - M) // Length of the data word (without encoding)
    #endif
#elif USED_CODE == CODE_REPETITION
    #ifndef REPETITION_CONFIG
        #define REPETITION_CONFIG

        // Repetition code configuration
        #define M 2 // Size of packets
        #define N (M * 3) // Length of the encoded words
        #define K (M) // Length of the data word (without encoding)
    #endif
#elif USED_CODE == CODE_GOLAY
    #ifndef GOLAY_CONFIG
        #define GOLAY_CONFIG

        // Repetition code configuration
        #define N 23 // Length of the encoded words
        #define K 12 // Length of the data word (without encoding)
    #endif
#endif // USED_CODE

#if USED_CODE == CODE_HAMMING
    #if M > 8
        #error The hamming parameter must be inferior to 8
    #endif // M
#elif USED_CODE == CODE_REPETITION
    #if M > 4
        #error The repetition parameter must be inferior to 4
    #endif // M
#endif // USED_CODE
