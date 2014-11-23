#include <stdlib.h>
#include <stdio.h>
#include "utilities.h"
#include "hamming.h"
#include <time.h>

int test_data_matrix_system();
int test_hamming();

int rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}
char transform_int_to_char(uint8_t bin)
{
    if (bin == 0)
        return 48;
    else
        return 49;
}
uint8_t transform_char_to_int(char bin)
{
    if (bin == 48)
        return 0;
    else
        return 1;
}
int main(int argc, char *argv[])
{
    struct Base base = base_generate(1);
    struct Hamming_config conf = hamming_generate_config(base, 3); // On utilise la configuration (7,4,3)

    FILE* file = fopen("joconde.txt", "r"); // Le fichier test
    FILE* file_coded = fopen("joconde_coded.txt", "w+"); // Le fichier contenant le code

    FILE* file_decoded_no_correction = fopen("joconde_decoded_no_correction.txt", "w+"); // Le fichier contenant le code
    FILE* file_decoded_with_correction = fopen("joconde_decoded_with_correction.txt", "w+"); // Le fichier contenant le code

    // Codage du fichier
    struct Matrix word = matrix_generate(conf.word_size, 1, base);
    struct Matrix word_coded;
    struct Matrix word_correct;

    uint8_t caractereActuel;
    uint8_t nb = 0;
    uint8_t nb_alea = 0;
    srand(time(NULL)); // initialisation de rand

    // Boucle de lecture des caractères un à un
    do
    {
        if(nb == conf.word_size) // Si la matrice de codage est plein
        {
            // Gestion du codage
            word_coded = hamming_encode(&conf, &word); // On encode
            for(uint8_t i = 1; i <= conf.total_size; i++) // On écrit le code dans le fichier
            {
                // Enregistrement dans le coded
                fputc(transform_int_to_char(matrix_get(&word_coded, i, 1)), file_coded);

                // Ajout d'aspérité au code
                nb_alea = rand_a_b(0,7);
                if(nb_alea == 5)
                    matrix_set(&word_coded, i, 1, inverse_word(matrix_get(&word_coded, i, 1)));
            }

            // Gestion du decodage sans correction
            word = hamming_decode(&conf, &word_coded);
            for(uint8_t i = 1; i <= conf.word_size; i++)
                fputc(transform_int_to_char(matrix_get(&word, i, 1)), file_decoded_no_correction);

            // Gestion du décodage avec correction
            word_correct = hamming_correction(&conf, &word_coded);
            word = hamming_decode(&conf, &word_coded);

            for(uint8_t i = 1; i <= conf.word_size; i++)
                fputc(transform_int_to_char(matrix_get(&word, i, 1)), file_decoded_with_correction);

            // On réinitialise
            nb = 0;
            matrix_void(&word);
            matrix_void(&word_coded);
            matrix_void(&word_correct);
        }
        else
        {
            nb++;
            caractereActuel = fgetc(file); // On lit le caractère

            // Conversion en int
            caractereActuel = transform_char_to_int(caractereActuel);
            matrix_set(&word, nb, 1, caractereActuel);
        }

    } while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)

    printf("DONE !!");
    // Fermeture des fichiers
    fclose(file);
    fclose(file_coded);
    return EXIT_SUCCESS;
}

int test_hamming()
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
    struct Hamming_config conf = hamming_generate_config(base, 4);
    printf("--------------------------\n### TEST DU CODE DE HAMMING (%d, %d, %d) ###\n--------------------------\n\n", conf.total_size, conf.word_size, conf.correction_size);

    // Affichage des matrices de controle et de generation
    printf("Matrice de controle :\n");
    matrix_show(&(conf.control_matrix));

    printf("Matrice generatrice :\n");
    matrix_show(&(conf.generatrix_matrix));

    printf("Tableau de syndromes : \n");
    for(uint8_t i = 1; i < int_pow(2, conf.m); i++)
    {
        print_var_bits(i);
        printf(" : ");
        print_var_bits(conf.syndrome_array[i]);
        printf(" (%d : %d)", i, conf.syndrome_array[i]);
        printf("\n");
    }
    printf("\n");
    // Creation du mot a encoder
    struct Matrix dte = matrix_generate(conf.word_size, 1, base);
    matrix_set(&dte, 3, 1, 1);
    matrix_set(&dte, 1, 1, 1);

    // Affichage
    printf("Data to encode : %d elements\n", dte.data.data_number);
    matrix_show_word(&dte);

    // Encodage
    struct Matrix d = hamming_encode(&conf, &dte);

    printf("Data encoded : %d elements\n", d.data.data_number);
    matrix_show_word(&d);

    // Infiltration d'une erreur dans le mot
    data_set(3, 1, &(d.data));

    printf("Data modified : %d elements\n", d.data.data_number);
    matrix_show_word(&d);
    /**
    // Correction
    struct Matrix r = hamming_syndrome(&conf, &d);
    // Affichage de la correction
    printf("############\nCORRECTION\n############\n\n");
    printf("Syndrome du code modifie : %d \n", matrix_word_to_int(&r));
    data_show(&(r.data));

    if(!matrix_isempty(&r))
    {
        uint8_t b = hamming_check(&conf, &d);
        printf("######### BIT CORROMPU : Le bit numero %d est corrompu\n", b + 1);
    }
    else
        printf("######### AUCUN BIT CORROMPU\n\n");

    hamming_free_config(&conf);
    **/
    return EXIT_SUCCESS;
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
