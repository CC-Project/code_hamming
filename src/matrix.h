#ifndef MATRIX_H
    #define MATRIX_H
    #pragma once

    #ifndef __AVR__
        #include <inttypes.h>
        #include <stdlib.h>
    #endif // __AVR__

    // Include
    #include"../config.h"
    #include "../../lib_utilities/utilities.h"
    #include "../../lib_data/data.h"
    #include <math.h>

    struct Matrix
    {
        uint16_t rows; // Number of rows
        uint16_t cols; // Number of cols
        struct Data* data;
    };

    // Generation and deletion
    struct Matrix* matrix_generate(uint16_t n, uint16_t p); //Returns a pointer to a null matrix
    void matrix_free(struct Matrix* m);


    // Utilities
    #ifdef DEBUG
        void matrix_show(struct Matrix* m);         // Prints out a matrix. Not adapted to AVR.
        void matrix_show_word(struct Matrix* m);    // Prints a word (colum) in an human-readable line
    #endif

    struct Matrix* matrix_transpose(struct Matrix * m); // Transposes a matrix
    uint8_t matrix_is_null(struct Matrix* m);   // Returns 1 if the matrix is empty (0 everywhere)
    uint16_t matrix_get_data_number(uint16_t i, uint16_t j, struct Matrix* m);  // Return the number of the (i,j) data in data attribute
    void matrix_make_identity(struct Matrix* m);    // Returns I_k


    // Matrix's data manipulations
    void matrix_set(struct Matrix* m, uint16_t i, uint16_t j, uint8_t val); //Sets the i-th line, j-th column of m to val
    uint8_t matrix_get(struct Matrix* m, uint16_t i, uint16_t j);           //Gets the i-th line, j-th column of m
    struct Matrix* matrix_copy(struct Matrix *a);    // Copy a matrix


    // Operations on matrix
    struct Matrix* matrix_mul(struct Matrix* a, struct Matrix* b);           // Mul two matrix
    struct Matrix* matrix_concat_down(struct Matrix *a, struct Matrix *b);   // Concatenate two matrix, by adding b below a
    struct Matrix* matrix_concat_right(struct Matrix *a, struct Matrix *b);  //Concatenate two matrix, by adding b at the right side of a


    // Misc
    void matrix_del_col(uint16_t j, struct Matrix* m);  // Remove the j-th col of m.
    uint16_t matrix_word_to_int(struct Matrix * m); // If the matrix is a word, this function return the number associated to this word.
#endif // MATRIX_H
