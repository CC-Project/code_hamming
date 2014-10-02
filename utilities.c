uint16_t int_pow(uint8_t a, uint8_t b)
{
    uint16_t r = 1;
    for(uint8_t i = 0; i < b; i++)
        r = r * a;
    return r;
}
