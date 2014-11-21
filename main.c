#include <stdlib.h>
#include <stdio.h>
#include "utilities.h"
#include "hamming.h"
#include <time.h>

int test_data_matrix_system();

int main(int argc, char *argv[])
{
    struct Base base = base_generate(1);

    //Test code
    /**
    uint8_t* i = malloc(2*sizeof(uint8_t));
    i[0] = 1;
    i[1] = 2;
    i = realloc(i, 3 * sizeof(uint8_t));
    i[2] = 3;
    printf("%d %d %d", i[0], i[1], i[2]);
    free(i);
    **/

    //Test code for data struct
    /**
    struct Data d = data_generate(base,9);
    data_set(0,2, &d);
    data_set(1, data_get(0,&d), &d);
    data_show(&d);
    data_delete(1,&d);
    data_show(&d);
    data_add(3,&d);
    data_show(&d);
    data_free(&d);
    **/
    //return test_data_matrix_system(atoi(argv[1]));

    //Test code for hamming
    struct Hamming_config conf = hamming_generate_config(base, 3);
    printf("--------------------------\n### TEST DU CODE DE HAMMING (%d, %d, %d) ###\n--------------------------\n\n", conf.total_size, conf.word_size, conf.correction_size);

    // Affichage des matrices de controle et de generation
    printf("Matrice de controle :\n");
    matrix_show(&(conf.control_matrix));

    printf("Matrice generatrice :\n");
    matrix_show(&(conf.generatrix_matrix));

    // Creation du mot a encoder
    struct Matrix dte = matrix_generate(conf.word_size, 1, base);
    matrix_set(&dte, 1, 0, 1);
    matrix_set(&dte, 3, 0, 1);

    // Affichage
    printf("Data to encode (dte) :\n");
    matrix_show_word(&dte);
    /**
    // Encodage
    struct Matrix d = hamming_encode(&conf, &dte);

    printf("Data encoded (de) :\n");
    matrix_show_word(&d);

    // Infiltration d'une erreur dans le mot
    data_set(1, 1, &(d.data));

    printf("Data modified (dm) :\n");
    matrix_show_word(&d);

    // Correction
    struct Matrix r = hamming_syndrome(&conf, &(d));
    // Affichage de la correction
    printf("Syndrome C x de :\n");
    matrix_show_word(&r);
    **/
    hamming_free_config(&conf);
}

int test_data_matrix_system(int sec)
{
    clock_t time;
    int n = 0;
    struct Matrix m = matrix_generate(5, 5, base_generate(1));
    //matrix_show(&m);
    time = clock();
    while(time/CLOCKS_PER_SEC < sec)
    {
        for(uint8_t i = 1; i <= m.rows; i++)
            for(uint8_t j = 1; j <= m.cols; j++)
            {
                matrix_set(&m, i, j, matrix_get(&m, i, j) >> 7);
                n += 2;
            }

        time = clock();
    }

    //printf("Nombre de manipulations de donnees : %d\n", n);
    return n;
}
