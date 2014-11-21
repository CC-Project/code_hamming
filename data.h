#ifndef DATA_H
    #define DATA_H
    #include "base.h"

    struct Data
    {
        struct Base data_base;  // Base de travail
        uint16_t data_number;   // Nombre de données contenu dans le tableau "data_array"
        uint8_t* data_array;    // Tableau de uint8_t contenant les données
    };

    struct Data data_generate(struct Base base, uint16_t data_number);
    uint8_t data_get(uint16_t n, struct Data* d);               //Returns the n-th data stored. Starting from 0.

    void data_free(struct Data* d);                             //Frees the memory
    void data_set(uint16_t n, uint8_t data, struct Data* d);    //Sets the n-th block of d to data
    void data_add(uint8_t data, struct Data* d);                // Add data at the end of d
    void data_delete(uint16_t n, struct Data* d);               // Delete the n-th block of d

    void data_show(struct Data* d);     // Print a data
#endif // DATA_H

