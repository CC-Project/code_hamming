struct Data
{
    struct Base data_base; // Base de travail
    uint16_t data_number; // Npmbre de données contenu dans le tableau "data_array"
	uint8_t ** data_array; // Tableau de uint8_t contenant les données
};

void data_get(uint16_t number, struct Data *d);
void data_set(uint16_t number, uint8_t new_data, struct Data *d);
