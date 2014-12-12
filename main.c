#include "hamming.h"

void test_data();    //Test code for data struct
void test_matrix();  //Test code for matrix
void test_hamming(); //Test code for Hamming
void test_joconde(); //Test Hamming code on an image

int main(int argc, char *argv[])
{
    test_matrix();
    test_hamming();
    return EXIT_SUCCESS;
}

void test_data()
{
    /**
    struct Data* d = data_generate(2);

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
    struct Matrix m = matrix_generate(2,2);
    matrix_set(&m,2,2,1);
    matrix_void(&m);
    printf("Matrix is empty: %d\n", matrix_isempty(&m));
    matrix_show(&m);
    matrix_free(&m);
    **/
}

void test_hamming()
{
    /**
    struct Hamming_config conf = hamming_generate_config(4);
    printf("--------------------------\n### TEST OF HAMMING CODE (%d, %d, %d) ###\n--------------------------\n\n", conf.EW_SIZE, conf.W_SIZE, conf.C_SIZE);

    // Affichage des matrices de controle et de generation
    printf("Matrice de controle :\n");
    matrix_show(&(conf.CONTROL_MATRIX));

    printf("Matrice generatrice :\n");
    matrix_show(&(conf.GENERATOR_MATRIX));

    printf("Tableau de syndromes : \n");
    for(uint8_t i = 1; i < int_pow(2, conf.m); i++)
    {
        print_var_bits(i);
        printf(" : ");
        print_var_bits(conf.SYNDROMES_ARRAY[i]);
        printf(" (%d : %d)", i, conf.SYNDROMES_ARRAY[i]);
        printf("\n");
    }
    printf("\n");
    // Creation du mot a encoder
    struct Matrix dte = matrix_generate(conf.word_size, 1);
    matrix_set(&dte, 3, 1, 1);
    matrix_set(&dte, 1, 1, 1);

    // Affichage
    printf("Data to encode : %d elements\n", dte.data->data_number);
    matrix_show_word(&dte);

    // Encodage
    struct Matrix d = hamming_encode(&conf, &dte);

    printf("Data encoded : %d elements\n", d.data.data_number);
    matrix_show_word(&d);

    // Infiltration d'une erreur dans le mot
    data_set(3, 1, &(d.data));

    printf("Data modified : %d elements\n", d.data.data_number);
    matrix_show_word(&d);

    // Correction
    struct Matrix r = hamming_syndrome(&conf, &d);
    // Affichage de la correction
    printf("############\nCORRECTION\n############\n\n");
    printf("Syndrome du code modifié : %d \n", matrix_word_to_int(&r));
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
}

void test_joconde()
{
    /*
    uint8_t ERROR_RATE = 40;

    // Programme
    struct Hamming_config conf = hamming_generate_config();

    FILE* file = fopen("einstein.txt", "r"); // Le fichier test

    FILE* file_coded = fopen("j_coded.txt", "w+"); // Le fichier contenant le code

    FILE* file_decoded_no_correction = fopen("j_decoded_no_cor.txt", "w+"); // Le fichier contenant le code
    FILE* file_decoded_with_correction = fopen("j_decoded_with_cor.txt", "w+"); // Le fichier contenant le code

    // Codage du fichier
    struct Matrix word = matrix_generate(conf.W_SIZE, 1);
    struct Matrix word_coded;
    struct Matrix word_correct;

    struct Matrix synd;
    // Initialisation
    uint8_t caractereActuel;
    uint8_t nb = 0;
    uint8_t nb_alea = 0;

    srand(time(NULL)); // initialisation de rand

    // Boucle de lecture des caractères un à un
    do
    {
        //printf("%d\n", nb);
        if(nb == conf.W_SIZE) // Si la matrice de codage est pleine
        {
            // Gestion du codage
            word_coded = hamming_encode(&word, &conf); // On encode

            for(uint8_t i = 1; i <= conf.EW_SIZE; i++) // On écrit le code dans le fichier
            {
                // Enregistrement dans le coded
                fputc(bin_to_ascii(matrix_get(&word_coded, i, 1)), file_coded);

                // Ajout d'aspérité au code
                nb_alea = rand_a_b(0,ERROR_RATE);

                if(nb_alea == ERROR_RATE / 2)
                    matrix_set(&word_coded, i, 1, opposite_word(matrix_get(&word_coded, i, 1)));
            }

            // Gestion du decodage sans correction
            word = hamming_decode(&word_coded, &conf);

            for(uint8_t i = 1; i <= conf.W_SIZE; i++)
                fputc(bin_to_ascii(matrix_get(&word, i, 1)), file_decoded_no_correction);

            //synd = hamming_syndrome(&word_coded, &conf);
            //matrix_show(&synd);
            //printf("Syndrome : %d\n", conf.SYNDROMES_ARRAY.data_array[matrix_word_to_int(&synd)]);

            // Gestion du décodage avec correction
            word_correct = hamming_correction(&word_coded, &conf);
            word = hamming_decode(&word_correct, &conf);

            for(uint8_t i = 1; i <= conf.W_SIZE; i++)
                fputc(bin_to_ascii(matrix_get(&word, i, 1)), file_decoded_with_correction);

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
            if(caractereActuel != '\n')
            {
                caractereActuel = ascii_to_bin(caractereActuel);
                matrix_set(&word, nb, 1, caractereActuel);
            }
        }

    } while (caractereActuel != '\n'); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)

    matrix_free(&word);
    matrix_free(&word_coded);
    matrix_free(&word_correct);
    matrix_free(&synd);
    printf("\n############# \nDONE !! \n#############");
    // Fermeture des fichiers
    fclose(file);
    fclose(file_coded);

    return EXIT_SUCCESS;
    */
}
