#include "code_matrix.h"

#else
    #if CODE_USED == CODE_HAMMING
        #if M == 2
            uint8_t synd_array[4][1] PROGMEM = {{0}, {2}, {1}, {0}};
        #elif M == 3
            uint8_t synd_array[8][1] PROGMEM = {{0}, {6}, {5}, {0}, {4}, {1}, {2}, {3}};
        #elif M == 4
            uint8_t synd_array[16][1] PROGMEM = {{0}, {14}, {13}, {0}, {12}, {1}, {2}, {3}, {11}, {4}, {5}, {6}, {7}, {8}, {9}, {10}};
        #elif M == 5
            uint8_t synd_array[32][1] PROGMEM = {{0}, {30}, {29}, {0}, {28}, {1}, {2}, {3}, {27}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {26}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19}, {20}, {21}, {22}, {23}, {24}, {25}};
        #elif M == 6
            uint8_t synd_array[64][1] PROGMEM = {{0}, {62}, {61}, {0}, {60}, {1}, {2}, {3}, {59}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {58}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19}, {20}, {21}, {22}, {23}, {24}, {25}, {57}, {26}, {27}, {28}, {29}, {30}, {31}, {32}, {33}, {34}, {35}, {36}, {37}, {38}, {39}, {40}, {41}, {42}, {43}, {44}, {45}, {46}, {47}, {48}, {49}, {50}, {51}, {52}, {53}, {54}, {55}, {56}};
        #elif M == 7
            uint8_t synd_array[128][1] PROGMEM = {{0}, {126}, {125}, {0}, {124}, {1}, {2}, {3}, {123}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {122}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19}, {20}, {21}, {22}, {23}, {24}, {25}, {121}, {26}, {27}, {28}, {29}, {30}, {31}, {32}, {33}, {34}, {35}, {36}, {37}, {38}, {39}, {40}, {41}, {42}, {43}, {44}, {45}, {46}, {47}, {48}, {49}, {50}, {51}, {52}, {53}, {54}, {55}, {56}, {120}, {57}, {58}, {59}, {60}, {61}, {62}, {63}, {64}, {65}, {66}, {67}, {68}, {69}, {70}, {71}, {72}, {73}, {74}, {75}, {76}, {77}, {78}, {79}, {80}, {81}, {82}, {83}, {84}, {85}, {86}, {87}, {88}, {89}, {90}, {91}, {92}, {93}, {94}, {95}, {96}, {97}, {98}, {99}, {100}, {101}, {102}, {103}, {104}, {105}, {106}, {107}, {108}, {109}, {110}, {111}, {112}, {113}, {114}, {115}, {116}, {117}, {118}, {119}};
        #elif M == 8
            uint8_t synd_array[256][1] PROGMEM = {{0}, {254}, {253}, {0}, {252}, {1}, {2}, {3}, {251}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {250}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19}, {20}, {21}, {22}, {23}, {24}, {25}, {249}, {26}, {27}, {28}, {29}, {30}, {31}, {32}, {33}, {34}, {35}, {36}, {37}, {38}, {39}, {40}, {41}, {42}, {43}, {44}, {45}, {46}, {47}, {48}, {49}, {50}, {51}, {52}, {53}, {54}, {55}, {56}, {248}, {57}, {58}, {59}, {60}, {61}, {62}, {63}, {64}, {65}, {66}, {67}, {68}, {69}, {70}, {71}, {72}, {73}, {74}, {75}, {76}, {77}, {78}, {79}, {80}, {81}, {82}, {83}, {84}, {85}, {86}, {87}, {88}, {89}, {90}, {91}, {92}, {93}, {94}, {95}, {96}, {97}, {98}, {99}, {100}, {101}, {102}, {103}, {104}, {105}, {106}, {107}, {108}, {109}, {110}, {111}, {112}, {113}, {114}, {115}, {116}, {117}, {118}, {119}, {247}, {120}, {121}, {122}, {123}, {124}, {125}, {126}, {127}, {128}, {129}, {130}, {131}, {132}, {133}, {134}, {135}, {136}, {137}, {138}, {139}, {140}, {141}, {142}, {143}, {144}, {145}, {146}, {147}, {148}, {149}, {150}, {151}, {152}, {153}, {154}, {155}, {156}, {157}, {158}, {159}, {160}, {161}, {162}, {163}, {164}, {165}, {166}, {167}, {168}, {169}, {170}, {171}, {172}, {173}, {174}, {175}, {176}, {177}, {178}, {179}, {180}, {181}, {182}, {183}, {184}, {185}, {186}, {187}, {188}, {189}, {190}, {191}, {192}, {193}, {194}, {195}, {196}, {197}, {198}, {199}, {200}, {201}, {202}, {203}, {204}, {205}, {206}, {207}, {208}, {209}, {210}, {211}, {212}, {213}, {214}, {215}, {216}, {217}, {218}, {219}, {220}, {221}, {222}, {223}, {224}, {225}, {226}, {227}, {228}, {229}, {230}, {231}, {232}, {233}, {234}, {235}, {236}, {237}, {238}, {239}, {240}, {241}, {242}, {243}, {244}, {245}, {246}};
        #endif // M
    #endif // CODE_USED
#endif

// Set up
struct Matrix_config* cmatrix_generate_config()
{
    struct Matrix_config* config = malloc(sizeof(struct Matrix_config));

    cmatrix_generate_control_matrix(config);
    cmatrix_generate_generator_matrix(config);
    cmatrix_generate_syndromes_array(config);

    return config;
}

void cmatrix_free_config(struct Matrix_config *conf)
{
    matrix_free(conf->CONTROL_MATRIX);
    matrix_free(conf->GENERATOR_MATRIX);
    free(conf->SYNDROMES_ARRAY);
    free(conf);
}

// -------------- Coding and decoding matrix ------------------
void cmatrix_generate_control_matrix(struct Matrix_config * conf)
{
    #if USED_CODE == CODE_HAMMING // Hamming code
        struct Matrix* control  = matrix_generate(M, (1 << M)); // Generation of the control matrix

        // C'est ici qu'intervient une condition sur m : m <= 12, en effet, data ne peut contenir que 2^16 data, en resolvant m*2^m <= 2^16 on trouve m <= 12

        // Fills the control matrix
        for(uint16_t i = 1; i <= M; i++)
            for(uint16_t j = 1; j <= (1 << M); j++)
                if(((j - 1) / (1 << (M - i))) % 2 == 0)
                    matrix_set(control, i, j, 0);
                else
                    matrix_set(control, i, j, 1);

        // Make the matrix systematic
        matrix_del_col(1, control);

        //Sub the identity
        for(uint8_t j = 0; j < M; j++)
            matrix_del_col((1 << j) - j, control);

        struct Matrix* identity = matrix_generate(M, M);
        matrix_make_identity(identity);

        conf->CONTROL_MATRIX  = matrix_concat_right(control, identity);

        // Frees memory
        matrix_free(identity);
        matrix_free(control);
    #elif USED_CODE == CODE_REPETITION
        struct Matrix* control = matrix_generate((uint16_t)(K * 2), (uint16_t)(K));

        for(uint8_t i = 0; i < K; i++)
            for(uint8_t p = 0; p < 2; p++)
                matrix_set(control, (p * K + i) + 1, i + 1, 1);

        struct Matrix* identity = matrix_generate((uint16_t)(K * 2), (uint16_t)(K * 2));
        matrix_make_identity(identity);

        conf->CONTROL_MATRIX = matrix_concat_right(control, identity); //Merge it with the identity

        matrix_free(identity); matrix_free(control);
    #endif // HAMMING_CONFIG
}

void cmatrix_generate_generator_matrix(struct Matrix_config * conf)
{
    #if USED_CODE == CODE_HAMMING // Hamming code
        // Get the control matrix
        struct Matrix* control = matrix_copy(conf->CONTROL_MATRIX);

        for(uint8_t i = 1; i <= control->rows; i++)
            matrix_del_col(control->cols, control); //Removes the m last cols

        struct Matrix* identity = matrix_generate(control->cols, control->cols);
        matrix_make_identity(identity);

        conf->GENERATOR_MATRIX = matrix_concat_down(identity, control); //Merge it with the identity

        // Frees memory
        matrix_free(identity);
        matrix_free(control);
    #elif USED_CODE == CODE_REPETITION
        struct Matrix* generator = matrix_generate((uint16_t)(K * 3), (uint16_t)(K));

        for(uint8_t i = 0; i < K; i++)
            for(uint8_t p = 0; p < 3; p++)
                matrix_set(generator, (p * K + i) + 1, i + 1, 1);

        conf->GENERATOR_MATRIX = generator;
    #endif // HAMMING_CONFIG
}


void cmatrix_generate_syndromes_array(struct Matrix_config * conf)
{
    #ifndef __AVR__
        #if USED_CODE == CODE_HAMMING
            conf->SYNDROMES_ARRAY = calloc((1 << conf->CONTROL_MATRIX->rows), sizeof(uint8_t)); // = 2^m
            struct Matrix* syndrome_test_matrix = matrix_generate(N, 1);
            struct Matrix* syndrome_result;
            uint8_t syndrome;

            // Correction de seulement une erreur (valable pour tout les codes)
            for(uint8_t i = 0; i < N; i++)
            {
                // Sets the "N - i" bit
                matrix_set(syndrome_test_matrix, N - i, 1, 1);

                // Computation of the syndrome
                syndrome_result = cmatrix_syndrome(syndrome_test_matrix, conf);
                syndrome = matrix_word_to_int(syndrome_result);

                // Adds the syndrome
                if(conf->SYNDROMES_ARRAY[syndrome] == 0)
                    conf->SYNDROMES_ARRAY[syndrome] = N - i - 1;

                // Resets the bit
                matrix_set(syndrome_test_matrix, N - i, 1, 0);
                matrix_free(syndrome_result);
            }

            matrix_free(syndrome_test_matrix);
            /*
            // Code général
            conf->SYNDROMES_ARRAY = calloc((1 << conf->CONTROL_MATRIX->rows), sizeof(SIZE_SYNDROME_ALLOCATION)); // = 2^m
            struct Matrix* syndrome_test_matrix = matrix_generate(N, 1);
            struct Matrix* syndrome_result;
            uint16_t syndrome;

            // Correction de seulement une erreur (valable pour tout les codes)
            for(SIZE_SYNDROME_ALLOCATION i = 0; i < N; i++)
            {
                // Sets the "N - i" bit
                matrix_set(syndrome_test_matrix, N - i, 1, 1);

                // Computation of the syndrome
                syndrome_result = cmatrix_syndrome(syndrome_test_matrix, conf);
                syndrome = matrix_word_to_int(syndrome_result);

                // Adds the syndrome
                if(conf->SYNDROMES_ARRAY[syndrome] == 0)
                    conf->SYNDROMES_ARRAY[syndrome] = N - i - 1;

                // Resets the bit
                matrix_set(syndrome_test_matrix, N - i, 1, 0);
                matrix_free(syndrome_result);
            }

            matrix_free(syndrome_test_matrix);
            */
        #else
            #if CODE_USED == CODE_HAMMING
                #if M == 2
                    uint8_t synd_array[4][1] PROGMEM = {{0}, {2}, {1}, {0}};
                #elif M == 3
                    uint8_t synd_array[8][1] PROGMEM = {{0}, {6}, {5}, {0}, {4}, {1}, {2}, {3}};
                #elif M == 4
                    uint8_t synd_array[16][1] PROGMEM = {{0}, {14}, {13}, {0}, {12}, {1}, {2}, {3}, {11}, {4}, {5}, {6}, {7}, {8}, {9}, {10}};
                #elif M == 5
                    uint8_t synd_array[32][1] PROGMEM = {{0}, {30}, {29}, {0}, {28}, {1}, {2}, {3}, {27}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {26}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19}, {20}, {21}, {22}, {23}, {24}, {25}};
                #elif M == 6
                    uint8_t synd_array[64][1] PROGMEM = {{0}, {62}, {61}, {0}, {60}, {1}, {2}, {3}, {59}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {58}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19}, {20}, {21}, {22}, {23}, {24}, {25}, {57}, {26}, {27}, {28}, {29}, {30}, {31}, {32}, {33}, {34}, {35}, {36}, {37}, {38}, {39}, {40}, {41}, {42}, {43}, {44}, {45}, {46}, {47}, {48}, {49}, {50}, {51}, {52}, {53}, {54}, {55}, {56}};
                #elif M == 7
                    uint8_t synd_array[128][1] PROGMEM = {{0}, {126}, {125}, {0}, {124}, {1}, {2}, {3}, {123}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {122}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19}, {20}, {21}, {22}, {23}, {24}, {25}, {121}, {26}, {27}, {28}, {29}, {30}, {31}, {32}, {33}, {34}, {35}, {36}, {37}, {38}, {39}, {40}, {41}, {42}, {43}, {44}, {45}, {46}, {47}, {48}, {49}, {50}, {51}, {52}, {53}, {54}, {55}, {56}, {120}, {57}, {58}, {59}, {60}, {61}, {62}, {63}, {64}, {65}, {66}, {67}, {68}, {69}, {70}, {71}, {72}, {73}, {74}, {75}, {76}, {77}, {78}, {79}, {80}, {81}, {82}, {83}, {84}, {85}, {86}, {87}, {88}, {89}, {90}, {91}, {92}, {93}, {94}, {95}, {96}, {97}, {98}, {99}, {100}, {101}, {102}, {103}, {104}, {105}, {106}, {107}, {108}, {109}, {110}, {111}, {112}, {113}, {114}, {115}, {116}, {117}, {118}, {119}};
                #elif M == 8
                    uint8_t synd_array[256][1] PROGMEM = {{0}, {254}, {253}, {0}, {252}, {1}, {2}, {3}, {251}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {250}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19}, {20}, {21}, {22}, {23}, {24}, {25}, {249}, {26}, {27}, {28}, {29}, {30}, {31}, {32}, {33}, {34}, {35}, {36}, {37}, {38}, {39}, {40}, {41}, {42}, {43}, {44}, {45}, {46}, {47}, {48}, {49}, {50}, {51}, {52}, {53}, {54}, {55}, {56}, {248}, {57}, {58}, {59}, {60}, {61}, {62}, {63}, {64}, {65}, {66}, {67}, {68}, {69}, {70}, {71}, {72}, {73}, {74}, {75}, {76}, {77}, {78}, {79}, {80}, {81}, {82}, {83}, {84}, {85}, {86}, {87}, {88}, {89}, {90}, {91}, {92}, {93}, {94}, {95}, {96}, {97}, {98}, {99}, {100}, {101}, {102}, {103}, {104}, {105}, {106}, {107}, {108}, {109}, {110}, {111}, {112}, {113}, {114}, {115}, {116}, {117}, {118}, {119}, {247}, {120}, {121}, {122}, {123}, {124}, {125}, {126}, {127}, {128}, {129}, {130}, {131}, {132}, {133}, {134}, {135}, {136}, {137}, {138}, {139}, {140}, {141}, {142}, {143}, {144}, {145}, {146}, {147}, {148}, {149}, {150}, {151}, {152}, {153}, {154}, {155}, {156}, {157}, {158}, {159}, {160}, {161}, {162}, {163}, {164}, {165}, {166}, {167}, {168}, {169}, {170}, {171}, {172}, {173}, {174}, {175}, {176}, {177}, {178}, {179}, {180}, {181}, {182}, {183}, {184}, {185}, {186}, {187}, {188}, {189}, {190}, {191}, {192}, {193}, {194}, {195}, {196}, {197}, {198}, {199}, {200}, {201}, {202}, {203}, {204}, {205}, {206}, {207}, {208}, {209}, {210}, {211}, {212}, {213}, {214}, {215}, {216}, {217}, {218}, {219}, {220}, {221}, {222}, {223}, {224}, {225}, {226}, {227}, {228}, {229}, {230}, {231}, {232}, {233}, {234}, {235}, {236}, {237}, {238}, {239}, {240}, {241}, {242}, {243}, {244}, {245}, {246}};
                #endif // M
            #endif // CODE_USED
        #endif
    #endif
}

// Manipulation of data
struct Matrix* cmatrix_encode(struct Matrix * word, struct Matrix_config * conf)
{
    return matrix_mul(conf->GENERATOR_MATRIX, word);
}

struct Matrix* cmatrix_decode(struct Matrix * word, struct Matrix_config * conf)
{
    struct Matrix* corr_word = cmatrix_correction(word, conf);
    struct Matrix* result = cmatrix_extract(word, conf);
    matrix_free(corr_word);

    return result;
}

// --------------- //
struct Matrix* cmatrix_extract(struct Matrix * word, struct Matrix_config * conf)
{
    struct Matrix* word_decode = matrix_generate(K, 1);

    for(uint16_t i = 1; i <= K; i++)
        matrix_set(word_decode, i, 1, matrix_get(word, i, 1));

    return word_decode;
}
struct Matrix* cmatrix_correction(struct Matrix * word, struct Matrix_config * conf)
{
    struct Matrix* synd = cmatrix_syndrome(word, conf);
    struct Matrix* word_correct = matrix_copy(word);

    if(!matrix_is_null(synd))
    {
        uint8_t synd_check = cmatrix_check_syndrome(synd, conf) + 1;
        matrix_set(word_correct, synd_check, 1, OPPOSITE_BIT(matrix_get(word, synd_check, 1)));

        return word_correct;
    }

    matrix_free(synd);
    return word_correct;
}

uint8_t cmatrix_check_syndrome(struct Matrix* synd, struct Matrix_config* conf)
{
    return conf->SYNDROMES_ARRAY[matrix_word_to_int(synd)];
}

struct Matrix* cmatrix_syndrome(struct Matrix* word, struct Matrix_config* conf)
{
    return matrix_mul(conf->CONTROL_MATRIX, word);
}
