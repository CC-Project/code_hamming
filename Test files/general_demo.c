#include "../hamming.h"
#include "string.h"
#include "time.h"

void test_data();    //Test code for data struct
void test_matrix();  //Test code for matrix
void test_hamming(); //Test code for Hamming
uint16_t rand_a_b(uint16_t a, uint16_t b);  //Returns a random number between a and b (inclusive). Needed for test_encode()
void test_encode(); //Test Hamming code on an file

int main(int argc, char *argv[])
{
    test_hamming();
    return EXIT_SUCCESS;
}

void test_data()
{
    struct Data* d = data_generate(10);

    data_set(0, 1, d);
    data_set(2, 1, d);
    data_set(4, 1, d);
    data_set(9,1,d);
    data_show(d);
    data_delete(4,d);
    data_show(d);
    data_set(3,1,d);
    data_show(d);
    data_free(d);
}

void test_matrix()
{
    struct Matrix* m = matrix_generate(5,5);
    printf("Matrix null: %d\n", matrix_is_null(m));
    matrix_make_identity(m);
    struct Matrix* m2 = matrix_copy(m);
    matrix_set(m2,1,2,1);
    struct Matrix* m3 = matrix_mul(m2,m);
    matrix_show(m3);
    matrix_free(m);
    matrix_free(m2);
    matrix_free(m3);
}

void test_hamming()
{
    struct Hamming_config* conf = hamming_generate_config();
    printf("\nTest of the (%d, %d, 3) Hamming code\n--------------------------------\n\n", N, K);

    // Display the generator and control matrix
    printf("Control matrix: \n");
    matrix_show(conf->CONTROL_MATRIX);

    printf("Generator matrix: \n");
    matrix_show(conf->GENERATOR_MATRIX);


    printf("Syndromes array: \n");
    for(uint8_t i = 0; i <= N; i++)
    {
        print_var_bits(i);
        printf(" : ");
        print_var_bits(conf->SYNDROMES_ARRAY->data_array[i]);
        printf(" (%d : %d)", i, conf->SYNDROMES_ARRAY->data_array[i]);
        printf("\n");
    }
    printf("\n");

    // Generation of the word to encode
    struct Matrix* dte = matrix_generate(K, 1);
    matrix_set(dte, 3, 1, 1);
    matrix_set(dte, 1, 1, 1);

    // Display
    printf("Data to encode : %d elements\n", dte->data->data_number);
    matrix_show_word(dte);

    // Encoding
    struct Matrix* d = hamming_encode(dte, conf);
    printf("Data encoded : %d elements\n", d->data->data_number);
    matrix_show_word(d);

    // Add an error
    data_set(3, 1, d->data);

    printf("Data modified : %d elements\n", d->data->data_number);
    matrix_show_word(d);

    // Correction
    struct Matrix* r = hamming_syndrome(d, conf);

    printf("\n\nCorrection\n-----------\n\n");
    printf("Syndrome of the modified code : %d \n", matrix_word_to_int(r));

    if(!matrix_is_null(r))
    {
        uint8_t b = hamming_check_syndrome(r, conf);
        printf("The bit %d is corrupted\n", b + 1);
    }
    else
        printf("No bit corrupted\n");

    matrix_free(dte);
    matrix_free(d);
    matrix_free(r);

    hamming_free_config(conf);
}

uint16_t rand_a_b(uint16_t a, uint16_t b)
{
    return rand() % (b - a) + a;
}

void test_encode()
{
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

    // Matrices
    struct Matrix* word;
    struct Matrix* word_coded;
    struct Matrix* word_correct;

    // Divers
    srand(time(NULL)); // initialisation de rand

    for(uint16_t k = 0; k <= 1001; k = k + 20)
    {
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
        word = matrix_generate(K, 1);
        nb = 0; nb_alea = 0;

        // Lecture des caractères un à un
        do
        {
            if(nb == K) // Si la matrice de codage est pleine
            {
                // Gestion du codage
                word_coded = hamming_encode(word, conf); // On encode

                for(i = 1; i <= N; i++) // On écrit le code dans le fichier
                {
                    if(k == 1) // Enregistrement dans le file_coded si c'est le premier passage
                        fputc(bin_to_ascii(matrix_get(word_coded, i, 1)), file_coded);

                    // Ajout d'aspérité au code
                    nb_alea = rand_a_b(0, 1000);
                    if(nb_alea < PROBABILITY_OF_ERROR)
                        matrix_set(word_coded, i, 1, opposite_bit(matrix_get(word_coded, i, 1)));
                }

                // Gestion du decodage sans correction
                matrix_free(word); // On supprime l'ancienne valeur de word
                word = hamming_decode(word_coded, conf);

                for(i = 1; i <= K; i++)
                    fputc(bin_to_ascii(matrix_get(word, i, 1)), file_decoded_no_correction);

                // Gestion du décodage avec correction
                word_correct = hamming_correction(word_coded, conf);

                matrix_free(word); // On supprime l'ancienne valeur de word
                word = hamming_decode(word_correct, conf);

                for(i = 1; i <= K; i++)
                    fputc(bin_to_ascii(matrix_get(word, i, 1)), file_decoded_with_correction);

                // On réinitialise
                matrix_free(word);
                matrix_free(word_coded);
                matrix_free(word_correct);

                nb = 0;
                word = matrix_generate(K, 1);
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
}
