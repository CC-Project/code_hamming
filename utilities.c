int int_pow(int a, int b)
{
    int r = 1;
    for(int i = 0; i < b; i++)
        r = r * a;
    return r;
}
