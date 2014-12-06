#include "hamming.h"

int test_data();    //Test code for data struct
int test_matrix();  //Test code for matrix
int test_hamming(); //Test code for Hamming
int test_joconde(); //Test Hamming code on an image

int main(int argc, char *argv[])
{
    //General test code
    struct Hamming_config conf = hamming_generate_config();

    matrix_show(&(conf.CONTROL_MATRIX));
    matrix_show(&(conf.GENERATOR_MATRIX));

    for(uint16_t i = 0; i < conf.EW_SIZE; i++)
    {
        printf("%d : %d", i, conf.SYNDROMES_ARRAY.data_array[i]);
        printf("\n");
    }

    return EXIT_SUCCESS;
}

int test_data()
{
    struct Data d = data_generate(2);

    data_set(0, 1, &d);
    data_set(1, data_get(0,&d), &d);
    data_show(&d);
    data_delete(0,&d);
    data_show(&d);
    data_add(0,&d);
    data_show(&d);
    data_free(&d);

    return EXIT_SUCCESS;
}

int test_matrix()
{
    struct Matrix m = matrix_generate(2,2);
    matrix_set(&m,2,2,1);
    matrix_void(&m);
    printf("Matrix is empty: %d\n", matrix_isempty(&m));
    matrix_show(&m);
    matrix_free(&m);
    return EXIT_SUCCESS;
}

int test_hamming()
{
    /**
    struct Hamming_config conf = hamming_generate_config(4);
    printf("--------------------------\n### TEST OF HAMMING CODE (%d, %d, %d) ###\n--------------------------\n\n", conf.total_size, conf.word_size, conf.correction_size);

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
    struct Matrix dte = matrix_generate(conf.word_size, 1);
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
    return 1;
}

int test_joconde()
{
    /**
    struct Hamming_config conf = hamming_generate_config(3);
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
                fputc(bin_to_ascii(matrix_get(&word_coded, i, 1)), file_coded);

                // Ajout d'aspérité au code
                nb_alea = rand_a_b(0,40);
                if(nb_alea == 5)
                    matrix_set(&word_coded, i, 1, inverse_word(matrix_get(&word_coded, i, 1)));
            }

            // Gestion du decodage sans correction
            word = hamming_decode(&conf, &word_coded);
            for(uint8_t i = 1; i <= conf.word_size; i++)
                fputc(bin_to_ascii(matrix_get(&word, i, 1)), file_decoded_no_correction);

            // Gestion du décodage avec correction
            word_correct = hamming_correction(&conf, &word_coded);
            word = hamming_decode(&conf, &word_correct);

            for(uint8_t i = 1; i <= conf.word_size; i++)
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

    printf("DONE !!");
    // Fermeture des fichiers
    fclose(file);
    fclose(file_coded);
    **/
    return EXIT_SUCCESS;
}
