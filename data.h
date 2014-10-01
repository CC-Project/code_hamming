struct Data
{
    struct Base data_base; // Base de travail
    unsigned short int data_number; // Npmbre de donn�es contenu dans le tableau "data_array"
	uint8_t ** data_array; // Tableau de uint8_t contenant les donn�es
};

void add_data(struct Data *d);
void get_data(struct Data *d, unsigned short int number);
void set_data(struct Data *d, unsigned short int number, unsigned char new_data);
