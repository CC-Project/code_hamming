#include <
void data_get(uint16_t number, struct Data *d)
{
    uint16_t real_nb = d->data_base.l * number; // Place r�el du premier bit de la donn�es recherch�
    uint16_t table_nb = (real_nb / 8); // Tableau dans lequel se trouve le bit calculer pr�c�dement
    uint8_t table_val_nb = (real_nb - (8 * (table))); // Place du bit rechercher dans le tableau calcul� pr�c�dement

    uint8_t table = d->data_array[table];
}

void data_set(uint16_t number, uint8_t new_data, struct Data *d)
{

}
