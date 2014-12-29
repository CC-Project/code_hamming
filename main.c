#include "hamming.h"
#include "string.h"
#include "time.h"

void test_data();    //Test code for data struct
void test_matrix();  //Test code for matrix
void test_hamming(); //Test code for Hamming
void test_encode(); //Test Hamming code on an file

int main(int argc, char *argv[])
{
    for(uint64_t i = 0; i<1000; i++)
        test_hamming();
    return EXIT_SUCCESS;
}

void test_data()
{
    /**
    struct Data* d = data_generate(10);

    data_set(0, 1, d);
    data_set(1, data_get(0,d), d);
    data_show(d);
    data_delete(0,d);
    data_show(d);
    data_add(0,d);
    data_show(d);
    data_free(d);
    **/
}

void test_matrix()
{
    /**
    struct Matrix* m = matrix_generate(2,2);
    matrix_make_identity(m);
    matrix_free(m);
    /*/
}

void test_hamming()
{
    /**/
    struct Hamming_config* conf = hamming_generate_config();
//    printf("\nTest of the (%d, %d, %d) Hamming code\n--------------------------------\n\n", conf->EW_SIZE, conf->W_SIZE, conf->C_SIZE);
//
//    // Display the generator and control matrix
//    printf("Control matrix: \n");
//    matrix_show(conf->CONTROL_MATRIX);
//
//    printf("Generator matrix: \n");
//    matrix_show(conf->GENERATOR_MATRIX);
//
//
//    printf("Syndromes array: \n");
//    for(uint8_t i = 0; i <= conf->EW_SIZE; i++)
//    {
//        print_var_bits(i);
//        printf(" : ");
//        print_var_bits(conf->SYNDROMES_ARRAY->data_array[i]);
//        printf(" (%d : %d)", i, conf->SYNDROMES_ARRAY->data_array[i]);
//        printf("\n");
//    }
//    printf("\n");

    // Generation of the word to encode
    struct Matrix* dte = matrix_generate(conf->W_SIZE, 1);
    matrix_set(dte, 3, 1, 1);
    matrix_set(dte, 1, 1, 1);

//    // Display
//    printf("Data to encode : %d elements\n", dte->data->data_number);
//    matrix_show_word(dte);
//
//    // Encoding
    struct Matrix* d = hamming_encode(dte, conf);
//
//    printf("Data encoded : %d elements\n", d->data->data_number);
//    matrix_show_word(d);

    // Add an error
    data_set(3, 1, d->data);

//    printf("Data modified : %d elements\n", d->data->data_number);
//    matrix_show_word(d);

    // Correction
    struct Matrix* r = hamming_syndrome(d, conf);

//    // Affichage de la correction
//    printf("\n\nCorrection\n-----------\n\n");
//    printf("Syndrome of the modified code : %d \n", matrix_word_to_int(r));
//    data_show(r->data);

    if(!matrix_isempty(r))
    {
        uint8_t b = hamming_check_syndrome(r, conf);
//        printf("The bit %d is corrupted\n", b + 1);
    }
    else
//        printf("No bit corrupted\n");

    matrix_free(dte);
    matrix_free(d);
    matrix_free(r);

    hamming_free_config(conf);
    /**/
}

void test_encode()
{
    /**
    // Configuration
    char FILE_NAME[64] = "einstein";

    // Génération de la configuration de hamming
    struct Hamming_config* conf = hamming_generate_config();

    // Déclaration des variables
    char FILE_COMPLEMENT[64];
    char FILE_CODED_NAME[64];
    char FILE_DECODED_F_NAME[64];
    char FILE_DECODED_T_NAME[64];
    char FILE_PATH[64];
    char PROB_CHAR[32];

    FILE* file;
    FILE* file_coded;
    FILE* file_decoded_no_correction;
    FILE* file_decoded_with_correction;

    uint8_t caractereActuel;
    uint8_t nb;
    uint8_t nb_alea;

    uint8_t i;

    uint16_t PROBABILITY_OF_ERROR; // En pourmille

    // Divers
    srand(time(NULL)); // initialisation de rand

    for(uint16_t k = 0; k <= 1001; k = k + 20)
    {
        struct Matrix* word;
        struct Matrix* word_coded;
        struct Matrix* word_correct;

        PROBABILITY_OF_ERROR = k;

        // Gestion des chaines de caractères
        sprintf(PROB_CHAR, "%d", k); // Conversion en chaine de caractere

        sprintf(FILE_COMPLEMENT, "%s%s", FILE_NAME, "_");
        sprintf(FILE_COMPLEMENT, "%s%s", FILE_COMPLEMENT, PROB_CHAR);
        sprintf(FILE_PATH, "%s%s", FILE_NAME, ".txt");

        sprintf(FILE_CODED_NAME, "%s%s", FILE_NAME, "_CODED.txt");
        sprintf(FILE_DECODED_F_NAME, "%s%s", FILE_COMPLEMENT, "_DECODED_NO_C.txt");
        sprintf(FILE_DECODED_T_NAME, "%s%s", FILE_COMPLEMENT, "_DECODED_WITH_C.txt");

        // Ouverture des fichiers
        file = fopen(FILE_PATH, "r"); // Le fichier à exploiter
        file_coded = fopen(FILE_CODED_NAME, "w+"); // Le fichier contenant le code codé
        file_decoded_no_correction = fopen(FILE_DECODED_F_NAME, "w+"); // Le fichier contenant le code sans corrections
        file_decoded_with_correction = fopen(FILE_DECODED_T_NAME, "w+"); // Le fichier contenant le code corrigé

        // Initialisation des variables
        word = matrix_generate(conf->W_SIZE, 1);
        nb = 0; nb_alea = 0;

        // Lecture des caractères un à un
        do
        {
            if(nb == conf->W_SIZE) // Si la matrice de codage est pleine
            {
                // Gestion du codage
                word_coded = hamming_encode(word, conf); // On encode
                for(i = 1; i <= conf->EW_SIZE; i++) // On écrit le code dans le fichier
                {
                    if(k == 1) // Enregistrement dans le file_coded si c'est le premier passage
                        fputc(bin_to_ascii(matrix_get(word_coded, i, 1)), file_coded);

                    // Ajout d'aspérité au code
                    nb_alea = rand_a_b(0, 1000);
                    if(nb_alea < PROBABILITY_OF_ERROR)
                        matrix_set(word_coded, i, 1, opposite_bit(matrix_get(word_coded, i, 1)));
                }

                // Gestion du decodage sans correction
                word = hamming_decode(word_coded, conf);
                for(i = 1; i <= conf->W_SIZE; i++)
                    fputc(bin_to_ascii(matrix_get(word, i, 1)), file_decoded_no_correction);

                // Gestion du décodage avec correction
                word_correct = hamming_correction(word_coded, conf);
                word = hamming_decode(word_correct, conf);

                for(i = 1; i <= conf->W_SIZE; i++)
                    fputc(bin_to_ascii(matrix_get(word, i, 1)), file_decoded_with_correction);

                // On réinitialise
                nb = 0;
                matrix_void(word);
                matrix_void(word_coded);
                matrix_void(word_correct);
            }
            else
            {
                nb++;
                caractereActuel = fgetc(file); // On lit le caractère

                // Conversion en int
                if(caractereActuel != '\n')
                {
                    caractereActuel = ascii_to_bin(caractereActuel);
                    matrix_set(word, nb, 1, caractereActuel);
                }
            }

        } while (caractereActuel != '\n'); // On continue tant que fgetc n'a pas retourné un retour à la ligne (fin de fichier)

        // Fermeture des fichiers
        fclose(file);
        fclose(file_coded);
        fclose(file_decoded_no_correction);
        fclose(file_decoded_with_correction);

        matrix_free(word);
        matrix_free(word_coded);
        matrix_free(word_correct);

        printf("DONE !! \n");
    }

    // Libération des matrices
    hamming_free_config(conf);

    // Affichage final
    printf("TOTALY DONE !! \n");
    system("PAUSE>NUL");
    **/
}
