/*
    Convention : d est une puissance de 2
    On a la relation 2^l = d
*/

#ifndef BASE_H
    #define BASE_H
    #include <inttypes.h>
    #include "utilities.h"

    struct Base
    {
        uint8_t d; // nombre d'elements dans l'ensemble de travail
        uint8_t l; // longueur des elements de la base (ex : dans F_8 : d = 8 mais l = 3)
    };

    struct Base base_generate(uint8_t l);
	
#endif // BASE_H
