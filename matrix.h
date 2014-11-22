#ifndef MATRIX_H
    #define MATRIX_H
    #include <inttypes.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include "data.h"

    /**
    Structure des matrices binaires
    **/
    struct Matrix
    {
        uint16_t rows;
        uint16_t cols;

        struct Data data;
    };

    // Generation
    struct Matrix matrix_generate(uint16_t n, uint16_t p, struct Base base);

    // Functions
    uint16_t matrix_get_data_number(uint16_t i, uint16_t j, struct Matrix* m); // Return the number of the (i,j) data in data attribute
    uint8_t matrix_isempty(struct Matrix* m);
    struct Matrix matrix_copy(struct Matrix *a); // Copy a matrix

    // Operations
    void matrix_free(struct Matrix* m); // Free memory of a matrix
    void matrix_show(struct Matrix* m); // See a matrix
    void matrix_show_word(struct Matrix* m); // See a word in line
    void matrix_void(struct Matrix* m); // Void a matrix

    // Matrix's data manipulations
    void matrix_set(struct Matrix* m, uint16_t i, uint16_t j, uint8_t val); //Sets the i-th line, j-th column of m to val
    uint8_t matrix_get(struct Matrix* m, uint16_t i, uint16_t j); //Gets the i-th line, j-th column of m

    // Operations on matrix
    struct Matrix matrix_mul(struct Matrix* a, struct Matrix* b); // Mul two matrix
    struct Matrix matrix_add(struct Matrix* a, struct Matrix* b); // Add two matrix
    struct Matrix matrix_pow(struct Matrix * m, uint8_t n); // Return M^n
    struct Matrix matrix_transpose(struct Matrix * m); // Transpose a matrix

    struct Matrix matrix_collapse_down(struct Matrix *a, struct Matrix *b); // Collapse two matrix
    struct Matrix matrix_collapse_right(struct Matrix *a, struct Matrix *b);

    // Manipulation of matrix's cols and lines
    void matrix_del_line(uint16_t i, struct Matrix* m);
    void matrix_del_col(uint16_t j, struct Matrix* m);
    void matrix_exchange_cols(uint16_t j1, uint16_t j2, struct Matrix * m);
    void matrix_exchange_lines(uint16_t i1, uint16_t i2, struct Matrix * m);

    void matrix_make_identity(struct Matrix* m);
    void matrix_make_jidentity(struct Matrix* m);
    void matrix_reverse(struct Matrix *a); // Replace 0 by 1

    uint16_t matrix_word_to_int(struct Matrix * m); // Si la matrice envoyer est une matrice colonne, on renvoi le nombre associé au mot
#endif // MATRIX_H
