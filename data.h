struct Data
{
    unsigned short int data_size;
    unsigned short int data_number;
	int8_t * *data_array;
};

void add_data(struct Data *d);
void get_data(struct Data *d, unsigned short int number);
void set_data(struct Data *d, unsigned short int number, unsigned char new_data);
