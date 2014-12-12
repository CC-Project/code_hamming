#ifndef MATRIX_H
    #define MATRIX_H
    #include "data.h"
    #include <math.h>

    struct Matrix
    {
        uint16_t rows; // Number of rows
        uint16_t cols; // Number of cols
        struct Data* data;
    };

    // Generation and deletion
    struct Matrix matrix_generate(uint16_t n, uint16_t p);
    void matrix_free(struct Matrix* m);


    // Utilities
    void matrix_show(struct Matrix* m);         // Prints out a matrix. Not adapted to AVR.
    void matrix_show_word(struct Matrix* m);    // Prints a word (colum) in an human-readable line
    uint8_t matrix_isempty(struct Matrix* m);   // Returns 1 if the matrix is empty (0 everywhere)
    uint16_t matrix_get_data_number(uint16_t i, uint16_t j, struct Matrix* m);  // Return the number of the (i,j) data in data attribute
    void matrix_make_identity(struct Matrix* m);    // Returns I_k
    void matrix_make_jidentity(struct Matrix* m);   // Returns J_k
    void matrix_opposite(struct Matrix *a);       // Returns the opposite matrix (Replace 0 by 1)


    // Matrix's data manipulations
    void matrix_set(struct Matrix* m, uint16_t i, uint16_t j, uint8_t val); //Sets the i-th line, j-th column of m to val
    uint8_t matrix_get(struct Matrix* m, uint16_t i, uint16_t j);           //Gets the i-th line, j-th column of m
    void matrix_void(struct Matrix* m);             // Voids a matrix i.e sets all data to 0.
    struct Matrix matrix_copy(struct Matrix *a);    // Copy a matrix


    // Operations on matrix
    struct Matrix matrix_mul(struct Matrix* a, struct Matrix* b);               // Mul two matrix
    struct Matrix matrix_add(struct Matrix* a, struct Matrix* b);               // Adds two matrix
    struct Matrix matrix_pow(struct Matrix * m, uint8_t n);                     // Returns M^n
    struct Matrix matrix_transpose(struct Matrix * m);                          // Transposes a matrix
    struct Matrix matrix_collapse_down(struct Matrix *a, struct Matrix *b);     // Collapse two matrix
    struct Matrix matrix_collapse_right(struct Matrix *a, struct Matrix *b);


    // Manipulation of rows and cols
    void matrix_del_row(uint16_t i, struct Matrix* m);  // Removes the i-th row of m. Thus the format is changed
    void matrix_del_col(uint16_t j, struct Matrix* m);  // Remove the j-th col of m.
    void matrix_exchange_rows(uint16_t i1, uint16_t i2, struct Matrix * m);
    void matrix_exchange_cols(uint16_t j1, uint16_t j2, struct Matrix * m);


    uint16_t matrix_word_to_int(struct Matrix * m); // If the matrix is a word, this function return the number associated to this word
#endif // MATRIX_H
