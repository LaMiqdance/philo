void    cleanup(int *tab, int index)
{
    int i;

    i = 0;
    while (i < index)
    {
        free(tab[i]);
        i++;
    }
}