#include <
void data_get(uint16_t number, struct Data *d)
{
    uint16_t real_nb = d->data_base.l * number; // Place réel du premier bit de la données recherché
    uint16_t table_nb = (real_nb / 8); // Tableau dans lequel se trouve le bit calculer précédement
    uint8_t table_val_nb = (real_nb - (8 * (table))); // Place du bit rechercher dans le tableau calculé précédement

    uint8_t table = d->data_array[table];
}

void data_set(uint16_t number, uint8_t new_data, struct Data *d)
{

}
