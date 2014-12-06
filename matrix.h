#ifndef MATRIX_H
    #define MATRIX_H
    #include "data.h"
    #include <math.h>

    /**
    # Structure des matrices :
        On travaille ici avec des uint16_t soit une taille de matrice maximum de 65535 x 65535 (2^16 -1 x 2^16 - 1)
        Les matrices peuvent stocker des nombres allant jusqu'a 2^BASE_L - 1
    **/

    struct Matrix
    {
        uint16_t rows; // Number of lines
        uint16_t cols; // Number of cols
        struct Data data;
    };

    // Generation and deletion
    struct Matrix matrix_generate(uint16_t n, uint16_t p);
    void matrix_free(struct Matrix* m);         // Frees memory of a matrix

    // Functions
    uint16_t matrix_get_data_number(uint16_t i, uint16_t j, struct Matrix* m);  // Return the number of the (i,j) data in data attribute
    uint8_t matrix_isempty(struct Matrix* m);                                   // Return 1 if the matrix is 0
    struct Matrix matrix_copy(struct Matrix *a);                                // Copy a matrix

    // Operations
    void matrix_show(struct Matrix* m);         // Prints out a matrix. Not adapted to avr.
    void matrix_show_word(struct Matrix* m);    // See a word in line
    void matrix_void(struct Matrix* m);         // Void a matrix

    // Matrix's data manipulations
    void matrix_set(struct Matrix* m, uint16_t i, uint16_t j, uint8_t val); //Sets the i-th line, j-th column of m to val
    uint8_t matrix_get(struct Matrix* m, uint16_t i, uint16_t j);           //Gets the i-th line, j-th column of m

    // Operations on matrix
    struct Matrix matrix_mul(struct Matrix* a, struct Matrix* b);   // Mul two matrix
    struct Matrix matrix_add(struct Matrix* a, struct Matrix* b);   // Add two matrix
    struct Matrix matrix_pow(struct Matrix * m, uint8_t n);         // Return M^n
    struct Matrix matrix_transpose(struct Matrix * m);              // Transpose a matrix

    struct Matrix matrix_collapse_down(struct Matrix *a, struct Matrix *b); // Collapse two matrix
    struct Matrix matrix_collapse_right(struct Matrix *a, struct Matrix *b);

    // Manipulation of matrix's cols and lines
    void matrix_del_line(uint16_t i, struct Matrix* m); // Remove a row
    void matrix_del_col(uint16_t j, struct Matrix* m);  // Remove a col
    void matrix_exchange_cols(uint16_t j1, uint16_t j2, struct Matrix * m);
    void matrix_exchange_lines(uint16_t i1, uint16_t i2, struct Matrix * m);

    // Manipulation of matrix types
    void matrix_make_identity(struct Matrix* m);
    void matrix_make_jidentity(struct Matrix* m);
    void matrix_opposite(struct Matrix *a);       // Returns the opposite matrix (Replace 0 by 1)

    uint16_t matrix_word_to_int(struct Matrix * m); // If the matrix is a word, this function return the number associated to this word
#endif // MATRIX_H
