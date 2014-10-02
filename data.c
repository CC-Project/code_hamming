#include <
void data_get(unsigned short int number, struct Data *d)
{
    unsigned int real_nb = d->data_base.l * number; // Place réel du premier bit de la données recherché
    unsigned int table_nb = (real_nb / 8); // Tableau dans lequel se trouve le bit calculer précédement
    unsigned int table_val_nb = (real_nb - (8 * (table))); // Place du bit rechercher dans le tableau calculé précédement

    uint8_t table = d->data_array[table];
}

void data_set(unsigned short int number, unsigned char new_data, struct Data *d)
{

}
