#include <
void data_get(unsigned short int number, struct Data *d)
{
    unsigned int real_nb = d->data_base.l * number; // Place r�el du premier bit de la donn�es recherch�
    unsigned int table_nb = (real_nb / 8); // Tableau dans lequel se trouve le bit calculer pr�c�dement
    unsigned int table_val_nb = (real_nb - (8 * (table))); // Place du bit rechercher dans le tableau calcul� pr�c�dement

    uint8_t table = d->data_array[table];
}

void data_set(unsigned short int number, unsigned char new_data, struct Data *d)
{

}
